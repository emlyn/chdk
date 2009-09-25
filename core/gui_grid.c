#include "stdlib.h"
#include "keyboard.h"
#include "platform.h"
#include "core.h"
#include "conf.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_grid.h"


//-------------------------------------------------------------------
#define GRID_BUF_SIZE               0x1000
#define GRID_REDRAW_INTERVAL        4

//-------------------------------------------------------------------
typedef enum {
    GRID_ELEM_LINE,
    GRID_ELEM_RECT,
    GRID_ELEM_FILLED_RECT,
    GRID_ELEM_ELLIPSE,
    GRID_ELEM_FILLED_ELLIPSE,
} grid_elem_type;

struct gline {
    grid_elem_type      type;
    coord               x0,y0,x1,y1;
    color               clf, clb;
    struct gline        *next;
};

char grid_title[36];

static int interval = GRID_REDRAW_INTERVAL;
static struct gline *head=NULL, *top=NULL;
static const char *grid_default =
    "@title Default grid\n"
    "@line 0,79,359,79,17\n"
    "@line 0,160,359,160,17\n";

//-------------------------------------------------------------------
static void grid_lines_free_data() {
    struct gline  *ptr = head, *prev;

    while (ptr) {
        prev=ptr;
        ptr=ptr->next;
        free(prev);
    }
    head=top=NULL;
}

//-------------------------------------------------------------------
static void process_title(const char *title) {
    register const char *ptr = title;
    register int i=0;

    while (ptr[0]==' ' || ptr[0]=='\t') ++ptr; // whitespaces
    while (i<(sizeof(grid_title)-1) && ptr[i] && ptr[i]!='\r' && ptr[i]!='\n') {
        grid_title[i]=ptr[i];
        ++i;
    }
    grid_title[i]=0;
}

//-------------------------------------------------------------------
static void process_element(const char *str, int n, grid_elem_type type) {
    register const char *ptr = str;
    char *nptr;
    register int i;
    long nums[6];
    struct gline  *gptr;

    for (i=0; i<(sizeof(nums)/sizeof(nums[0])) && i<n; ++i) {
        while (ptr[0]==' ' || ptr[0]=='\t' || ptr[0]==',') ++ptr; // whitespaces
        nums[i] = strtol(ptr, &nptr, 0);
        if (nptr == ptr) { // error
            return;
        } else {
            ptr = nptr;
        }
    }

    gptr = malloc(sizeof(struct gline));
    
   
    if (gptr) {
      gptr->type=type;
      #if CAM_USES_ASPECT_CORRECTION //nandoide sep-2009
        gptr->x0=ASPECT_GRID_XCORRECTION(nums[0]);  gptr->y0=ASPECT_GRID_YCORRECTION(nums[1]);
        gptr->x1=ASPECT_GRID_XCORRECTION(nums[2]);  gptr->y1=ASPECT_GRID_YCORRECTION(nums[3]);
      #else
        gptr->x0=nums[0];  gptr->y0=nums[1];
        gptr->x1=nums[2];  gptr->y1=nums[3];
      #endif
      gptr->clf=nums[4]; gptr->clb=nums[5];
      if (!head) head=gptr;
      if (top) top->next=gptr;
      gptr->next=NULL;
      top=gptr;
    }
}

//-------------------------------------------------------------------
static void parse_grid_file(const char *fn, const char *ptr) {
    char *c;

    c=strrchr(fn, '/');
    strncpy(grid_title, (c)?c+1:fn, sizeof(grid_title));
    grid_title[sizeof(grid_title)-1]=0;

    while (ptr[0]) {
        while (ptr[0]==' ' || ptr[0]=='\t') ++ptr; // whitespaces
        if (ptr[0]=='@') {
            if (strncmp("@title", ptr, 6)==0) {
                ptr+=6;
                process_title(ptr);
            } else if (strncmp("@line", ptr, 5)==0) {
                ptr+=5;
                process_element(ptr, 5, GRID_ELEM_LINE);
            } else if (strncmp("@rectf", ptr, 6)==0) {
                ptr+=6;
                process_element(ptr, 6, GRID_ELEM_FILLED_RECT);
            } else if (strncmp("@rect", ptr, 5)==0) {
                ptr+=5;
                process_element(ptr, 5, GRID_ELEM_RECT);
            } else if (strncmp("@elpsf", ptr, 6)==0) {
                ptr+=6;
                process_element(ptr, 5, GRID_ELEM_FILLED_ELLIPSE);
            } else if (strncmp("@elps", ptr, 5)==0) {
                ptr+=5;
                process_element(ptr, 5, GRID_ELEM_ELLIPSE);
            }
        }
        while (ptr[0] && ptr[0]!='\n') ++ptr; // unless end of line
        if (ptr[0]) ++ptr;
    }
}

//-------------------------------------------------------------------
void grid_lines_load(const char *fn) {
    char *buf;
    const char *grid;
    int fd;

    if (fn[0]) {
        buf = umalloc(GRID_BUF_SIZE);
        if (!buf) return;

        grid = grid_default;
        fd = open(fn, O_RDONLY, 0777);
        if (fd>=0) {
            int rcnt = read(fd, buf, GRID_BUF_SIZE);
            if (rcnt > 0) {
                if (rcnt == GRID_BUF_SIZE) 
        	    buf[GRID_BUF_SIZE-1] = 0;
                else
        	    buf[rcnt] = 0;
                grid = buf;
            }
            close(fd);
            strcpy(conf.grid_lines_file, fn);
        } else {
            conf.grid_lines_file[0] = 0;
        }

        grid_lines_free_data();
        parse_grid_file(fn, grid);
    
        ufree(buf);
    }
}

//-------------------------------------------------------------------
void gui_grid_draw_osd(int force) {
    struct gline  *ptr;

    if (force || --interval==0) {
        for (ptr=head; ptr; ptr=ptr->next) {
            switch (ptr->type) {
                case GRID_ELEM_LINE:
                    draw_line(ptr->x0, ptr->y0, ptr->x1, ptr->y1, (conf.grid_force_color)?conf.grid_color:ptr->clf);
                    break;
                case GRID_ELEM_RECT:
                    draw_rect(ptr->x0, ptr->y0, ptr->x1, ptr->y1, (conf.grid_force_color)?conf.grid_color:ptr->clf);
                    break;
                case GRID_ELEM_FILLED_RECT:
                    draw_filled_rect(ptr->x0, ptr->y0, ptr->x1, ptr->y1, (conf.grid_force_color)?conf.grid_color:MAKE_COLOR(ptr->clb, ptr->clf));
                    break;
                case GRID_ELEM_ELLIPSE:
                    draw_ellipse(ptr->x0, ptr->y0, (unsigned int)(ptr->x1), (unsigned int)(ptr->y1), (conf.grid_force_color)?conf.grid_color:ptr->clf);
                    break;
                case GRID_ELEM_FILLED_ELLIPSE:
                    draw_filled_ellipse(ptr->x0, ptr->y0, (unsigned int)(ptr->x1), (unsigned int)(ptr->y1), (conf.grid_force_color)?conf.grid_color:MAKE_COLOR(ptr->clf, 0));
                    break;
            }
        }
        interval = GRID_REDRAW_INTERVAL;
    }
}

//-------------------------------------------------------------------
