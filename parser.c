/**********************************************************************/
/* lab 1 DVG C01 - Parser OBJECT                                      */
/**********************************************************************/

/**********************************************************************/
/* Include files                                                      */
/**********************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/**********************************************************************/
/* Other OBJECT's METHODS (IMPORTED)                                  */
/**********************************************************************/
#include "keytoktab.h"               /* when the keytoktab is added   */
/* #include "lexer.h"       */       /* when the lexer     is added   */
/* #include "symtab.h"      */       /* when the symtab    is added   */
/* #include "optab.h"       */       /* when the optab     is added   */

/**********************************************************************/
/* OBJECT ATTRIBUTES FOR THIS OBJECT (C MODULE)                       */
/**********************************************************************/
#define DEBUG 1
static int  lookahead=0;
static int  is_parse_ok=1;

/**********************************************************************/
/* RAPID PROTOTYPING - simulate the token stream & lexer (get_token)  */
/**********************************************************************/
/* define tokens + keywords NB: remove this when keytoktab.h is added */
/**********************************************************************/
//enum tvalues {program = 257, id, input, output, var, integer, begin,  assign, number, end};
/**********************************************************************/
/* Simulate the token stream for a given program                      */
/**********************************************************************/
static int tokens[] = {program, id, '(', input, ',', output, ')', ';',
                       var, id, ',', id, ',', id, ':', integer, ';',
                       begin, 
                       id, assign, id, '+', id, '*', number, 
                       end, '.', 
                       '$'};

/**********************************************************************/
/*  Simulate the lexer -- get the next token from the buffer          */
/**********************************************************************/
static int pget_token()
{  
   static int i=0;
   if (tokens[i] != '$') return tokens[i++]; else return '$';
}

/**********************************************************************/
/*  PRIVATE METHODS for this OBJECT  (using "static" in C)            */
/**********************************************************************/
static void in(char* msg) {
   printf("\n *** In  %s", msg);
}

static void out(char* msg) {
   printf("\n *** Out  %s", msg);
}
/**********************************************************************/
/* The Parser functions                                               */
/**********************************************************************/
static void match(int t)
{
   if(DEBUG) printf("\n *** In match expected %-15s found %s",
                    tok2lex(t), tok2lex(lookahead));
   if (lookahead == t) lookahead = pget_token();
   else {
      is_parse_ok=0;
      printf("\n *** Unexpected Token: expected %-15s found %s (in match)",
              tok2lex(t), tok2lex(lookahead));
    }
}

/**********************************************************************/
/* The grammar functions                                              */
/**********************************************************************/

/*---------------------- Program Header -----------------------------*/
static void program_header() {
   if (DEBUG) in("program_header");
   match(program); match(id); match('('); match(input);
   match(','); match(output); match(')'); match(';');
   if (DEBUG) out("program_header\n");
}

/*--------------------------- Variable Part ---------------------------*/
static void type() {
   if (DEBUG) in("type");
   if (lookahead == integer) { 
      match(integer);
   }
    if (DEBUG) out("type");
}

static void id_list() {
   if (DEBUG) in("id_list");
   match(id);
   if (lookahead == ',') {
      match(',');
      id_list();
   }
   if (DEBUG) out("id_list");
}

static void var_dec() {
   if (DEBUG) in("var_dec");
   id_list();
   match(':');
   type();
   match(';');
   if (DEBUG) out("var_dec");
}

static void var_dec_list() {
   if (DEBUG) in("var_dec_list");
   var_dec();
   if (lookahead == id) {
      var_dec_list();
   } 
   if (DEBUG) out("var_dec_list");
}

static void var_part() {
   if (DEBUG) in("var_part");
   if (lookahead == var) {
      match(lookahead);
      var_dec_list();
   }
   if (DEBUG) out("var_part\n");
}

/*--------------------------- Statement Part --------------------------*/
static void expr();

static void operand() {
   if (DEBUG) in("operand");
   if (lookahead == id) {
      match(id);
   } else {
      match(number);
   }
   if (DEBUG) out("operand");
}

static void factor() {
   if (DEBUG) in("factor");
   if (lookahead == '(') {
      match('(');
      expr();
      match(')');
   } else {
      operand();
   }
   if (DEBUG) out("factor");
}

static void term() {
   if (DEBUG) in("term");
   factor();
   if (lookahead == '*') {
      match('*');
      term();
   }
   if (DEBUG) out("term");
}

static void expr() {
   if (DEBUG) in("expr");
   term();
   if (lookahead == '+') {
      match('+');
      expr();
   }
   if (DEBUG) out("expr");
}

static void assign_stat() {
   if (DEBUG) in("assign_stat");
   match(id);
   match(assign);
   expr();
   if (DEBUG) out("assign_stat");
}

static void stat() {
   if (DEBUG) in("stat");
   assign_stat();
   if (DEBUG) out("stat");
}

static void stat_list() {
   if (DEBUG) in("stat_list");
   stat();
   if (lookahead == ';') {
      match(';');
      stat_list();
   }
   if (DEBUG) out("stat_list");
}

static void stat_part() {
   if (DEBUG) in("stat_part");
   match(begin);
   stat_list();
   match(end);
   match('.');
   if (DEBUG) out("stat_part");
}
   
/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/

int parser()
{
   if (DEBUG) printf("\n *** In  parser");
   lookahead = pget_token();       // get the first token
   program_header();               // call the first grammar rule
   var_part();                     // call the second grammar rule
   stat_part();                    // call the third grammar rule
   return is_parse_ok;             // status indicator
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
