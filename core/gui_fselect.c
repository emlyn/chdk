#include "stdlib.h"
#include "keyboard.h"
#include "platform.h"
#include "core.h"
#include "lang.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_lang.h"
#include "gui_mbox.h"
#include "gui_mpopup.h"
#include "gui_fselect.h"
#include "raw_merge.h"
#include "conf.h"

//-------------------------------------------------------------------
#define HEAD_LINES              1
#define BODY_LINES              10
#define FOOT_LINES              1
#define HEAD_FONT_LINES         HEAD_LINES * FONT_HEIGHT
#define BODY_FONT_LINES         BODY_LINES * FONT_HEIGHT
#define FOOT_FONT_LINES         FOOT_LINES * FONT_HEIGHT

#define NAME_SIZE               15 // "FILENAME123 "
#define SIZE_SIZE               7 // "1000 b|M|G"
#define TIME_SIZE               14 // "01.01'70 00:00"

#define NAME_FONT_SIZE          NAME_SIZE * FONT_WIDTH
#define EXTE_FONT_SIZE          EXTE_SIZE * FONT_WIDTH
#define SIZE_FONT_SIZE          SIZE_SIZE * FONT_WIDTH
#define TIME_FONT_SIZE          TIME_SIZE * FONT_WIDTH

#define SPACING                 4
#define TAB_DIVIDER             1
#define BORDER                  2
#define SCROLLBAR               4

#define MARKED_OP_NONE          0
#define MARKED_OP_CUT           1
#define MARKED_OP_COPY          2
#define MARKED_BUF_SIZE         0x10000

//-------------------------------------------------------------------
static char current_dir[100], selected_file[100];
static char buf[100];
static char marked_dir[100];
static enum Gui_Mode    gui_fselect_mode_old;
struct fitem {
    unsigned int    n;
    char            *name;
    unsigned char   attr;
    unsigned long   size;
    unsigned long   mtime;
    unsigned char   marked;
    struct fitem    *prev, *next;
};
static struct fitem *head=NULL, *top, *selected;
static unsigned int count, max_dir_len;
static struct fitem *marked_head=NULL;
static unsigned int marked_count;
static char marked_operation;
static coord main_x, main_y, main_w, main_h; //main browser window coord (without BORDERs)
static coord head_x, head_y, head_w, head_h; //header window coord
static coord body_x, body_y, body_w, body_h; //main body window coord
static coord foot_x, foot_y, foot_w, foot_h; //footer window coord 
static int gui_fselect_redraw;
static char *fselect_title;
static void (*fselect_on_select)(const char *fn);
static char raw_operation;

//-------------------------------------------------------------------
static void gui_fselect_free_data() {
    struct fitem  *ptr = head, *prev;

    while (ptr) {
        if (ptr->name)
            free(ptr->name);
        prev = ptr;
        ptr = ptr->next;
        free(prev);
    }
    head = top = selected = NULL;
    count = 0;
}

//-------------------------------------------------------------------
extern int fselect_sort_nothumb(const void* v1, const void* v2);
int fselect_sort(const void* v1, const void* v2) {
    struct fitem *i1=*((struct fitem **)v1), *i2=*((struct fitem **)v2);

    if (i1->attr & DOS_ATTR_DIRECTORY) {
        if (i2->attr & DOS_ATTR_DIRECTORY) {
            if (i1->name[0]=='.' && i1->name[1]=='.' && i1->name[2]==0) {
                return -1;
            } else if (i2->name[0]=='.' && i2->name[1]=='.' && i2->name[2]==0) {
                return 1;
            } else {
                return strcmp(i1->name, i2->name);
            }
        } else {
            return -1;
        }
    } else {
        if (i2->attr & DOS_ATTR_DIRECTORY) {
            return 1;
        } else {
            return strcmp(i1->name, i2->name);
        }
    }
}

//-------------------------------------------------------------------
static void gui_fselect_read_dir(const char* dir) {
    DIR           *d;
    struct dirent *de;
    static struct stat   st;
    struct fitem  **ptr = &head, *prev = NULL;
    int    i;

    gui_fselect_free_data();

    d = opendir(dir);
    if (d) {
        de = readdir(d);
        while (de) {
            if (de->name[0] != 0xE5 /* deleted entry */ && (de->name[0]!='.' || de->name[1]!=0)) {
                *ptr = malloc(sizeof(struct fitem));
                if (*ptr) {
                    (*ptr)->n = count;
                    (*ptr)->name = malloc(strlen(de->name)+1);
                    if ((*ptr)->name)
                        strcpy((*ptr)->name, de->name);
                    sprintf(buf, "%s/%s", dir, de->name);
                    if (stat(buf, &st)==0) {
                        (*ptr)->attr=st.st_attrib;
                        (*ptr)->size=st.st_size;
                        (*ptr)->mtime=st.st_mtime;
                    } else {
                        (*ptr)->attr=(de->name[0]=='.' && de->name[1]=='.' && de->name[2]==0)?DOS_ATTR_DIRECTORY:0xFF;
                        (*ptr)->size=(*ptr)->mtime=0;
                    }
                    (*ptr)->marked=0;
                    (*ptr)->prev=prev;
                    prev=*ptr;
                    ptr = &((*ptr)->next);
                    ++count;
                }   
            }
            de = readdir(d);
        }
        closedir(d);
    }
    *ptr=NULL;
    
    if (count) {
        // sort
        ptr=malloc(count*sizeof(struct fitem*));
        if (ptr) {
            prev=head;
            count=0;
            while (prev) {
                ptr[count++]=prev;
                prev=prev->next;
            }
            
            qsort(ptr, count, sizeof(struct fitem*), fselect_sort_nothumb);
            
            for (i=0; i<count-1; ++i) {
                ptr[i]->n=i;
                ptr[i]->next=ptr[i+1];
                ptr[i+1]->prev=ptr[i];
            }
            ptr[0]->prev=ptr[count-1]->next=NULL;
            ptr[count-1]->n=count-1;
            head=ptr[0];

            free(ptr);
        }
    }

    top = selected = head;
}

//-------------------------------------------------------------------
void gui_fselect_init(int title, const char* dir, void (*on_select)(const char *fn)) {
    int i;
    
    int chars_width = NAME_FONT_SIZE + SIZE_FONT_SIZE + TIME_FONT_SIZE;
    main_w = SPACING/*N*/+SPACING+TAB_DIVIDER+SPACING/*S*/+SPACING+TAB_DIVIDER+SPACING/*T*/+SPACING+SCROLLBAR+chars_width;
    main_h = HEAD_FONT_LINES + TAB_DIVIDER + BODY_FONT_LINES + TAB_DIVIDER + FOOT_FONT_LINES;
    main_x = (screen_width - main_w) >> 1;
    main_y = (screen_height - main_h) >> 1;
    
    head_x = body_x = foot_x = main_x;
    head_w = body_w = foot_w = main_w;    
    head_y = main_y;
    head_h = HEAD_FONT_LINES;    
    body_y = head_y + head_h + TAB_DIVIDER;
    body_h = BODY_FONT_LINES;
    foot_y = body_y + body_h + TAB_DIVIDER;
    foot_h = FOOT_FONT_LINES;
    
    fselect_title = lang_str(title);
    strcpy(current_dir, dir);
    max_dir_len = NAME_SIZE + SIZE_SIZE + SPACING;
    gui_fselect_read_dir(current_dir);
    top = selected = head;
    selected_file[0] = 0;
    fselect_on_select = on_select;
    marked_operation = MARKED_OP_NONE;
    gui_fselect_mode_old = gui_get_mode();
    gui_fselect_redraw = 2;
    gui_set_mode(GUI_MODE_FSELECT);
}

//-------------------------------------------------------------------
char* gui_fselect_result() {
    if (selected_file[0])
        return selected_file;
    else
        return NULL;
}

//-------------------------------------------------------------------
void gui_fselect_draw_initial() {
    int title_font_size;
    int i;

    draw_filled_rect(head_x, head_y, head_x+head_w-1, head_y+head_h-1, MAKE_COLOR(COLOR_BLACK, COLOR_BLACK)); //header box
    title_font_size = strlen(fselect_title) * FONT_WIDTH;
    draw_string(head_x+((head_w-title_font_size)>>1), head_y, fselect_title, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE)); //title text
    
    for (i = 1; i <= BORDER; i++)
      draw_rect(main_x-i, main_y-i, main_x+main_w+i-1, main_y+main_h+i-1, MAKE_COLOR(COLOR_WHITE, COLOR_WHITE)); //border frame
    draw_line(body_x, body_y-1, body_x+body_w-1, body_y-1, MAKE_COLOR(COLOR_WHITE, COLOR_WHITE)); //border head-body
    draw_line(foot_x, foot_y-1, foot_x+foot_w-1, foot_y-1, MAKE_COLOR(COLOR_WHITE, COLOR_WHITE)); //border body-foot    
}

//-------------------------------------------------------------------
void gui_fselect_draw() {
    int i, j, off_name_x, off_size_x, off_time_x, off_body_x, off_body_y;
    struct fitem  *ptr;
    char buf[100];
    struct tm *time;
    unsigned long sum_size;
    color cl_markered = ((mode_get()&MODE_MASK) == MODE_REC)?COLOR_YELLOW:0x66;
    color cl_marked, cl_selected;

    if (gui_fselect_redraw) {
        if (gui_fselect_redraw == 2)
            gui_fselect_draw_initial();

        off_body_y = 0;
        off_name_x = body_x+SPACING;
        off_size_x = off_name_x+NAME_FONT_SIZE+SPACING+TAB_DIVIDER+SPACING;
        off_time_x = off_size_x+SIZE_FONT_SIZE+SPACING+TAB_DIVIDER+SPACING;
        off_body_x = off_time_x+TIME_FONT_SIZE+SPACING;

        sum_size = 0;
        for (i=0, ptr=top; i<BODY_LINES && ptr; ++i, ptr=ptr->next) {
        
            cl_marked = MAKE_COLOR((ptr==selected)?COLOR_RED:COLOR_GREY, (ptr->marked)?cl_markered:COLOR_WHITE);
            cl_selected = (ptr==selected)?MAKE_COLOR(COLOR_RED, COLOR_RED):MAKE_COLOR(COLOR_GREY, COLOR_GREY);
        
            // print name
            for (j=0; j<NAME_SIZE && ptr->name[j]; ++j) 
                buf[j] = ptr->name[j];
                
            if (j==NAME_SIZE && ptr->name[j]) buf[NAME_SIZE-1] = '~'; // too long name
            
            if (ptr->attr & DOS_ATTR_DIRECTORY && ptr->attr != 0xFF) { //?
                if (j<NAME_SIZE) {
                    buf[j++]='/';
                } else {
                    buf[NAME_SIZE-2]='~';
                    buf[NAME_SIZE-1]='/';
                }
            }
            for (; j<NAME_SIZE && (buf[j++]=' ');); //fill upto NAME_SIZE
            buf[NAME_SIZE] = 0; // eos
            
            off_body_y = body_y+(i*FONT_HEIGHT);
            draw_filled_rect(body_x, off_body_y, off_name_x-1, off_body_y+FONT_HEIGHT-1, cl_selected);
            draw_string(off_name_x, off_body_y, buf, cl_marked);
            draw_filled_rect(off_name_x+NAME_FONT_SIZE, off_body_y, off_name_x+NAME_FONT_SIZE+SPACING-1, off_body_y+FONT_HEIGHT-1, cl_selected);
            
            // print size or <Dir>
            if (ptr->attr & DOS_ATTR_DIRECTORY) {
                if (ptr->attr == 0xFF) {
                    sprintf(buf, "  ???  ");
                } else if (ptr->name[0] == '.' && ptr->name[1] == '.' && ptr->name[2] == 0) {
                    sprintf(buf, "<UpDir>");
                } else {
                    sprintf(buf, "< Dir >");
                }
            } else {
                if (ptr->size < 1024)
                    sprintf(buf, "%5d b", ptr->size); // " 1023 b"
                else if (ptr->size < 1024*1024)
                    sprintf(buf, "%3ld,%1d k", ptr->size/1024, (ptr->size%1024*10)/1024); // "999,9 k"
                else if (ptr->size < 1024*1024*1024)
                    sprintf(buf, "%3ld,%ld M", ptr->size/(1024*1024), (ptr->size%(1024*1024)*10)/(1024*1024) ); // "999,9 M"
                else
                    sprintf(buf, "%31d,%ld G", ptr->size/(1024*1024*1024), (ptr->size%(1024*1024*1024)*10)/(1024*1024*1024)); // "999.9 G"
                    
                if (ptr->marked)
                  sum_size += ptr->size;
            }
            buf[SIZE_SIZE] = 0;
            //tab divider
            draw_line(off_size_x-TAB_DIVIDER-SPACING, off_body_y, off_size_x-TAB_DIVIDER-SPACING, off_body_y+FONT_HEIGHT-1, COLOR_WHITE);
            draw_filled_rect(off_size_x-SPACING, off_body_y, off_size_x-1, off_body_y+FONT_HEIGHT-1, cl_selected);            
            draw_string(off_size_x, off_body_y, buf, cl_marked);
            draw_filled_rect(off_size_x+SIZE_FONT_SIZE, off_body_y, off_size_x+SIZE_FONT_SIZE+SPACING-1, off_body_y+FONT_HEIGHT-1, cl_selected);            
            
            // print modification time
            if (ptr->mtime) {
                time = localtime(&(ptr->mtime));
                sprintf(buf, "%02u.%02u'%02u %02u:%02u", time->tm_mday, time->tm_mon+1, (time->tm_year<100)?time->tm_year:time->tm_year-100, time->tm_hour, time->tm_min);
            } else {
                sprintf(buf, "%14s", "");
            }
            buf[TIME_SIZE] = 0;
            //tab divider
            draw_line(off_time_x-TAB_DIVIDER-SPACING, off_body_y, off_time_x-TAB_DIVIDER-SPACING, off_body_y+FONT_HEIGHT-1, COLOR_WHITE);
            draw_filled_rect(off_time_x-SPACING, off_body_y, off_time_x-1, off_body_y+FONT_HEIGHT-1, cl_selected);
            draw_string(off_time_x, off_body_y, buf, cl_marked);            
            draw_filled_rect(off_time_x+TIME_FONT_SIZE, off_body_y, off_time_x+TIME_FONT_SIZE+SPACING-1, off_body_y+FONT_HEIGHT-1, cl_selected);
        }

        //fill the rest of body
        off_body_y += FONT_HEIGHT;
        if (i>0 && i<BODY_LINES) {
            draw_filled_rect(body_x, off_body_y, body_x+body_w-1, body_y+body_h-1, MAKE_COLOR(COLOR_GREY, COLOR_GREY));
        }
        
       // scrollbar
        draw_filled_rect(off_body_x, body_y, off_body_x+SCROLLBAR-1, body_y+body_h-1, MAKE_COLOR(COLOR_BLACK, COLOR_BLACK));
        if (count>BODY_LINES) {
            i = BODY_FONT_LINES - 1;
            j = i*BODY_LINES/count;
            if (j<20) j=20;
            i = (i-j)*selected->n/(count-1);
            draw_filled_rect(off_body_x, body_y+i, off_body_x+SCROLLBAR-2, body_y+i+j, MAKE_COLOR(COLOR_WHITE, COLOR_WHITE));
        }

        //footer
        i = strlen(current_dir);
        if (i > max_dir_len) {
          strncpy(buf, current_dir+i-max_dir_len, max_dir_len);
          buf[0] = '.';
          buf[1] = '.';          
        } else {
          strcpy(buf, current_dir);          
        }
        buf[max_dir_len] = 0;
        draw_filled_rect(foot_x, foot_y, foot_x+foot_w-1, foot_y+foot_h-1, MAKE_COLOR(COLOR_GREY, COLOR_GREY)); //footer box        
        draw_string(off_name_x, foot_y, buf, MAKE_COLOR(COLOR_GREY, COLOR_WHITE)); //current dir
        
        if (sum_size) {
          sprintf(buf, "%d b", sum_size); //selected size
        } else {
          unsigned int fr, tot;
          fr = GetFreeCardSpaceKb(); tot = GetTotalCardSpaceKb();
          if (fr < 1024*1024)
            sprintf(buf, "%dM (%d%%)", fr/1024, tot? fr*100/tot: 0);
          else
            sprintf(buf, "%dG (%d%%)", fr/(1024*1024), tot? fr*100/tot: 0);
        }
        draw_string(foot_x+foot_w-strlen(buf)*FONT_WIDTH-BORDER, foot_y, buf, MAKE_COLOR(COLOR_GREY, COLOR_WHITE)); // free space
        gui_fselect_redraw = 0;
    }
}

//-------------------------------------------------------------------
static void fselect_delete_file_cb(unsigned int btn) {
    if (btn==MBOX_BTN_YES) {
        started();
        sprintf(selected_file, "%s/%s", current_dir, selected->name);
        remove(selected_file);
        finished();
        selected_file[0]=0;
        gui_fselect_read_dir(current_dir);
    }
    gui_fselect_redraw = 2;
}

static void fselect_purge_cb(unsigned int btn) {

   DIR             *d,  *d2,  *d3,  *d4;
   struct dirent   *de, *de2, *de3, *de4;
   struct fitem    *ptr, *ptr2;
   char            sub_dir[20], sub_dir_search[20];
   char            selected_item[256];
   int             i, found=0;

   if (btn==MBOX_BTN_YES) {
       //If selected folder is DCIM (this is to purge all RAW files in any Canon folder)
       if (selected->name[0] == 'D' && selected->name[1] == 'C' && selected->name[2] == 'I' && selected->name[3] == 'M') {
           sprintf(current_dir+strlen(current_dir), "/%s", selected->name);
           d=opendir(current_dir);
           while ((de=readdir(d)) != NULL) {//Loop to find all Canon folders
               if (de->name[0] != '.' && de->name[1] != '.') {//If item is not UpDir
                   sprintf(sub_dir, "%s/%s", current_dir, de->name);
                   d2=opendir(sub_dir);
                   while ((de2=readdir(d2)) != NULL) {//Loop to find all the RAW files inside a Canon folder
                       if (de2->name[0] == 'C' || de2->name[9] == 'C') {//If file is RAW (Either CRW/CR2 prefix or file extension)
                           d3=opendir(current_dir);
                           while ((de3=readdir(d3)) != NULL) {//Loop to find all Canon folders
                               if (de3->name[0] != '.' && de3->name[1] != '.') {//If item is not UpDir
                                   sprintf(sub_dir_search, "%s/%s", current_dir, de3->name);
                                   d4=opendir(sub_dir_search);
                                   while ((de4=readdir(d4)) != NULL) {//Loop to find a corresponding JPG file inside a Canon folder
                                       if (de2->name[4] == de4->name[4] && de2->name[5] == de4->name[5] &&//If the four digits of the Canon number are the same
                                           de2->name[6] == de4->name[6] && de2->name[7] == de4->name[7] &&
                                           de4->name[9] == 'J' && !(de4->name[0] == 'C' || de4->name[9] == 'C' || de4->name[0] == 0xE5)) {//If file is JPG, is not CRW/CR2 and is not a deleted item
                                           started();
                                           found=1;//A JPG file with the same Canon number was found
                                       }                                 
                                   }
                                   closedir(d4);                 
                               }  
                           }
                           closedir(d3);
                           //If no JPG found, delete RAW file
                           if (found == 0) {
                               sprintf(selected_item, "%s/%s", sub_dir, de2->name);
                               remove(selected_item);
                               finished();
                           }
                           else {
                               found=0;
                               finished();
                           }                             
                       }
                   }
                   closedir(d2);
               }
           }
           closedir(d);
           i=strlen(current_dir);
           while (current_dir[--i] != '/');
           current_dir[i]=0;
       }
       //If item is a Canon folder (this is to purge all RAW files inside a single Canon folder)
       else if (selected->name[3] == 'C') {
           sprintf(current_dir+strlen(current_dir), "/%s", selected->name);
           d=opendir(current_dir);
           while ((de=readdir(d)) != NULL) {//Loop to find all the RAW files inside the Canon folder 
               if (de->name[0] == 'C' || de->name[9] == 'C') {//If file is RAW (Either CRW/CR2 prefix or file extension)
                   d2=opendir(current_dir);
                   while ((de2=readdir(d2)) != NULL) {//Loop to find a corresponding JPG file inside the Canon folder
                       if (de->name[4] == de2->name[4] && de->name[5] == de2->name[5] &&//If the four digits of the Canon number are the same
                           de->name[6] == de2->name[6] && de->name[7] == de2->name[7] &&
                           de2->name[9] == 'J' && !(de2->name[0] == 'C' || de2->name[9] == 'C' || de2->name[0] == 0xE5)) {//If file is JPG and is not CRW/CR2 and is not a deleted item
                           started();
                           found=1;//A JPG file with the same Canon number was found
                       }                                 
                   }
                   closedir(d2); 
                   //If no JPG found, delete RAW file                
                   if (found == 0) {
                       sprintf(selected_item, "%s/%s", current_dir, de->name);
                       remove(selected_item);
                       finished();
                   }
                   else {
                       found=0;
                       finished();
                   }
               }
           }
           closedir(d);
           i=strlen(current_dir);
           while (current_dir[--i] != '/');
           current_dir[i]=0;
       }
       else {
           //If inside a Canon folder (files list)
           for (ptr=head; ptr; ptr=ptr->next) {//Loop to find all the RAW files in the list
               if ((ptr->name[0] == 'C' || ptr->name[9] == 'C') && !(ptr->marked)) {//If file is RAW (Either CRW/CR2 prefix or file extension) and is not marked
                   for (ptr2=head; ptr2; ptr2=ptr2->next) {//Loop to find a corresponding JPG file in the list
                       if (ptr->name[4] == ptr2->name[4] && ptr->name[5] == ptr2->name[5] &&//If the four digits of the Canon number are the same
                           ptr->name[6] == ptr2->name[6] && ptr->name[7] == ptr2->name[7] &&
                           ptr2->name[9] == 'J' && !(ptr2->name[0] == 'C' || ptr2->name[9] == 'C')) {//If file is JPG and is not CRW/CR2
                           started();
                           found=1;
                       }
                   }
                   //If no JPG found, delete RAW file           
                   if (found == 0) {
                       sprintf(selected_file, "%s/%s", current_dir, ptr->name);
                       remove(selected_file);
                       finished();
                   }
                   else {
                       found=0;
                       finished();
                   }
               }
           }
       }
       gui_fselect_read_dir(current_dir);
   }
   gui_fselect_redraw = 2;
}


//-------------------------------------------------------------------
static void fselect_delete_folder_cb(unsigned int btn) {
    DIR           *d;
    struct dirent *de;
    int           i;

    if (btn==MBOX_BTN_YES) {
        sprintf(current_dir+strlen(current_dir), "/%s", selected->name);
        d = opendir(current_dir);
        if (d) {
            de = readdir(d);
            while (de) {
                if (de->name[0] != 0xE5 /* deleted entry */ && (de->name[0]!='.' || (de->name[1]!='.' && de->name[1]!=0) || (de->name[1]=='.' && de->name[2]!=0))) {
                    started();
                    sprintf(selected_file, "%s/%s", current_dir, de->name);
                    remove(selected_file);
                    finished();
                }
                de = readdir(d);
            }
            closedir(d);
        }
        started();
        remove(current_dir);
        finished();
        i=strlen(current_dir);
        while (current_dir[--i] != '/');
        current_dir[i]=0;
        selected_file[0]=0;
        gui_fselect_read_dir(current_dir);
    }
    gui_fselect_redraw = 2;
}

//-------------------------------------------------------------------
static void fselect_goto_prev(int step) {
    register int j, i;

    for (j=0; j<step; ++j) {
        if (selected->prev==top && top->prev) 
            top=top->prev;
        if (selected->prev) 
            selected=selected->prev;
		else
		if (step == 1)
		{
			for(; selected->next; selected=selected->next);
			for (i=0, top=selected; i<BODY_LINES-1 && top->prev; ++i, top=top->prev);
		}
    }
}

//-------------------------------------------------------------------
static void fselect_goto_next(int step) {
    register int j, i;
    struct fitem  *ptr;

    for (j=0; j<step; ++j) {
        for (i=0, ptr=top; i<BODY_LINES-1 && ptr; ++i, ptr=ptr->next);
        if (i==BODY_LINES-1 && ptr && ptr->prev==selected && ptr->next)
            top=top->next;
        if (selected->next) 
            selected=selected->next;
		else
		if (step == 1)
		{
			for(; top->prev; top = top->prev);
			selected = top;
		}
    }
}

//-------------------------------------------------------------------
static void fselect_marked_toggle() {
    if (selected && selected->attr != 0xFF && !(selected->attr & DOS_ATTR_DIRECTORY)) {
        selected->marked = !selected->marked;
    }
}

//-------------------------------------------------------------------
static void gui_fselect_marked_free_data() {
    struct fitem  *ptr = marked_head, *prev;

    while (ptr) {
        if (ptr->name)
            free(ptr->name);
        prev=ptr;
        ptr=ptr->next;
        free(prev);
    }
    marked_head=NULL;
    marked_count=0;
    marked_operation = MARKED_OP_NONE;
}

//-------------------------------------------------------------------
static void fselect_marked_copy_list() {
    gui_fselect_marked_free_data();

    struct fitem  *ptr, **marked_ptr=&marked_head, *prev = NULL;

    for (ptr=head; ptr; ptr=ptr->next) {
        if (ptr->marked) {
            *marked_ptr = malloc(sizeof(struct fitem));
            if (*marked_ptr) {
                (*marked_ptr)->n = ptr->n;
                (*marked_ptr)->name = malloc(strlen(ptr->name)+1);
                if ((*marked_ptr)->name)
                   strcpy((*marked_ptr)->name, ptr->name);
                (*marked_ptr)->attr=ptr->attr;
                (*marked_ptr)->size=ptr->size;
                (*marked_ptr)->mtime=ptr->mtime;
                (*marked_ptr)->marked=ptr->marked;
                (*marked_ptr)->prev=prev;
                prev=*marked_ptr;
                marked_ptr = &((*marked_ptr)->next);
                *marked_ptr=NULL;
                ++marked_count;
            }
        }
    }

    if (!marked_count)
        if (selected && selected->attr != 0xFF)
            if (!(selected->attr & DOS_ATTR_DIRECTORY)) {
                *marked_ptr = malloc(sizeof(struct fitem));
                if (*marked_ptr) {
                    (*marked_ptr)->n = selected->n;
                    (*marked_ptr)->name = malloc(strlen(selected->name)+1);
                    if ((*marked_ptr)->name)
                        strcpy((*marked_ptr)->name, selected->name);
                    (*marked_ptr)->attr=selected->attr;
                    (*marked_ptr)->size=selected->size;
                    (*marked_ptr)->mtime=selected->mtime;
                    (*marked_ptr)->marked=!(0);
                    (*marked_ptr)->prev=prev;
                    prev=*marked_ptr;
                    marked_ptr = &((*marked_ptr)->next);
                    *marked_ptr=NULL;
                    ++marked_count;
                }
            }

    sprintf(marked_dir, "%s", current_dir);
}

//-------------------------------------------------------------------
static void fselect_marked_paste_cb(unsigned int btn) {
    struct fitem  *ptr;
    int ss, sd, fsrc, fdst, i=0;
    register int *buf;
    unsigned char fend;
    static struct utimbuf t;

    if (btn != MBOX_BTN_YES) return;

    if (strcmp(marked_dir, current_dir) != 0) {
        buf = umalloc(MARKED_BUF_SIZE);
        if (buf) {
            for (ptr=marked_head; ptr; ptr=ptr->next) {
                if (ptr->attr != 0xFF && !(ptr->attr & DOS_ATTR_DIRECTORY)) {
                    started();
                    ++i;
                    if (marked_count)
                        gui_browser_progress_show(lang_str(LANG_FSELECT_PROGRESS_TITLE),i*100/marked_count);
                    sprintf(selected_file, "%s/%s", marked_dir, ptr->name);
                    fsrc = open(selected_file, O_RDONLY, 0777);
                    if (fsrc>=0) {
                        sprintf(selected_file, "%s/%s", current_dir, ptr->name);
                        // trying to open for read to check if file exists
                        fdst = open(selected_file, O_RDONLY, 0777);
                        if (fdst<0) {
                            fdst = open(selected_file, O_WRONLY|O_CREAT, 0777);
                            if (fdst>=0) {
                                do {
                                    ss=read(fsrc, buf, MARKED_BUF_SIZE);
                                    if (ss>0) sd=write(fdst, buf, ss);
                                } while (ss>0 && ss==sd);
                                close(fdst);
                                t.actime = t.modtime = ptr->mtime;
                                utime(selected_file, &t);
                                if (marked_operation == MARKED_OP_CUT && ss==0) {
                                    close(fsrc); fsrc = -1;
                                    sprintf(selected_file, "%s/%s", marked_dir, ptr->name);
                                    remove(selected_file);
                                }
                            }
                        } else {
                            close(fdst);
                        }
                        if (fsrc>=0) close(fsrc);
                    }
                    finished();
                    selected_file[0]=0;
                }
            }
            ufree(buf);
            if (marked_operation == MARKED_OP_CUT) {
                gui_fselect_marked_free_data();
            }
        }
        gui_fselect_read_dir(current_dir);
    }
    gui_fselect_redraw = 2;
}

//-------------------------------------------------------------------
static inline unsigned int fselect_real_marked_count() {
    struct fitem  *ptr;
    register unsigned int cnt=0;

    for (ptr=head; ptr; ptr=ptr->next) {
        if (ptr->attr != 0xFF && !(ptr->attr & DOS_ATTR_DIRECTORY) && ptr->marked) 
            ++cnt;
    }
    return cnt;
}
//-------------------------------------------------------------------
static unsigned int fselect_marked_count() {
    struct fitem  *ptr;
    register unsigned int cnt=fselect_real_marked_count();

    if (!cnt) {
        if (selected && selected->attr != 0xFF && !(selected->attr & DOS_ATTR_DIRECTORY)) 
            ++cnt;
    }

    return cnt;
}

//-------------------------------------------------------------------
static void fselect_marked_delete_cb(unsigned int btn) {
    struct fitem  *ptr;
    unsigned int del_cnt=0, cnt;

    if (btn != MBOX_BTN_YES) return;

    cnt=fselect_marked_count();
    for (ptr=head; ptr; ptr=ptr->next)
        if (ptr->marked && ptr->attr != 0xFF && !(ptr->attr & DOS_ATTR_DIRECTORY)) {
            started();
            ++del_cnt;
            if (cnt)
                gui_browser_progress_show(lang_str(LANG_FSELECT_PROGRESS_TITLE),del_cnt*100/cnt);
            sprintf(selected_file, "%s/%s", current_dir, ptr->name);
            remove(selected_file);
            finished();
            selected_file[0]=0;
        }

    if (del_cnt == 0 && selected) {
        started();
        sprintf(selected_file, "%s/%s", current_dir, selected->name);
        remove(selected_file);
        finished();
        selected_file[0]=0;
    }
    gui_fselect_read_dir(current_dir);
    gui_fselect_redraw = 2;
}

//-------------------------------------------------------------------
static void fselect_marked_inverse_selection() {
    struct fitem  *ptr;
    
    for (ptr=head; ptr; ptr=ptr->next)
        if (ptr->attr != 0xFF && !(ptr->attr & DOS_ATTR_DIRECTORY))
            ptr->marked = !ptr->marked;
    
    gui_fselect_redraw = 2;
}

//-------------------------------------------------------------------
void process_raw_files(void){
 struct fitem *ptr;
 if ((fselect_marked_count()>1) && raw_merge_start(raw_operation)) {
   for (ptr=head; ptr; ptr=ptr->next)
     if (ptr->marked && ptr->attr != 0xFF && !(ptr->attr & DOS_ATTR_DIRECTORY)) {
       sprintf(selected_file, "%s/%s", current_dir, ptr->name);
       raw_merge_add_file(selected_file);
      }
  raw_merge_end();
  gui_fselect_read_dir(current_dir);
 }
}

static void fselect_subtract_cb(unsigned int btn) {
    struct fitem *ptr;
    char *raw_subtract_from;
    char *raw_subtract_sub;
    char *raw_subtract_dest;
    if (btn != MBOX_BTN_YES) return;

    if(!(raw_subtract_from = malloc(300))) //3x full path
        return;
    raw_subtract_sub = raw_subtract_from + 100;
    raw_subtract_dest = raw_subtract_sub + 100;
    sprintf(raw_subtract_sub,"%s/%s",current_dir,selected->name);
    for (ptr=head; ptr; ptr=ptr->next) {
        if (ptr->marked && ptr->attr != 0xFF && 
            !(ptr->attr & DOS_ATTR_DIRECTORY) &&
            ptr->size == hook_raw_size() &&
            (strcmp(ptr->name,selected->name)) != 0) {
            sprintf(raw_subtract_from,"%s/%s",current_dir,ptr->name);
            sprintf(raw_subtract_dest,"%s/%s%s",current_dir,img_prefixes[conf.sub_batch_prefix],ptr->name+4);
            strcpy(raw_subtract_dest + strlen(raw_subtract_dest) - 4,img_exts[conf.sub_batch_ext]);
			// don't let users attempt to write one of the files being read
			if( strcmp(raw_subtract_dest,raw_subtract_from) != 0 && strcmp(raw_subtract_dest,raw_subtract_sub) != 0) {
                raw_subtract(raw_subtract_from,raw_subtract_sub,raw_subtract_dest);
			}
        }
    }
    free(raw_subtract_from);
    gui_fselect_read_dir(current_dir);
    gui_fselect_redraw = 2;
}


#define MAX_SUB_NAMES 6
static void setup_batch_subtract(void) {
    struct fitem *ptr;
    int i;
    char *p = buf + sprintf(buf,"%s %s\n",selected->name,lang_str(LANG_FSELECT_SUB_FROM));
    for (ptr=head, i=0; ptr; ptr=ptr->next) {
        if (ptr->marked && ptr->attr != 0xFF && !(ptr->attr & DOS_ATTR_DIRECTORY) && ptr->size == hook_raw_size()) {
            if ( i < MAX_SUB_NAMES ) {
                sprintf(p, "%s\n",ptr->name);
                // keep a pointer to the one before the end, so we can stick ...and more on
                if (i < MAX_SUB_NAMES - 1) {
                    p += strlen(p);
                }
            }
            i++;
        }
    }
    if (i > MAX_SUB_NAMES) {
//      "...%d more files"
        sprintf(p,lang_str(LANG_FSELECT_SUB_AND_MORE),i - (MAX_SUB_NAMES - 1));
    }
    gui_mbox_init(LANG_FSELECT_SUBTRACT, (int)buf,
                  MBOX_TEXT_CENTER|MBOX_BTN_YES_NO|MBOX_DEF_BTN2, fselect_subtract_cb);
}

//-------------------------------------------------------------------
static void fselect_mpopup_cb(unsigned int actn) {
    switch (actn) {
        case MPOPUP_CUT:
            fselect_marked_copy_list();
            marked_operation=MARKED_OP_CUT;
            break;
        case MPOPUP_COPY:
            fselect_marked_copy_list();
            marked_operation=MARKED_OP_COPY;
            break;
        case MPOPUP_PASTE:
            if (marked_operation == MARKED_OP_CUT) {
                sprintf(buf, lang_str(LANG_FSELECT_CUT_TEXT), marked_count, marked_dir);
                gui_mbox_init(LANG_FSELECT_CUT_TITLE, (int)buf,
                              MBOX_TEXT_CENTER|MBOX_BTN_YES_NO|MBOX_DEF_BTN2, fselect_marked_paste_cb);
            }
            else {
                sprintf(buf, lang_str(LANG_FSELECT_COPY_TEXT), marked_count, marked_dir);
                gui_mbox_init(LANG_FSELECT_COPY_TITLE, (int)buf,
                              MBOX_TEXT_CENTER|MBOX_BTN_YES_NO|MBOX_DEF_BTN2, fselect_marked_paste_cb);
            }
            break;
        case MPOPUP_DELETE:
            sprintf(buf, lang_str(LANG_FSELECT_DELETE_TEXT), fselect_marked_count());
            gui_mbox_init(LANG_FSELECT_DELETE_TITLE, (int)buf,
                          MBOX_TEXT_CENTER|MBOX_BTN_YES_NO|MBOX_DEF_BTN2, fselect_marked_delete_cb);
            break;
         case MPOPUP_PURGE:
           if (selected->name[0] == 'D' && selected->name[1] == 'C' && selected->name[2] == 'I' && selected->name[3] == 'M') {//If selected item is DCIM folder
               sprintf(buf, lang_str(LANG_FSELECT_PURGE_DCIM_TEXT), fselect_marked_count());
               gui_mbox_init(LANG_FSELECT_PURGE_TITLE, (int)buf,
                         MBOX_TEXT_CENTER|MBOX_BTN_YES_NO|MBOX_DEF_BTN2, fselect_purge_cb);
           }
           else if (selected->name[3] == 'C') {//If selected item is a Canon folder
               sprintf(buf, lang_str(LANG_FSELECT_PURGE_CANON_FOLDER_TEXT), fselect_marked_count());
               gui_mbox_init(LANG_FSELECT_PURGE_TITLE, (int)buf,
                         MBOX_TEXT_CENTER|MBOX_BTN_YES_NO|MBOX_DEF_BTN2, fselect_purge_cb);
           }
           else if (selected->name[9] == 'C' || selected->name[9] == 'T' || selected->name[9] == 'W' || selected->name[9] == 'J') {//If seleted item is a file produced by the camera 
               sprintf(buf, lang_str(LANG_FSELECT_PURGE_LIST_TEXT), fselect_marked_count());
               gui_mbox_init(LANG_FSELECT_PURGE_TITLE, (int)buf,
                         MBOX_TEXT_CENTER|MBOX_BTN_YES_NO|MBOX_DEF_BTN2, fselect_purge_cb);
           }
           else {
               sprintf(buf, lang_str(LANG_FSELECT_PURGE_DISABLED_TEXT), fselect_marked_count());
               gui_mbox_init(LANG_FSELECT_PURGE_TITLE, (int)buf,
                         MBOX_TEXT_CENTER|MBOX_BTN_OK|MBOX_DEF_BTN1, fselect_purge_cb);
           }
           break;
        case MPOPUP_SELINV:
            fselect_marked_inverse_selection();
            break;
        case MPOPUP_CANCEL:
            break;
	case MPOPUP_RAW_AVERAGE:
	    raw_operation=RAW_OPERATIOM_AVERAGE;
            process_raw_files();
            break;
        case MPOPUP_RAW_ADD:
            raw_operation=RAW_OPERATIOM_SUM;
            process_raw_files();
            break;
		case MPOPUP_RAW_DEVELOP:
            sprintf(buf, "%s/%s", current_dir, selected->name);
            gui_mbox_init((int)"", LANG_RAW_DEVELOP_MESSAGE, MBOX_BTN_OK|MBOX_TEXT_CENTER, NULL);
            raw_prepare_develop(buf);
		break;
        case MPOPUP_SUBTRACT:
        {
            setup_batch_subtract();
            break;
        }
    }
    gui_fselect_redraw = 2;
}

//-------------------------------------------------------------------
void gui_fselect_kbd_process() {
    int i;
    
    switch (kbd_get_autoclicked_key()) {
        case KEY_UP:
            if (selected) {
				if (kbd_is_key_pressed(KEY_SHOOT_HALF)) fselect_goto_prev(4);
                else fselect_goto_prev(1);
                gui_fselect_redraw = 1;
            }
            break;
        case KEY_DOWN:
            if (selected) {
                if (kbd_is_key_pressed(KEY_SHOOT_HALF)) fselect_goto_next(4);
				else fselect_goto_next(1);
                gui_fselect_redraw = 1;
            }
            break;
        case KEY_ZOOM_OUT:
            if (selected) {
                fselect_goto_prev(BODY_LINES-1);
                gui_fselect_redraw = 1;
            }
            break;
        case KEY_ZOOM_IN:
            if (selected) {
                fselect_goto_next(BODY_LINES-1);
                gui_fselect_redraw = 1;
            }
            break;
        case KEY_RIGHT:
            if (selected) {
                fselect_marked_toggle();
                fselect_goto_next(1);
                gui_fselect_redraw = 1;
            }
            break;
        case KEY_LEFT:
            if (selected && selected->attr != 0xFF) {
                i=MPOPUP_CUT|MPOPUP_COPY|MPOPUP_SELINV|MPOPUP_RAW_ADD|MPOPUP_RAW_AVERAGE;
                if (fselect_marked_count() > 0) {
                    i |= MPOPUP_DELETE;
                    // doesn't make sense to subtract from itself!
                    if( selected->marked == 0 && fselect_real_marked_count() > 0)
                        i |= MPOPUP_SUBTRACT;
                }
                if (marked_operation == MARKED_OP_CUT || marked_operation == MARKED_OP_COPY)
                    i |= MPOPUP_PASTE;
                if (!(selected->attr & DOS_ATTR_DIRECTORY) || !(selected->name[0] == '.' && selected->name[1] == '.' && selected->name[2] == 0) ||//If item is not a folder or UpDir
                     (selected->name[0] == 'D' && selected->name[1] == 'C' && selected->name[2] == 'I' && selected->name[3] == 'M') ||//If item is DCIM folder
                     (selected->name[3] == 'C'))//If item is a DCIM sub folder
                    i |= MPOPUP_PURGE;//Display PURGE RAW function in popup menu
                if(selected->size == hook_raw_size())
                    i |= MPOPUP_RAW_DEVELOP;
                gui_mpopup_init(i, fselect_mpopup_cb);
            }
            break;
        case KEY_SET:
            if (selected && selected->attr != 0xFF) {
                if (selected->attr & DOS_ATTR_DIRECTORY) {
                    i=strlen(current_dir);
                    if (selected->name[0]=='.' && selected->name[1]=='.' && selected->name[2]==0) {
                        while (current_dir[--i] != '/');
                        current_dir[i]=0;
                    } else {
                        sprintf(current_dir+i, "/%s", selected->name);
                    }
                    gui_fselect_read_dir(current_dir);
                    gui_fselect_redraw = 1;
                } else  {
                    sprintf(selected_file, "%s/%s", current_dir, selected->name);
                    gui_fselect_free_data();
                    gui_fselect_marked_free_data();
                    gui_set_mode(gui_fselect_mode_old);
                    draw_restore();
                    if (fselect_on_select) 
                        fselect_on_select(selected_file);
                }
            }
            break;
      #if CAM_HAS_ERASE_BUTTON
        case KEY_ERASE:
      #else
        case KEY_DISPLAY:
      #endif
            if (selected && selected->attr != 0xFF) {
                if (selected->attr & DOS_ATTR_DIRECTORY) {
                    if (selected->name[0]!='.' || selected->name[1]!='.' || selected->name[2]!=0)
                        gui_mbox_init(LANG_BROWSER_ERASE_DIR_TITLE, LANG_BROWSER_ERASE_DIR_TEXT,
                                      MBOX_TEXT_CENTER|MBOX_BTN_YES_NO|MBOX_DEF_BTN2, fselect_delete_folder_cb);
                } else {
                    gui_mbox_init(LANG_BROWSER_DELETE_FILE_TITLE, LANG_BROWSER_DELETE_FILE_TEXT,
                                  MBOX_TEXT_CENTER|MBOX_BTN_YES_NO|MBOX_DEF_BTN2, fselect_delete_file_cb);
                }
            }
            break;
        case KEY_MENU:
            gui_fselect_free_data();
            gui_fselect_marked_free_data();
            gui_set_mode(gui_fselect_mode_old);
            draw_restore();
            if (fselect_on_select) 
                fselect_on_select(NULL);
            break;
    }
}

//-------------------------------------------------------------------
