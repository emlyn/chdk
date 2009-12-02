/*
 * Copyright (c) 2006, Adam Dunkels
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the author nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#if DEBUG
#define DEBUG_PRINTF(...)  printf(__VA_ARGS__)
#else
#define DEBUG_PRINTF(...)
#endif

#ifdef UBASIC_TEST
#include <string.h>
#include <ctype.h>
#endif

#include "tokenizer.h"
#include "stdlib.h"

static char const *ptr, *nextptr;

#define MAX_NUMLEN 6

struct keyword_token {
  const char *keyword;
  int token;
};

static ubasic_token current_token = TOKENIZER_ERROR;
static int current_line = 0;

static const struct keyword_token keywords[] = {
  {"<>",          			  TOKENIZER_NE},
  {"<=",          			  TOKENIZER_LE},
  {">=",          			  TOKENIZER_GE},
  {"<",             		  TOKENIZER_LT},
  {">",                       TOKENIZER_GT},
  {"not",                     TOKENIZER_LNOT},
  {"or",                      TOKENIZER_LOR},
  {"and",                     TOKENIZER_LAND},

  {"let",                     TOKENIZER_LET},
  {"if",                      TOKENIZER_IF},
  {"then",                    TOKENIZER_THEN},
  {"else",                    TOKENIZER_ELSE},
  {"endif",                   TOKENIZER_ENDIF},
  {"select",                  TOKENIZER_SELECT},
  {"case_else",               TOKENIZER_CASE_ELSE},
  {"case",                    TOKENIZER_CASE},
  {"end_select",              TOKENIZER_END_SELECT},
  {"for",                     TOKENIZER_FOR},
  {"to",                      TOKENIZER_TO},
  {"next",                    TOKENIZER_NEXT},
  {"step",                    TOKENIZER_STEP},
  {"do",                      TOKENIZER_DO},
  {"until",                   TOKENIZER_UNTIL},
  {"while",                   TOKENIZER_WHILE},
  {"wend",                    TOKENIZER_WEND},
  {"goto",                    TOKENIZER_GOTO},
  {"gosub",                   TOKENIZER_GOSUB},
  {"return",                  TOKENIZER_RETURN},
  {"call",                    TOKENIZER_CALL},
  {"rem",                     TOKENIZER_REM},
  {"cls",                     TOKENIZER_CLS},
  {"print_screen",            TOKENIZER_PRINT_SCREEN},
  {"print",                   TOKENIZER_PRINT},
  {"random",                  TOKENIZER_RANDOM},
  {"click",                   TOKENIZER_CLICK},
  {"playsound",                   TOKENIZER_PLAY_SOUND},
  {"press",                   TOKENIZER_PRESS},
  {"release",                 TOKENIZER_RELEASE},
  //{"shot",                    TOKENIZER_SHOOT}, // for compatibility
  {"shoot",                   TOKENIZER_SHOOT},
  {"sleep",                   TOKENIZER_SLEEP}, 

  /* WARNING due to tokenizer limitation longest match must be first */
// GET  
  {"get_av96",                TOKENIZER_GET_AV96},
  {"get_av",                  TOKENIZER_GET_USER_AV_ID}, //FOR COMPATIBILITY
  {"get_bv96",                TOKENIZER_GET_BV96},
  {"get_capture_mode",        TOKENIZER_GET_CAPTURE_MODE},
  {"get_display_mode",        TOKENIZER_GET_DISPLAY_MODE},
  {"get_day_seconds",         TOKENIZER_GET_DAY_SECONDS},
  {"get_disk_size",           TOKENIZER_GET_DISK_SIZE},
  {"get_dof",                 TOKENIZER_GET_DOF},
  {"get_far_limit",           TOKENIZER_GET_FAR_LIMIT},
  {"get_free_disk_space",     TOKENIZER_GET_FREE_DISK_SPACE},
  {"get_focus_mode",          TOKENIZER_GET_FOCUS_MODE},
  {"get_focus",               TOKENIZER_GET_FOCUS},
  {"get_hyp_dist",            TOKENIZER_GET_HYPERFOCAL_DIST},
  {"get_iso_market",          TOKENIZER_GET_ISO_MARKET},
  {"get_iso_mode",            TOKENIZER_GET_ISO_MODE},
  {"get_iso_real",            TOKENIZER_GET_ISO_REAL},
  {"get_iso",                 TOKENIZER_GET_ISO_MODE}, //FOR COMPATIBILITY
  {"get_jpg_count",           TOKENIZER_GET_JPG_COUNT},
  {"get_movie_status",        TOKENIZER_GET_MOVIE_STATUS},
  {"get_mode",				        TOKENIZER_GET_MODE},  // Returns 0 in recordmode, 1 in playmode
  {"get_near_limit",          TOKENIZER_GET_NEAR_LIMIT},
  {"get_platform_id",          TOKENIZER_GET_PLATFORM_ID},
  {"get_propset",             TOKENIZER_GET_PROPSET},
  {"get_prop",                TOKENIZER_GET_PROP},
  {"get_quality",             TOKENIZER_GET_QUALITY},
  {"get_raw_count",           TOKENIZER_GET_RAW_COUNT},
  {"get_raw_nr",              TOKENIZER_GET_RAW_NR},
  {"get_raw",                 TOKENIZER_GET_RAW},
  {"get_resolution",          TOKENIZER_GET_RESOLUTION},
  {"get_sv96",	              TOKENIZER_GET_SV96},
  {"get_temperature",         TOKENIZER_GET_TEMPERATURE},
  {"get_tick_count",          TOKENIZER_GET_TICK_COUNT},
  {"get_time",          			TOKENIZER_GET_TIME},
  {"get_tv96",                TOKENIZER_GET_TV96},
  {"get_user_av_id",          TOKENIZER_GET_USER_AV_ID},
  {"get_user_av96",           TOKENIZER_GET_USER_AV96},
  {"get_user_tv_id",          TOKENIZER_GET_USER_TV_ID},
  {"get_user_tv96",           TOKENIZER_GET_USER_TV96},
  {"get_video_button",        TOKENIZER_GET_VIDEO_BUTTON},
  {"get_vbatt",               TOKENIZER_GET_VBATT},  
  {"get_zoom_steps",          TOKENIZER_GET_ZOOM_STEPS},
  {"get_zoom",                TOKENIZER_GET_ZOOM},
  {"get_exp_count",           TOKENIZER_GET_EXP_COUNT},



//SET  
  {"set_av96_direct",         TOKENIZER_SET_AV96_DIRECT},
  {"set_av_rel",              TOKENIZER_SET_USER_AV_BY_ID_REL}, //FOR COMPATIBILITY
  {"set_av96",                TOKENIZER_SET_AV96},
  {"set_av",                  TOKENIZER_SET_USER_AV_BY_ID}, //FOR COMPATIBILITY
  {"set_backlight",           TOKENIZER_SET_BACKLIGHT},
  {"set_capture_mode_canon",  TOKENIZER_SET_CAPTURE_MODE_CANON},
  {"set_capture_mode",        TOKENIZER_SET_CAPTURE_MODE},
  {"set_focus",               TOKENIZER_SET_FOCUS},
  {"set_iso_mode",            TOKENIZER_SET_ISO_MODE},
  {"set_iso_real",            TOKENIZER_SET_ISO_REAL},
  {"set_iso",                 TOKENIZER_SET_ISO_MODE}, //FOR COMPATIBILITY
  {"set_led",                 TOKENIZER_SET_LED},
  {"set_movie_status",        TOKENIZER_SET_MOVIE_STATUS},  
  {"set_nd_filter",           TOKENIZER_SET_ND_FILTER},
  {"set_prop",                TOKENIZER_SET_PROP},
  {"set_quality",                TOKENIZER_SET_QUALITY},
  {"set_raw_nr",              TOKENIZER_SET_RAW_NR},
  {"set_raw",                 TOKENIZER_SET_RAW},
  {"set_resolution",          TOKENIZER_SET_RESOLUTION},
    //{"set_shutter_speed",       TOKENIZER_SET_SHUTTER_SPEED},
  {"set_sv96",		          TOKENIZER_SET_SV96},
  {"set_tv96_direct",         TOKENIZER_SET_TV96_DIRECT},
  {"set_tv_rel",              TOKENIZER_SET_USER_TV_BY_ID_REL}, //FOR COMPATIBILITY
  {"set_tv96",                TOKENIZER_SET_TV96},
  {"set_tv",                  TOKENIZER_SET_USER_TV_BY_ID}, //FOR COMPATIBILITY
  {"set_user_av_by_id_rel",   TOKENIZER_SET_USER_AV_BY_ID_REL},
  {"set_user_av_by_id",       TOKENIZER_SET_USER_AV_BY_ID},
  {"set_user_av96",           TOKENIZER_SET_USER_AV96},
  {"set_user_tv_by_id_rel",   TOKENIZER_SET_USER_TV_BY_ID_REL},
  {"set_user_tv_by_id",       TOKENIZER_SET_USER_TV_BY_ID},
  {"set_user_tv96",           TOKENIZER_SET_USER_TV96},
  {"set_zoom_speed",          TOKENIZER_SET_ZOOM_SPEED},
  {"set_zoom_rel",            TOKENIZER_SET_ZOOM_REL},
  {"set_zoom",                TOKENIZER_SET_ZOOM},
  {"set_record",              TOKENIZER_SET_RECORD},
  
  
  {"wait_click",              TOKENIZER_WAIT_CLICK},
  {"is_pressed",              TOKENIZER_IS_PRESSED},
  {"is_key",                  TOKENIZER_IS_KEY},
  
  {"wheel_right",             TOKENIZER_WHEEL_RIGHT},
  {"wheel_left",              TOKENIZER_WHEEL_LEFT},
  
  {"@title",                  TOKENIZER_REM},
  {"@param",                  TOKENIZER_REM},
  {"@default",                TOKENIZER_REM},

  {"md_detect_motion",        TOKENIZER_MD_DETECT_MOTION},
  {"md_get_cell_diff",        TOKENIZER_MD_GET_CELL_DIFF},
  {"autostarted",             TOKENIZER_SCRIPT_AUTOSTARTED},
  {"get_autostart",           TOKENIZER_GET_SCRIPT_AUTOSTART},
  {"set_autostart",           TOKENIZER_SET_SCRIPT_AUTOSTART},
  {"get_usb_power",           TOKENIZER_GET_USB_POWER},
  {"exit_alt",                TOKENIZER_EXIT_ALT},
  {"shut_down",               TOKENIZER_SHUT_DOWN},

  {"get_shooting",            TOKENIZER_GET_SHOOTING},
  {"get_drive_mode",          TOKENIZER_GET_DRIVE_MODE},
  {"get_flash_mode",          TOKENIZER_GET_FLASH_MODE},
  {"get_flash_ready",         TOKENIZER_GET_FLASH_READY},
  {"get_IS_mode",             TOKENIZER_GET_IS_MODE},
  {"set_ev",                  TOKENIZER_SET_EV},
  {"get_ev",                  TOKENIZER_GET_EV},
  {"get_orientation_sensor",  TOKENIZER_GET_ORIENTATION_SENSOR},
  {"get_nd_present",          TOKENIZER_GET_ND_PRESENT},
  {"get_histo_range",         TOKENIZER_GET_HISTO_RANGE},
   {"shot_histo_enable",       TOKENIZER_SHOT_HISTO_ENABLE},
   {"set_aflock",            TOKENIZER_SET_AFLOCK},
  {"is_capture_mode_valid",  TOKENIZER_IS_CAPTURE_MODE_VALID},
  
  {"end",                     TOKENIZER_END},

  {NULL,                      TOKENIZER_ERROR}
};

/*---------------------------------------------------------------------------*/
static int
singlechar(void)
{
  if(*ptr == '\n') {
    return TOKENIZER_CR;
  } else if(*ptr == ',') {
    return TOKENIZER_COMMA;
  } else if(*ptr == ';') {
    return TOKENIZER_SEMICOLON;
  } else if(*ptr == '+') {
    return TOKENIZER_PLUS;
  } else if(*ptr == '-') {
    return TOKENIZER_MINUS;
  } else if(*ptr == '&') {
    return TOKENIZER_AND;
  } else if(*ptr == '|') {
    return TOKENIZER_OR;
  } else if(*ptr == '^') {
    return TOKENIZER_XOR;
  } else if(*ptr == '*') {
    return TOKENIZER_ASTR;
  } else if(*ptr == '/') {
    return TOKENIZER_SLASH;
  } else if(*ptr == '%') {
    return TOKENIZER_MOD;
  } else if(*ptr == '(') {
    return TOKENIZER_LEFTPAREN;
  } else if(*ptr == ')') {
    return TOKENIZER_RIGHTPAREN;
  } else if(*ptr == '=') {
    return TOKENIZER_EQ;
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
static int
get_next_token(void)
{
  struct keyword_token const *kt;
  int i;

  DEBUG_PRINTF("get_next_token(): '%s'\n", ptr);

  // eat all whitespace
  while(*ptr == ' ' || *ptr == '\t' || *ptr == '\r') ptr++;

  if(*ptr == 0) {
    return TOKENIZER_ENDOFINPUT;
  }
  
  if(isdigit(*ptr)) {
    for(i = 0; i < (MAX_NUMLEN+1); ++i) {
      if(!isdigit(ptr[i])) {
	if(i > 0) {
	  nextptr = ptr + i;
	  return TOKENIZER_NUMBER;
	} else {
	  DEBUG_PRINTF("get_next_token: error due to too short number\n");
	  return TOKENIZER_ERROR;
	}
      }
      if(!isdigit(ptr[i])) {
	DEBUG_PRINTF("get_next_token: error due to malformed number\n");
	return TOKENIZER_ERROR;
      }
    }
    DEBUG_PRINTF("get_next_token: error due to too long number\n");
    return TOKENIZER_ERROR;
  } else if(*ptr == ':') {
    // label
    nextptr = ptr;
    do {
      ++nextptr;
    } while(*nextptr != ' ' && *nextptr != '\r' && *nextptr != '\n' && *nextptr != '\t');
    return TOKENIZER_LABEL;
  } else if((i=singlechar()) != 0) {
    if (i == TOKENIZER_CR){
      // move to next line, and skip all following empty lines as well
      while (singlechar() == TOKENIZER_CR) 
      {
        current_line++;
        ptr++;
        // eat all whitespace
        while(*ptr == ' ' || *ptr == '\t' || *ptr == '\r') ptr++;
      };
      ptr--;
      // dangelo: now the last char might point to a whitespace instead of
      // a CR. I hope that doesn't break anything.
    }
    nextptr = ptr + 1;
    return i;
  } else if(*ptr == '"') {
    nextptr = ptr;
    do {
      ++nextptr;
    } while(*nextptr != '"');
    ++nextptr;
    return TOKENIZER_STRING;
  } else {
    for(kt = keywords; kt->keyword != NULL; ++kt) {
      if(strncmp(ptr, kt->keyword, strlen(kt->keyword)) == 0) {
	nextptr = ptr + strlen(kt->keyword);
        if (kt->token == TOKENIZER_REM) {
           while(*nextptr != 0 && *nextptr != '\r' && *nextptr != '\n') ++nextptr;
        }
	return kt->token;
      }
    }
  }

  if((*ptr >= 'a' && *ptr <= 'z') || (*ptr >= 'A' && *ptr <= 'Z')) {
    nextptr = ptr + 1;
    return TOKENIZER_VARIABLE;
  }

  
  return TOKENIZER_ERROR;
}
/*---------------------------------------------------------------------------*/
void
tokenizer_init(const char *program)
{
  ptr = program;
  current_line = 1;
  current_token = get_next_token();
}
/*---------------------------------------------------------------------------*/
int
tokenizer_token(void)
{
  return current_token;
}
/*---------------------------------------------------------------------------*/
void
tokenizer_next(void)
{

  if(tokenizer_finished()) {
    return;
  }

  DEBUG_PRINTF("tokenizer_next: %p\n", nextptr);
  ptr = nextptr;
  while((*ptr == ' ') || (*ptr == '\t')) {
    ++ptr;
  }
  current_token = get_next_token();
  DEBUG_PRINTF("tokenizer_next: '%s' %d\n", ptr, current_token);
  return;
}
/*---------------------------------------------------------------------------*/
int
tokenizer_num(void)
{
  return atoi(ptr);
}
/*---------------------------------------------------------------------------*/
void
tokenizer_string(char *dest, int len)
{
  char *string_end;
  int string_len;
  
  if(tokenizer_token() != TOKENIZER_STRING) {
    return;
  }
  string_end = strchr(ptr + 1, '"');
  if(string_end == NULL) {
    return;
  }
  string_len = string_end - ptr - 1;
  if(len < string_len) {
    string_len = len;
  }
  memcpy(dest, ptr + 1, string_len);
  dest[string_len] = 0;
}
/*---------------------------------------------------------------------------*/
void
tokenizer_label(char *dest, int len)
{
  char *string_end;
  int string_len;
  
  if(tokenizer_token() != TOKENIZER_LABEL) {
    return;
  }
  // allow string \r, \n, tabulation and space to end labels
  string_end = strpbrk(ptr + 1, " \t\r\n");

  if(string_end == NULL) {
    return;
  }
  string_len = string_end - ptr - 1;
  if(len < string_len) {
    string_len = len;
  }
  memcpy(dest, ptr + 1, string_len);
  dest[string_len] = 0;
}
/*---------------------------------------------------------------------------*/
void
tokenizer_error_print(void)
{
  DEBUG_PRINTF("tokenizer_error_print: '%s'\n", ptr);
}
/*---------------------------------------------------------------------------*/
int
tokenizer_finished(void)
{
  return *ptr == 0 || current_token == TOKENIZER_ENDOFINPUT;
}
/*---------------------------------------------------------------------------*/
int
tokenizer_variable_num(void)
{
  return *ptr - (*ptr>='a'?'a':('A'-26));
}
/*---------------------------------------------------------------------------*/
int tokenizer_line_number(void)
{
  return current_line;
}
