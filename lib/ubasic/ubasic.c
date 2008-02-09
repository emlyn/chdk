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

#ifdef TEST
#include "../../include/ubasic.h"
#include "../../include/platform.h"
#include "../../include/script.h"
#include <string.h>
#include <fcntl.h>
#include <io.h>
#else
#include "ubasic.h"
#include "platform.h"
#include "script.h"
#endif
#include "tokenizer.h"

#include "camera_functions.h"

#include "stdlib.h" /* exit() */

#ifdef DEBUG
#include <stdio.h>
#endif

static char const *program_ptr;
#define MAX_STRINGLEN 40
static char string[MAX_STRINGLEN];

#define MAX_GOSUB_STACK_DEPTH 10
static short gosub_stack[MAX_GOSUB_STACK_DEPTH];
static int gosub_stack_ptr;

#define MAX_IF_STACK_DEPTH 4
static short if_stack[MAX_IF_STACK_DEPTH];
static int if_stack_ptr;

#define MAX_WHILE_STACK_DEPTH 4
static short while_stack[MAX_WHILE_STACK_DEPTH];
static int while_stack_ptr;

#define MAX_DO_STACK_DEPTH 4
static short do_stack[MAX_DO_STACK_DEPTH];
static int do_stack_ptr;

struct for_state {
  short line_after_for;
  short for_variable;
  int to;
  int step;
};
#define MAX_FOR_STACK_DEPTH 4
static struct for_state for_stack[MAX_FOR_STACK_DEPTH];
static int for_stack_ptr;

#define MAX_VARNUM 52
static int variables[MAX_VARNUM];

static int  print_screen_p;             // print_screen predicate: 0-off 1-on.
static int  print_screen_d = -1;        // print_screen file descriptor.
static const char print_screen_file[] ="A/CHDK/SCRIPTS/PR_SCREEN.TXT";

static int ended;

static int expr(void);
static void line_statement(void);
static void statement(void);
static int relation(void);

int ubasic_error;
const char *ubasic_errstrings[UBASIC_E_ENDMARK] = 
{
    "No err",
    "Parse err",
    "Unk stmt",
    "Unk key",
    "Unk label",
    "Stack ful",
    "bad return",
    "Unk err" 
};

/*---------------------------------------------------------------------------*/
int
ubasic_linenumber()
{
  return tokenizer_line_number();
}

/*---------------------------------------------------------------------------*/
void
ubasic_init(const char *program)
{
  program_ptr = program;
  for_stack_ptr = gosub_stack_ptr = while_stack_ptr = do_stack_ptr = if_stack_ptr = 0;
  tokenizer_init(program);
  ended = 0;
  print_screen_p = 0;
  if (print_screen_d >= 0) {
    close(print_screen_d);
    print_screen_d = -1;
  }
  ubasic_error = UBASIC_E_NONE;
}
/*---------------------------------------------------------------------------*/
static void
accept(int token)
{
  if(token != tokenizer_token()) {
    DEBUG_PRINTF("Token not what was expected (expected %d, got %d)\n",
		 token, tokenizer_token());
    tokenizer_error_print();
     tokenizer_next();
     ended = 1;
     ubasic_error = UBASIC_E_PARSE;
     return;
  }
  DEBUG_PRINTF("Expected %d, got it\n", token);
  tokenizer_next();
}
/*---------------------------------------------------------------------------*/
static void
accept_cr()
{
    while(tokenizer_token() != TOKENIZER_CR &&
	    tokenizer_token() != TOKENIZER_ENDOFINPUT)
      tokenizer_next();
    accept(TOKENIZER_CR);
}
/*---------------------------------------------------------------------------*/
static int
varfactor(void)
{
  int r;
  DEBUG_PRINTF("varfactor: obtaining %d from variable %d\n", variables[tokenizer_variable_num()], tokenizer_variable_num());
  r = ubasic_get_variable(tokenizer_variable_num());
  accept(TOKENIZER_VARIABLE);
  return r;
}
/*---------------------------------------------------------------------------*/
static int
factor(void)
{
  int r;

  DEBUG_PRINTF("factor: token %d\n", tokenizer_token());
  switch(tokenizer_token()) {
  case TOKENIZER_NUMBER:
    r = tokenizer_num();
    DEBUG_PRINTF("factor: number %d\n", r);
    accept(TOKENIZER_NUMBER);
    break;
  case TOKENIZER_LEFTPAREN:
    accept(TOKENIZER_LEFTPAREN);
    r = relation();
    accept(TOKENIZER_RIGHTPAREN);
    break;
  case TOKENIZER_PLUS:
    accept(TOKENIZER_PLUS);
    r = factor();
    break;
  case TOKENIZER_MINUS:
    accept(TOKENIZER_MINUS);
    r = - factor();
    break;
  case TOKENIZER_LNOT:
    accept(TOKENIZER_LNOT);
    r = ! relation();
    break;
case TOKENIZER_GET_VBATT:
    accept(TOKENIZER_GET_VBATT);
    r = (unsigned short) stat_get_vbatt();     
    break;
 case TOKENIZER_GET_DAY_SECONDS:
    accept(TOKENIZER_GET_DAY_SECONDS);
    r = shooting_get_day_seconds();     
    break;
 case TOKENIZER_GET_TICK_COUNT:
    accept(TOKENIZER_GET_TICK_COUNT);
    r = shooting_get_tick_count();     
   break;
 case TOKENIZER_GET_RAW_NR:
    accept(TOKENIZER_GET_RAW_NR);
    r = ubasic_camera_get_nr();     
    break;
 case TOKENIZER_IS_KEY:
    accept(TOKENIZER_IS_KEY);
    tokenizer_string(string, sizeof(string));
    tokenizer_next();
    r = ubasic_camera_is_clicked(string);     
    break;
case TOKENIZER_SCRIPT_AUTOSTART:
    accept(TOKENIZER_SCRIPT_AUTOSTART);
    r = ubasic_camera_script_autostart();     
    break;
 case TOKENIZER_GET_USB_POWER:
    accept(TOKENIZER_GET_USB_POWER);
    r = get_usb_power(0);     
    break;

  default:
    r = varfactor();
    break;
  }
  return r;
}
/*---------------------------------------------------------------------------*/
static int
term(void)
{
  int f1, f2;
  int op;

  f1 = factor();
  op = tokenizer_token();
  DEBUG_PRINTF("term: token %d\n", op);
  while(op == TOKENIZER_ASTR ||
	op == TOKENIZER_SLASH ||
	op == TOKENIZER_LT ||
	op == TOKENIZER_GT ||
	op == TOKENIZER_GE ||
	op == TOKENIZER_LE ||
	op == TOKENIZER_NE ||
	op == TOKENIZER_EQ ||
	op == TOKENIZER_XOR || 
        op == TOKENIZER_OR ||
	op == TOKENIZER_MOD) {
    tokenizer_next();
    f2 = factor();
    DEBUG_PRINTF("term: %d %d %d\n", f1, op, f2);
    switch(op) {
    case TOKENIZER_ASTR:
      f1 = f1 * f2;
      break;
    case TOKENIZER_SLASH:
      f1 = f1 / f2;
      break;
    case TOKENIZER_MOD:
      f1 = f1 % f2;
      break;
    case TOKENIZER_LT:
      f1 = f1 < f2;
      break;
    case TOKENIZER_GT:
      f1 = f1 > f2;
      break;
    case TOKENIZER_EQ:
      f1 = f1 == f2;
      break;
    case TOKENIZER_NE:
      f1 = f1 != f2;
      break;
    case TOKENIZER_LE:
      f1 = f1 <= f2;
      break;
    case TOKENIZER_GE:
      f1 = f1 >= f2;
      break;
    case TOKENIZER_OR:
      f1 = f1 | f2;
      break;
    case TOKENIZER_XOR:
      f1 = f1 ^ f2;
      break;
    }
    op = tokenizer_token();
  }
  DEBUG_PRINTF("term: %d\n", f1);
  return f1;
}
/*---------------------------------------------------------------------------*/
static int
expr(void)
{
  int t1, t2;
  int op;
  
  t1 = term();
  op = tokenizer_token();
  DEBUG_PRINTF("expr: token %d\n", op);
  while(op == TOKENIZER_PLUS ||
	op == TOKENIZER_MINUS ||
	op == TOKENIZER_AND ||
        op == TOKENIZER_LOR ||
	op == TOKENIZER_XOR) {
    tokenizer_next();
    t2 = term();
    DEBUG_PRINTF("expr: %d %d %d\n", t1, op, t2);
    switch(op) {
    case TOKENIZER_PLUS:
      t1 = t1 + t2;
      break;
    case TOKENIZER_MINUS:
      t1 = t1 - t2;
      break;
    case TOKENIZER_AND:
      t1 = t1 & t2;
      break;
    case TOKENIZER_LOR:
      t1 = t1 || t2;
      break;
    }
    op = tokenizer_token();
  }
  DEBUG_PRINTF("expr: %d\n", t1);
  return t1;
}
/*---------------------------------------------------------------------------*/
static int
relation(void)
{
  int r1, r2;
  int op;
  
  r1 = expr();
  op = tokenizer_token();
  DEBUG_PRINTF("relation: token %d\n", op);
  while(op == TOKENIZER_LAND) {
    tokenizer_next();
    r2 = expr();
    DEBUG_PRINTF("relation: %d %d %d\n", r1, op, r2);
    switch(op) {
    case TOKENIZER_LAND:
      r1 = r1 && r2;
      break;
    }
    op = tokenizer_token();
  }
  return r1;
}

#if 0
/*---------------------------------------------------------------------------*/
static void
jump_linenum(int linenum)
{
  tokenizer_init(program_ptr);
  while(tokenizer_num() != linenum) {
    do {
      do {
	tokenizer_next();
      } while(tokenizer_token() != TOKENIZER_CR &&
	      tokenizer_token() != TOKENIZER_ENDOFINPUT);
      if(tokenizer_token() == TOKENIZER_CR) {
	tokenizer_next();
      }
    } while(tokenizer_token() != TOKENIZER_NUMBER);
    DEBUG_PRINTF("jump_linenum: Found line %d\n", tokenizer_num());
  }
}
#endif

/*---------------------------------------------------------------------------*/
static void
jump_line(int linenum)
{
  tokenizer_init(program_ptr);
  while(tokenizer_line_number() != linenum) {
    tokenizer_next();
  }
  /* swallow the CR that would be read next */
  accept(TOKENIZER_CR);

}
/*---------------------------------------------------------------------------*/
// TODO: error handling?
static int
jump_label(char * label)
{
  char currLabel[MAX_STRINGLEN];
  tokenizer_init(program_ptr);
  currLabel[0] = 0;
  while(tokenizer_token() != TOKENIZER_ENDOFINPUT) {
    tokenizer_next();
    if (tokenizer_token() == TOKENIZER_LABEL) {
      tokenizer_label(currLabel, sizeof(currLabel));
      tokenizer_next();
      if(strcmp(label, currLabel) == 0) {
        accept(TOKENIZER_CR);
        DEBUG_PRINTF("jump_linenum: Found line %d\n", tokenizer_line_number());
        break;
      }
    }
  }
  if (tokenizer_token() == TOKENIZER_ENDOFINPUT) {
      DEBUG_PRINTF("Label %s not found", label);
      ubasic_error = UBASIC_E_UNK_LABEL;
      return 0;
  } else {
      return 1;
  }
}
/*---------------------------------------------------------------------------*/
static void
goto_statement(void)
{
  accept(TOKENIZER_GOTO);
  if(tokenizer_token() == TOKENIZER_STRING) {
    tokenizer_string(string, sizeof(string));
    tokenizer_next();
    jump_label(string);
  } else {
    DEBUG_PRINTF("ubasic.c: goto_statement(): no label specified\n");
    ended = 1;
    ubasic_error = UBASIC_E_UNK_LABEL;
  }
}
/*---------------------------------------------------------------------------*/
static void
print_screen_statement(void)
{
  int val;
  accept(TOKENIZER_PRINT_SCREEN);
  val = expr();
  accept(TOKENIZER_CR);
  if (val && print_screen_d<0) {
      print_screen_d = open(print_screen_file, O_WRONLY|O_CREAT|O_TRUNC, 0777);
  }
  print_screen_p = val;
}
/*---------------------------------------------------------------------------*/
static void
print_statement(void)
{
  static char buf[128];

  buf[0]=0;
  accept(TOKENIZER_PRINT);
  do {
    DEBUG_PRINTF("Print loop\n");
    if(tokenizer_token() == TOKENIZER_STRING) {
      tokenizer_string(string, sizeof(string));
      sprintf(buf+strlen(buf), "%s", string);
      tokenizer_next();
    } else if(tokenizer_token() == TOKENIZER_COMMA) {
      strcat(buf, " ");
      tokenizer_next();
    } else if(tokenizer_token() == TOKENIZER_SEMICOLON) {
      tokenizer_next();
    } else {
      sprintf(buf+strlen(buf), "%d", expr());
    }
  } while(tokenizer_token() != TOKENIZER_CR && tokenizer_token() != TOKENIZER_ENDOFINPUT && tokenizer_token() != TOKENIZER_ELSE);
  script_console_add_line(buf);
  if (print_screen_p && print_screen_d>=0) {
    int bl = strlen(buf);
    buf[bl]='\n';
    write(print_screen_d, buf, bl+1);
  }
  DEBUG_PRINTF("End of print\n");
  accept_cr();
}
/*---------------------------------------------------------------------------*/
static void
if_statement(void)
{
  int r, else_cntr,endif_cntr;
  
  accept(TOKENIZER_IF);

  r = relation(); /*relation(); */
 // printf("if_statement: relation %d\n", r);
  accept(TOKENIZER_THEN);
  if (tokenizer_token() == TOKENIZER_CR) {  
	if(if_stack_ptr < MAX_IF_STACK_DEPTH) {
	 if_stack[if_stack_ptr] = r;
	 if_stack_ptr++;
	}
	  accept(TOKENIZER_CR);
	  if(r) {
	  	return;
	  }
	  else {
	  	else_cntr=endif_cntr=0;
		  tokenizer_next();        
		while(((tokenizer_token() != TOKENIZER_ELSE &&  tokenizer_token() != TOKENIZER_ENDIF) 
		       || else_cntr || endif_cntr) && tokenizer_token() != TOKENIZER_ENDOFINPUT){
		  if( tokenizer_token() == TOKENIZER_IF) {else_cntr+=1;endif_cntr+=1;}		    
		  if( tokenizer_token() == TOKENIZER_ELSE) {
			  else_cntr--;		  
		  }
		  if( tokenizer_token() == TOKENIZER_ENDIF)  {
		    endif_cntr--;
            if (endif_cntr != else_cntr) else_cntr--;
		  }    
		  tokenizer_next();                                                         
		 }
	    if(tokenizer_token() == TOKENIZER_ELSE) {
	    	return;
		}
	  }                                                  
	  accept(TOKENIZER_ENDIF);
	  accept(TOKENIZER_CR);  	              
  }else {
	  if(r) {
	    statement();
	  } else {
	    do {
	      tokenizer_next();
	    } while(tokenizer_token() != TOKENIZER_ELSE &&
		    tokenizer_token() != TOKENIZER_CR &&
		    tokenizer_token() != TOKENIZER_ENDOFINPUT);
	    if(tokenizer_token() == TOKENIZER_ELSE) {
	      tokenizer_next();
	      statement();
	    } else if(tokenizer_token() == TOKENIZER_CR) {
	      tokenizer_next();
	    }
	  }
  }
}
/*---------------------------------------------------------------------------*/
static void
else_statement(void)
{
  int r=0, endif_cntr;
  
  accept(TOKENIZER_ELSE);

  if(if_stack_ptr > 0) {
    r = if_stack[if_stack_ptr-1];
  }
 // printf("if_statement: relation %d\n", r);
  if (tokenizer_token() == TOKENIZER_CR) {  
	  accept(TOKENIZER_CR);
	  if(!r) {
	  	return;
	  }
	  else {                                      
	  	endif_cntr=0;
		tokenizer_next();        
		while(((tokenizer_token() != TOKENIZER_ENDIF ) 
		       || endif_cntr) && tokenizer_token() != TOKENIZER_ENDOFINPUT){
		  if( tokenizer_token() == TOKENIZER_IF) {endif_cntr+=1;}		    
		  if( tokenizer_token() == TOKENIZER_ENDIF)  {
		    endif_cntr--;
		  }    
		  tokenizer_next();                                                         
		 }
	  }                                                  
//	  accept(TOKENIZER_ENDIF);
//	  accept(TOKENIZER_CR);  	              
  }
}
/*---------------------------------------------------------------------------*/
static void
endif_statement(void)
{
	accept(TOKENIZER_ENDIF);
	accept(TOKENIZER_CR);  	              
    if(if_stack_ptr > 0) {
    	if_stack_ptr--;
    }
}
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
static void
let_statement(void)
{
 
  int var;

  var = tokenizer_variable_num();

  accept(TOKENIZER_VARIABLE);
  accept(TOKENIZER_EQ);
  ubasic_set_variable(var, expr());
  DEBUG_PRINTF("let_statement: assign %d to %d\n", variables[var], var);
  accept_cr();
}
/*---------------------------------------------------------------------------*/
static void
rem_statement(void)
{
  accept(TOKENIZER_REM);
  DEBUG_PRINTF("rem_statement\n");
  accept(TOKENIZER_CR);
}
/*---------------------------------------------------------------------------*/
static void
cls_statement(void)
{
  accept(TOKENIZER_CLS);
  script_console_clear();
  DEBUG_PRINTF("cls_statement\n");
  accept(TOKENIZER_CR);
}
/*---------------------------------------------------------------------------*/
static void
gosub_statement(void)
{
  accept(TOKENIZER_GOSUB);
  if(tokenizer_token() == TOKENIZER_STRING) {
    tokenizer_string(string, sizeof(string));
    do {
    tokenizer_next();
    } while(tokenizer_token() != TOKENIZER_CR);
    accept(TOKENIZER_CR);
    if(gosub_stack_ptr < MAX_GOSUB_STACK_DEPTH) {
/*    tokenizer_line_number_inc();*/
      gosub_stack[gosub_stack_ptr] = tokenizer_line_number();
      gosub_stack_ptr++;
      jump_label(string);
    } else {
      DEBUG_PRINTF("gosub_statement: gosub stack exhausted\n");
      ended = 1;
      ubasic_error = UBASIC_E_GOSUB_STACK_EXHAUSTED;
    }
  } else {
    DEBUG_PRINTF("ubasic.c: goto_statement(): no label specified\n");
    ended = 1;
    ubasic_error = UBASIC_E_UNK_LABEL;
  }
}
/*---------------------------------------------------------------------------*/
static void
return_statement(void)
{
  accept(TOKENIZER_RETURN);
  if(gosub_stack_ptr > 0) {
    gosub_stack_ptr--;
    jump_line(gosub_stack[gosub_stack_ptr]);
  } else {
    DEBUG_PRINTF("return_statement: non-matching return\n");
    ended = 1;
    ubasic_error = UBASIC_E_UNMATCHED_RETURN;
  }
}
/*---------------------------------------------------------------------------*/
static void
next_statement(void)
{
  int var, value;
  
  accept(TOKENIZER_NEXT);
  var = tokenizer_variable_num();
  accept(TOKENIZER_VARIABLE);
  if(for_stack_ptr > 0 &&
     var == for_stack[for_stack_ptr - 1].for_variable) {
    value = ubasic_get_variable(var) + for_stack[for_stack_ptr - 1].step;
    ubasic_set_variable(var, value);
    
    if(((for_stack[for_stack_ptr - 1].step > 0) && (value <= for_stack[for_stack_ptr - 1].to)) ||
       ((for_stack[for_stack_ptr - 1].step < 0) && (value >= for_stack[for_stack_ptr - 1].to)))
        jump_line(for_stack[for_stack_ptr - 1].line_after_for); 
    else {
      for_stack_ptr--;
      accept(TOKENIZER_CR);
    }
  } else {
    DEBUG_PRINTF("next_statement: non-matching next (expected %d, found %d)\n", for_stack[for_stack_ptr - 1].for_variable, var);
    accept(TOKENIZER_CR);
  }

}
/*---------------------------------------------------------------------------*/
static void
for_statement(void)
{
  int for_variable, to, step;
  
  accept(TOKENIZER_FOR);
  for_variable = tokenizer_variable_num();
  accept(TOKENIZER_VARIABLE);
  accept(TOKENIZER_EQ);
  ubasic_set_variable(for_variable, expr());
  accept(TOKENIZER_TO);
  to = expr();                     
  step = 1;
  if (tokenizer_token() != TOKENIZER_CR) {
	  accept(TOKENIZER_STEP);
	  step = expr();         
  }
  accept(TOKENIZER_CR);

  if(for_stack_ptr < MAX_FOR_STACK_DEPTH) {
    for_stack[for_stack_ptr].line_after_for = tokenizer_line_number();
    for_stack[for_stack_ptr].for_variable = for_variable;
    for_stack[for_stack_ptr].to = to;
    for_stack[for_stack_ptr].step = step;
    DEBUG_PRINTF("for_statement: new for, var %d to %d\n",
		 for_stack[for_stack_ptr].for_variable,
		 for_stack[for_stack_ptr].to);
		 
    for_stack_ptr++;
  } else {
    DEBUG_PRINTF("for_statement: for stack depth exceeded\n");
  }
}
/*---------------------------------------------------------------------------*/
static void
do_statement(void)
{
  accept(TOKENIZER_DO);
  accept(TOKENIZER_CR);
  if(do_stack_ptr < MAX_DO_STACK_DEPTH) {
     do_stack[do_stack_ptr] = tokenizer_line_number();
     do_stack_ptr++;
  }
}
/*---------------------------------------------------------------------------*/
static void
until_statement(void)
{
  int r;
  
  accept(TOKENIZER_UNTIL);
  r = relation();
  if(!r) {
    if(do_stack_ptr > 0) {
      jump_line(do_stack[do_stack_ptr-1]);
    }
  }
  else {
    do_stack_ptr--;
  	accept_cr();
  }

}
/*---------------------------------------------------------------------------*/
static void
while_statement(void)
{
  int r, while_cntr;
  
  accept(TOKENIZER_WHILE);
  if(while_stack_ptr < MAX_WHILE_STACK_DEPTH) {
    if ((while_stack_ptr == 0)||((while_stack_ptr > 0) && (while_stack[while_stack_ptr-1] != tokenizer_line_number()))){
      while_stack[while_stack_ptr] = tokenizer_line_number();
      while_stack_ptr++;
    }
  }
  r = relation();
  if(!r) {
  	while_cntr=0;
    while((tokenizer_token() != TOKENIZER_WEND  || while_cntr ) && 
	    tokenizer_token() != TOKENIZER_ENDOFINPUT){   
	    if (tokenizer_token() == TOKENIZER_WHILE) while_cntr+=1;
	    if (tokenizer_token() == TOKENIZER_WEND) while_cntr-=1;           
	  tokenizer_next();
	}  
    while_stack_ptr--;
    
    accept(TOKENIZER_WEND);
    accept(TOKENIZER_CR);  	
  }
  else  {
  	accept_cr();        
  } 
}
/*---------------------------------------------------------------------------*/
static void
wend_statement(void)
{
  accept(TOKENIZER_WEND);
  if(while_stack_ptr > 0) {
    jump_line(while_stack[while_stack_ptr-1]);
  }
  else {
  	accept_cr();
  }
}
/*---------------------------------------------------------------------------*/
static void
end_statement(void)
{
  accept(TOKENIZER_END);
  ended = 1;
}
/*---------------------------------------------------------------------------*/
static void
click_statement(void)
{
  accept(TOKENIZER_CLICK);
  tokenizer_string(string, sizeof(string));
  ubasic_camera_click(string);
  tokenizer_next();
  DEBUG_PRINTF("End of click\n");
  accept_cr();
}
/*---------------------------------------------------------------------------*/
static void
press_statement(void)
{
  accept(TOKENIZER_PRESS);
  tokenizer_string(string, sizeof(string));
  ubasic_camera_press(string);
  tokenizer_next();
  DEBUG_PRINTF("End of press\n");
  accept_cr();
}
/*---------------------------------------------------------------------------*/
static void
release_statement(void)
{
  accept(TOKENIZER_RELEASE);
  tokenizer_string(string, sizeof(string));
  ubasic_camera_release(string);
  tokenizer_next();
  DEBUG_PRINTF("End of release\n");
  accept_cr();
}
/*---------------------------------------------------------------------------*/
static void
sleep_statement(void)
{
  int val;
  accept(TOKENIZER_SLEEP);
  val = expr();
  ubasic_camera_sleep(val);
  DEBUG_PRINTF("End of sleep\n");
  accept_cr();
}
/*---------------------------------------------------------------------------*/
static void
shoot_statement(void)
{
  accept(TOKENIZER_SHOOT);
  ubasic_camera_shoot();
  DEBUG_PRINTF("End of shoot\n");
  accept_cr();
}

/*---------------------------------------------------------------------------*/
static void get_tv96_statement()
{
    int var;
    accept(TOKENIZER_GET_TV96);
    var = tokenizer_variable_num();
    accept(TOKENIZER_VARIABLE);
    ubasic_set_variable(var, shooting_get_tv96());
    accept_cr();
}

static void get_user_tv96_statement()
{
    int var;
    accept(TOKENIZER_GET_USER_TV96);
    var = tokenizer_variable_num();
    accept(TOKENIZER_VARIABLE);
    ubasic_set_variable(var, shooting_get_user_tv96());
    accept_cr();
}


static void get_user_tv_id_statement()
{
    int var;
    accept(TOKENIZER_GET_USER_TV_ID);
    var = tokenizer_variable_num();
    accept(TOKENIZER_VARIABLE);
    ubasic_set_variable(var, shooting_get_user_tv_id());
    accept_cr();
}

static void set_tv96_statement()
{
    int to;
    accept(TOKENIZER_SET_TV96);
    to = expr();
    shooting_set_tv96((short int)to, SET_LATER);
    accept_cr();
}

static void set_shutter_speed_statement()
{
    int to;
    accept(TOKENIZER_SET_SHUTTER_SPEED);
    to = expr();
    shooting_set_shutter_speed_ubasic(to, SET_LATER);
    accept_cr();
}

static void set_tv96_direct_statement()
{
    int to;
    accept(TOKENIZER_SET_TV96_DIRECT);
    to = expr();
    shooting_set_tv96_direct((short int)to, SET_LATER);
    accept_cr();
}

static void set_user_tv96_statement()
{
    int to;
    accept(TOKENIZER_SET_USER_TV96);
    to = expr();
    shooting_set_user_tv96((short int)to);
    accept_cr();
}

static void set_user_tv_by_id_statement()
{
    int to;
    accept(TOKENIZER_SET_USER_TV_BY_ID);
    to = expr();
    shooting_set_user_tv_by_id(to);
    accept_cr();
}

static void set_user_tv_by_id_rel_statement()
{
    int to;
    accept(TOKENIZER_SET_USER_TV_BY_ID_REL);
    to = expr();
    shooting_set_user_tv_by_id_rel(to);
    accept_cr();
}

static void set_sv96_statement()
{
    int to;
    accept(TOKENIZER_SET_SV96);
    to = expr();
    shooting_set_sv96((short int)to, SET_LATER);
    accept_cr();
}


/*---------------------------------------------------------------------------*/

static void get_av96_statement()
{
    int var;
    accept(TOKENIZER_GET_AV96);
    var = tokenizer_variable_num();
    accept(TOKENIZER_VARIABLE);
    ubasic_set_variable(var, shooting_get_av96());
    accept_cr();
}

static void get_user_av96_statement()
{
    int var;
    accept(TOKENIZER_GET_USER_AV96);
    var = tokenizer_variable_num();
    accept(TOKENIZER_VARIABLE);
    ubasic_set_variable(var, shooting_get_user_av96());
    accept_cr();
}

static void get_user_av_id_statement()
{
    int var;
    accept(TOKENIZER_GET_USER_AV_ID);
    var = tokenizer_variable_num();
    accept(TOKENIZER_VARIABLE);
    ubasic_set_variable(var, shooting_get_user_av_id());
    accept_cr();
}

static void set_av96_statement()
{
    int to;
    accept(TOKENIZER_SET_AV96);
    to = expr();
    shooting_set_av96((short int)to, SET_LATER);
    accept_cr();
}

static void set_av96_direct_statement()
{
    int to;
    accept(TOKENIZER_SET_AV96_DIRECT);
    to = expr();
    shooting_set_av96_direct((short int)to, SET_LATER);
    accept_cr();
}

static void set_user_av96_statement()
{
    int to;
    accept(TOKENIZER_SET_USER_AV96);
    to = expr();
    shooting_set_user_av96((short int)to);
    accept_cr();
}

static void set_user_av_by_id_statement()
{
    int to;
    accept(TOKENIZER_SET_USER_AV_BY_ID);
    to = expr();
    shooting_set_user_av_by_id(to);
    accept_cr();
}

static void set_user_av_by_id_rel_statement()
{
    int to;
    accept(TOKENIZER_SET_USER_AV_BY_ID_REL);
    to = expr();
    shooting_set_user_av_by_id_rel(to);
    accept_cr();
}

/*---------------------------------------------------------------------------*/

static void get_zoom_statement()
{
    int var;
    accept(TOKENIZER_GET_ZOOM);
    var = tokenizer_variable_num();
    accept(TOKENIZER_VARIABLE);
    ubasic_set_variable(var, shooting_get_zoom());
    accept_cr();
}

static void set_zoom_statement()
{
    int to;
    accept(TOKENIZER_SET_ZOOM);
    to = expr();
    shooting_set_zoom(to);
    accept_cr();
}

static void set_zoom_rel_statement()
{
    int to;
    accept(TOKENIZER_SET_ZOOM_REL);
    to = expr();
    shooting_set_zoom_rel(to);
    accept_cr();
}

static void set_zoom_speed_statement()
{
    int to;
    accept(TOKENIZER_SET_ZOOM_SPEED);
    to = expr();
    shooting_set_zoom_speed(to);
    accept_cr();
}

/*---------------------------------------------------------------------------*/

static void get_focus_statement()
{
    int var;
    accept(TOKENIZER_GET_FOCUS);
    var = tokenizer_variable_num();
    accept(TOKENIZER_VARIABLE);
    ubasic_set_variable(var, shooting_get_subject_distance());
    accept_cr();
}

static void get_near_limit_statement()
{
    int var;
    accept(TOKENIZER_GET_NEAR_LIMIT);
    var = tokenizer_variable_num();
    accept(TOKENIZER_VARIABLE);
    ubasic_set_variable(var, shooting_get_near_limit_of_acceptable_sharpness());
    accept_cr();
}

static void get_far_limit_statement()
{
    int var;
    accept(TOKENIZER_GET_FAR_LIMIT);
    var = tokenizer_variable_num();
    accept(TOKENIZER_VARIABLE);
    ubasic_set_variable(var, shooting_get_far_limit_of_acceptable_sharpness());
    accept_cr();
}

static void get_dof_statement()
{
    int var;
    accept(TOKENIZER_GET_DOF);
    var = tokenizer_variable_num();
    accept(TOKENIZER_VARIABLE);
    ubasic_set_variable(var, shooting_get_depth_of_field());
    accept_cr();
}

static void get_hyperfocal_distance_statement()
{
    int var;
    accept(TOKENIZER_GET_HYPERFOCAL_DIST);
    var = tokenizer_variable_num();
    accept(TOKENIZER_VARIABLE);
    ubasic_set_variable(var, shooting_get_hyperfocal_distance());
    accept_cr();
}



static void set_focus_statement()
{
    int to;
    accept(TOKENIZER_SET_FOCUS);
    to = expr();
    int m=mode_get()&MODE_SHOOTING_MASK;
    int mode_video=((m==MODE_VIDEO_STD) || 
			    (m==MODE_VIDEO_SPEED) ||  
			    (m==MODE_VIDEO_COMPACT) ||
			    (m==MODE_VIDEO_MY_COLORS) || 
			    (m==MODE_VIDEO_COLOR_ACCENT));
#if !defined (CAMERA_ixus700_sd500) && !defined (CAMERA_ixus800_sd700) && !defined (CAMERA_a560) && !defined (ixus70_sd1000)    
    if (shooting_get_focus_mode() || (mode_video)) shooting_set_focus(to, SET_NOW);
    else shooting_set_focus(to, SET_LATER);
#else
    if (mode_video) shooting_set_focus(to, SET_NOW);
    else shooting_set_focus(to, SET_LATER);    
#endif    
    accept_cr();
}

static void get_vbatt_statement()
{
    int var;
    accept(TOKENIZER_GET_VBATT);
    var = tokenizer_variable_num();
    accept(TOKENIZER_VARIABLE);
    ubasic_set_variable(var, (unsigned short)stat_get_vbatt());
	
    accept_cr();
}

static void get_prop_statement()
{
    int var, var1;
    accept(TOKENIZER_GET_PROP);
    var = expr();
    var1 = tokenizer_variable_num();
    accept(TOKENIZER_VARIABLE);
    ubasic_set_variable(var1, shooting_get_prop(var));
	
    accept_cr();
}
static void set_led_statement()
{
    int to, to1, to2;
    accept(TOKENIZER_SET_LED);
    to = expr();
    to1 = expr();
	to2 = 200;
	if (tokenizer_token() != TOKENIZER_CR && tokenizer_token() != TOKENIZER_ELSE ) {
		to2 = expr();
    }
	ubasic_set_led(to, to1, to2);
    accept_cr();
}
static void set_prop_statement()
{
    int to, to1;
    accept(TOKENIZER_SET_PROP);
    to = expr();
    to1 = expr();
	shooting_set_prop(to, to1);
    accept_cr();
}



/*---------------------------------------------------------------------------*/
//ARM Begin
static void get_iso_market_statement()
{
    int var;
    accept(TOKENIZER_GET_ISO_MARKET);
    var = tokenizer_variable_num();
    accept(TOKENIZER_VARIABLE);
    ubasic_set_variable(var, (int)shooting_get_iso_market());
    accept_cr();
}

static void get_iso_real_statement()
{
    int var;
    accept(TOKENIZER_GET_ISO_REAL);
    var = tokenizer_variable_num();
    accept(TOKENIZER_VARIABLE);
    ubasic_set_variable(var, (int)shooting_get_iso_real());
    accept_cr();
}

static void get_bv96_statement()
{
    int var;
    accept(TOKENIZER_GET_BV96);
    var = tokenizer_variable_num();
    accept(TOKENIZER_VARIABLE);
    ubasic_set_variable(var, (int)shooting_get_bv96());
    accept_cr();
}

static void get_sv96_statement()
{
    int var;
    accept(TOKENIZER_GET_SV96);
    var = tokenizer_variable_num();
    accept(TOKENIZER_VARIABLE);
    ubasic_set_variable(var, (int)shooting_get_sv96());
    accept_cr();
}

/*static void set_iso_market_statement()
{
    int to;
    accept(TOKENIZER_SET_ISO_MARKET);
    to = expr();
    shooting_set_iso_market(to);
    accept_cr();
}

static void set_iso_real_delta_from_base_statement()
{
    int to;
    accept(TOKENIZER_SET_ISO_DL_F_B);
    to = expr();
    shooting_set_iso_real_delta_from_base(to);
    accept_cr();
}*/

static void set_iso_real_statement()
{
    short int to;
    accept(TOKENIZER_SET_ISO_REAL);
    to = expr();
    shooting_set_iso_real(to, SET_LATER);
    accept_cr();
}

//ARM End


static void get_iso_mode_statement()
{
    int var;
    accept(TOKENIZER_GET_ISO_MODE);
    var = tokenizer_variable_num();
    accept(TOKENIZER_VARIABLE);
    ubasic_set_variable(var, shooting_get_iso_mode());
    accept_cr();
}

static void set_iso_mode_statement()
{
    int to;
    accept(TOKENIZER_SET_ISO_MODE);
    to = expr();
    shooting_set_iso_mode(to);
    accept_cr();
}
static void set_raw_statement()
{
    int to;
    accept(TOKENIZER_SET_RAW);
    to = expr();
    ubasic_camera_set_raw(to);
    accept_cr();
}
static void set_raw_nr_statement()
{
    int to;
    accept(TOKENIZER_SET_RAW_NR);
    to = expr();
    ubasic_camera_set_nr(to);
    accept_cr();
}

static void set_autostart_statement()
{
    int to;
    accept(TOKENIZER_SET_SCRIPT_AUTOSTART);
    to = expr();
    ubasic_camera_set_script_autostart(to);
    accept_cr();
}
static void exit_alt_statement()
{
    int to;
    accept(TOKENIZER_EXIT_ALT);
    to = expr();
    exit_alt(to);
    accept_cr();
}
/*---------------------------------------------------------------------------*/

static void wait_click_statement()
{
    int timeout=0;
    accept(TOKENIZER_WAIT_CLICK);
    if (tokenizer_token() != TOKENIZER_CR &&
        tokenizer_token() != TOKENIZER_ELSE ) {
        timeout = expr();
    }
    ubasic_camera_wait_click(timeout);
    accept_cr();
}

static void is_key_statement(void)
{
    int var;
    accept(TOKENIZER_IS_KEY);
    var = tokenizer_variable_num();
    accept(TOKENIZER_VARIABLE);
    tokenizer_string(string, sizeof(string));
    tokenizer_next();
    ubasic_set_variable(var, ubasic_camera_is_clicked(string));
    DEBUG_PRINTF("End of is_key\n");
    accept_cr();
}

static void wheel_left_statement(void){
  accept(TOKENIZER_WHEEL_LEFT);
#if defined (CAMERA_g7)
  JogDial_CCW();
#endif
  accept_cr();
}


static void wheel_right_statement(void){
  accept(TOKENIZER_WHEEL_RIGHT);
#if defined (CAMERA_g7)
  JogDial_CW();
#endif
  accept_cr();
}









/*---------------------------------------------------------------------------*/

static void md_get_cell_diff_statement()
{
    int var, col, row;
    accept(TOKENIZER_MD_GET_CELL_DIFF);

		col=expr();tokenizer_next();

		row=expr();tokenizer_next();

    var = tokenizer_variable_num();
    accept(TOKENIZER_VARIABLE);
	
    ubasic_set_variable(var, md_get_cell_diff(col,row));
    accept_cr();
}

static void md_detect_motion_statement()
{

 int columns;
 int rows;
 int pixel_measure_mode;
 int detection_timeout;
 int measure_interval;
 int threshold;
 int draw_grid=0;
 int clipping_region_mode=0;
 int clipping_region_row1=0;
 int clipping_region_column1=0;
 int clipping_region_row2=0;
 int clipping_region_column2=0;
 int ret_var_num;
 int parameters=0;
 int pixels_step=1;
 int msecs_before_trigger=0;

 //static char buf[128];

    accept(TOKENIZER_MD_DETECT_MOTION);

//		sprintf(buf,"token: %d",tokenizer_token()); script_console_add_line(buf);
		columns=expr();tokenizer_next();

//		sprintf(buf,"tk: %d",tokenizer_token()); script_console_add_line(buf);
		rows=expr();tokenizer_next();

//		sprintf(buf,"tk %d",tokenizer_token()); script_console_add_line(buf);
		pixel_measure_mode=expr();tokenizer_next();

		detection_timeout=expr();tokenizer_next();

//		printf("token: %d",tokenizer_token());
		measure_interval=expr();tokenizer_next();

//		printf("token: %d",tokenizer_token());
		threshold=expr();tokenizer_next();

//		printf("token: %d",tokenizer_token());
		draw_grid=expr();tokenizer_next();

//		printf("token: %d",tokenizer_token());
    ret_var_num = tokenizer_variable_num();

//		printf("%d,%d,%d,%d",columns,rows,pixel_measure_mode, detection_timeout);

    accept(TOKENIZER_VARIABLE);


    if (tokenizer_token() != TOKENIZER_CR && tokenizer_token() != TOKENIZER_ELSE) {
			// eat COMA	
//			tokenizer_next();
		}


		
    if (tokenizer_token() != TOKENIZER_CR && tokenizer_token() != TOKENIZER_ELSE) {
				tokenizer_next();
        clipping_region_mode = expr();
    }
    if (tokenizer_token() != TOKENIZER_CR && tokenizer_token() != TOKENIZER_ELSE ) {
				tokenizer_next();
        clipping_region_column1 = expr();
    }
    if (tokenizer_token() != TOKENIZER_CR && tokenizer_token() != TOKENIZER_ELSE ) {
				tokenizer_next();
        clipping_region_row1 = expr();
    }
    if (tokenizer_token() != TOKENIZER_CR && tokenizer_token() != TOKENIZER_ELSE ) {
				tokenizer_next();
        clipping_region_column2 = expr();
    }
    if (tokenizer_token() != TOKENIZER_CR && tokenizer_token() != TOKENIZER_ELSE ) {
				tokenizer_next();
        clipping_region_row2 = expr();
    }
    if (tokenizer_token() != TOKENIZER_CR && tokenizer_token() != TOKENIZER_ELSE ) {
				tokenizer_next();
        parameters = expr();
    }
    if (tokenizer_token() != TOKENIZER_CR && tokenizer_token() != TOKENIZER_ELSE ) {
				tokenizer_next();
        pixels_step = expr();
    }

    if (tokenizer_token() != TOKENIZER_CR && tokenizer_token() != TOKENIZER_ELSE ) {
				tokenizer_next();
        msecs_before_trigger = expr();
    }
			

    accept_cr();

//		sprintf(buf,"[%dx%d] md:%d tmout:%d", columns, rows, pixel_measure_mode, detection_timeout);
//		script_console_add_line(buf);

//		sprintf(buf,"int:%d trsh:%d g:%d vr:%d", measure_interval, threshold, draw_grid, ret_var_num);
//		script_console_add_line(buf);

//		sprintf(buf,"clip %d [%d,%d][%d,%d]", clipping_region_mode, clipping_region_column1, clipping_region_row1, clipping_region_column2,clipping_region_row2);
//		script_console_add_line(buf);

	md_init_motion_detector(
			columns, rows, pixel_measure_mode, detection_timeout, 
			measure_interval, threshold, draw_grid, ret_var_num,
			clipping_region_mode,
			clipping_region_column1, clipping_region_row1,
			clipping_region_column2, clipping_region_row2,
			parameters, pixels_step, msecs_before_trigger
	);
}

/*---------------------------------------------------------------------------*/



static void
statement(void)
{
  ubasic_token token;

  token = tokenizer_token();

  switch(token) {

  case TOKENIZER_PRINT_SCREEN:
    print_screen_statement();
    break;
  case TOKENIZER_PRINT:
    print_statement();
    break;

  case TOKENIZER_SLEEP:
    sleep_statement();
    break;
  case TOKENIZER_CLICK:
    click_statement();
    break;
  case TOKENIZER_PRESS:
    press_statement();
    break;
  case TOKENIZER_RELEASE:
    release_statement();
    break;
  case TOKENIZER_SHOOT:
    shoot_statement();
    break;
  case TOKENIZER_GET_TV96:
    get_tv96_statement();
    break; 
  case TOKENIZER_GET_USER_TV96:
    get_user_tv96_statement();
    break;   
  case TOKENIZER_GET_USER_TV_ID:
    get_user_tv_id_statement();
    break;
  case TOKENIZER_SET_TV96_DIRECT:
    set_tv96_direct_statement();
    break;    
  case TOKENIZER_SET_TV96:
    set_tv96_statement();
    break;  
  case TOKENIZER_SET_SHUTTER_SPEED:
    set_shutter_speed_statement();
    break;    
  case TOKENIZER_SET_USER_TV96:
    set_user_tv96_statement();
    break;    
  case TOKENIZER_SET_USER_TV_BY_ID:
    set_user_tv_by_id_statement();
    break;
  case TOKENIZER_SET_USER_TV_BY_ID_REL:
    set_user_tv_by_id_rel_statement();
    break;
  case TOKENIZER_GET_AV96:
    get_av96_statement();
    break;  
  case TOKENIZER_GET_USER_AV96:
    get_user_av96_statement();
    break;    
  case TOKENIZER_GET_USER_AV_ID:
    get_user_av_id_statement();
    break;
  case TOKENIZER_SET_AV96_DIRECT:
    set_av96_direct_statement();
    break;    
  case TOKENIZER_SET_AV96:
    set_av96_statement();
    break;  
    
  case TOKENIZER_SET_USER_AV96:
    set_user_av96_statement();
    break;    
  case TOKENIZER_SET_USER_AV_BY_ID:
    set_user_av_by_id_statement();
    break;
  case TOKENIZER_SET_USER_AV_BY_ID_REL:
    set_user_av_by_id_rel_statement();
    break;

  case TOKENIZER_GET_ZOOM:
    get_zoom_statement();
    break;
  case TOKENIZER_SET_ZOOM:
    set_zoom_statement();
    break;
  case TOKENIZER_SET_ZOOM_REL:
    set_zoom_rel_statement();
    break;
  case TOKENIZER_SET_ZOOM_SPEED:
    set_zoom_speed_statement();
    break;

  case TOKENIZER_GET_FOCUS:
    get_focus_statement();
    break;
  case TOKENIZER_SET_FOCUS:
    set_focus_statement();
    break;
  //ARM Begin
  case TOKENIZER_GET_NEAR_LIMIT:
    get_near_limit_statement();
    break;
  case TOKENIZER_GET_FAR_LIMIT:
    get_far_limit_statement();
    break;  
   case TOKENIZER_GET_DOF:
    get_dof_statement();
    break;
  case TOKENIZER_GET_HYPERFOCAL_DIST:
    get_hyperfocal_distance_statement();
    break;  
  case TOKENIZER_GET_ISO_MARKET:
    get_iso_market_statement();
    break;
  case TOKENIZER_GET_ISO_REAL:
    get_iso_real_statement();
    break;
  /*case TOKENIZER_SET_ISO_MARKET:
    set_iso_market_statement();
    break;
  case TOKENIZER_SET_ISO_DL_F_B:
    set_iso_real_delta_from_base_statement();
    break;*/  
  case TOKENIZER_SET_ISO_REAL:
    set_iso_real_statement();
    break;
  case TOKENIZER_GET_BV96:
    get_bv96_statement();
    break;  
  case TOKENIZER_GET_SV96:
    get_sv96_statement();
    break;    
  case TOKENIZER_SET_SV96:
    set_sv96_statement();
    break;  
  
  //ARM End
  
    

  case TOKENIZER_GET_ISO_MODE:
    get_iso_mode_statement();
    break;
  case TOKENIZER_SET_ISO_MODE:
    set_iso_mode_statement();
    break;

  case TOKENIZER_GET_VBATT:
    get_vbatt_statement();
    break;
  case TOKENIZER_GET_PROP:
    get_prop_statement();
    break;
  case TOKENIZER_SET_PROP:
    set_prop_statement();
    break;
  case TOKENIZER_SET_LED:
    set_led_statement();
    break;

  
  case TOKENIZER_WAIT_CLICK:
    wait_click_statement();
    break;
  case TOKENIZER_IS_KEY:
    is_key_statement();
    break;

  case TOKENIZER_WHEEL_LEFT:
    wheel_left_statement();
    break;
  case TOKENIZER_WHEEL_RIGHT:
    wheel_right_statement();
    break;

  case TOKENIZER_IF:
    if_statement();
    break;
  case TOKENIZER_ELSE:
    else_statement();
    break;
  case TOKENIZER_ENDIF:
    endif_statement();
    break;
  case TOKENIZER_GOTO:
    goto_statement();
    break;
  case TOKENIZER_GOSUB:
    gosub_statement();
    break;
  case TOKENIZER_RETURN:
    return_statement();
    break;
  case TOKENIZER_FOR:
    for_statement();
    break;
  case TOKENIZER_NEXT:
    next_statement();
    break;
  case TOKENIZER_DO:
    do_statement();
    break;
  case TOKENIZER_UNTIL:
    until_statement();
    break;
  case TOKENIZER_WHILE:
    while_statement();
    break;
  case TOKENIZER_WEND:
    wend_statement();
    break;
  case TOKENIZER_END:
    end_statement();
    break;
  case TOKENIZER_LET:
    accept(TOKENIZER_LET);
    /* Fall through. */
  case TOKENIZER_VARIABLE:
    let_statement();
    break;
  case TOKENIZER_REM:
    rem_statement();
    break;
  case TOKENIZER_CLS:
    cls_statement();
    break;
  case TOKENIZER_SET_RAW:
    set_raw_statement();
    break;
  case TOKENIZER_SET_RAW_NR:
    set_raw_nr_statement();
    break;
  case TOKENIZER_SET_SCRIPT_AUTOSTART:
    set_autostart_statement();
    break;
  case TOKENIZER_EXIT_ALT:
    exit_alt_statement();
    break;

// >> mx3 . motion detector
	case   TOKENIZER_MD_DETECT_MOTION:
		md_detect_motion_statement();
		break;
	case  TOKENIZER_MD_GET_CELL_DIFF:
		md_get_cell_diff_statement();
		break;
// << mx3 . motion_detector


  default:
    DEBUG_PRINTF("ubasic.c: statement(): not implemented %d\n", token);
    ended = 1;
    ubasic_error = UBASIC_E_UNK_STATEMENT;
  }
}
/*---------------------------------------------------------------------------*/
static void
line_statement(void)
{
  /* line numbers have been removed */
  DEBUG_PRINTF("----------- Line number %d ---------\n", tokenizer_line_number());
  /*    current_linenum = tokenizer_num();*/
  if (tokenizer_token() == TOKENIZER_LABEL) {
#ifdef DEBUG
      tokenizer_label(string, sizeof(string));
      DEBUG_PRINTF("line_statement: label: %s\n", string );
#endif
      accept(TOKENIZER_LABEL);
      accept(TOKENIZER_CR);
      return;
  }
  statement();
  return;
}
/*---------------------------------------------------------------------------*/
void
ubasic_run(void)
{
  if(tokenizer_finished()) {
    DEBUG_PRINTF("uBASIC program finished\n");
    return;
  }

  line_statement();
}
/*---------------------------------------------------------------------------*/
int
ubasic_finished(void)
{
  return ended || tokenizer_finished();
}
/*---------------------------------------------------------------------------*/
void
ubasic_set_variable(int varnum, int value)
{
  if(varnum >= 0 && varnum < MAX_VARNUM) {
    variables[varnum] = value;
  }
}
/*---------------------------------------------------------------------------*/
int
ubasic_get_variable(int varnum)
{
  if(varnum >= 0 && varnum < MAX_VARNUM) {
    return variables[varnum];
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
void
ubasic_end() {
  if (print_screen_d >= 0) {
    close(print_screen_d);
    print_screen_d = -1;
    print_screen_p = 0;
  }
}
/*---------------------------------------------------------------------------*/


