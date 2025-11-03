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
#include "lexer.h"                   /* when the lexer     is added   */
#include "symtab.h"                  /* when the symtab    is added   */
#include "optab.h"                   /* when the optab     is added   */

/**********************************************************************/
/* OBJECT ATTRIBUTES FOR THIS OBJECT (C MODULE)                       */
/**********************************************************************/
#define DEBUG 0
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
/*static int tokens[] = {program, id, '(', input, ',', output, ')', ';',
                       var, id, ',', id, ',', id, ':', integer, ';',
                       begin, 
                       id, assign, id, '+', id, '*', number, 
                       end, '.', 
                       '$'};*/

/**********************************************************************/
/*  Simulate the lexer -- get the next token from the buffer          */
/**********************************************************************/
/*static int pget_token()
{  
   static int i=0;
   if (tokens[i] != '$') return tokens[i++]; else return '$';
}*/

/**********************************************************************/
/*  PRIVATE METHODS for this OBJECT  (using "static" in C)            */
/**********************************************************************/
static void in(char* msg) {
   printf("\n *** In  %s", msg);
}

static void out(char* msg) {
   printf("\n *** Out  %s", msg);
}

static void get_extra_symbs()  {
   printf("\nSYNTAX: Extra symbols after end of parse!");
   printf("\n%8s", "");
   while (lookahead != '$') { 
      printf("%s ", get_lexeme());
      lookahead = get_token();
   }
}
/**********************************************************************/
/* The Parser functions                                               */
/**********************************************************************/
static void match(int t) {
   if(DEBUG) printf("\n *** In match expected %s found %s", 
                   tok2lex(t), get_lexeme());
   if (lookahead == t) lookahead = get_token();
   else {
      is_parse_ok=0;
      printf("\nSYNTAX: Symbol expected %s found %s",
              tok2lex(t), get_lexeme());
    } 
}

/**********************************************************************/
/* The grammar functions                                              */
/**********************************************************************/

/*---------------------- Program Header -----------------------------*/
static void program_header() {
   if (DEBUG) in("program_header");
   match(program); 
   if (lookahead == id) {
      addp_name(get_lexeme());
      match(id);
   }
   else {
      printf("\nSYNTAX: ID expected found %s", get_lexeme());
      addp_name("???");
      is_parse_ok = 0;
   }
   match('('); match(input);
   match(','); match(output); match(')'); match(';');
   if (DEBUG) out("program_header\n");
}

/*--------------------------- Variable Part ---------------------------*/
static void type() {
   if (DEBUG) in("type");
   switch (lookahead) {
      case integer:
         setv_type(integer); 
         match(integer);
         break;
      case boolean:
         setv_type(boolean);
         match(boolean);
         break;
      case real:
         setv_type(real);
         match(real);
         break;
      default:
         printf("\nSYNTAX: Type name expected found %s", get_lexeme());
         is_parse_ok = 0;
         setv_type(error);
   }
   if (DEBUG) out("type");
}

static void id_list() {
   if (DEBUG) in("id_list");
   if (lookahead == id) {
      char *var_name = get_lexeme();
      if (find_name(var_name) == 0) {
         addv_name(var_name);
      }
      else {
         printf("\nSEMANTIC: ID already declared: %s", var_name);
         is_parse_ok = 0;
      }
   }
   if (lookahead == id) {
      match(id);
   }
   else {
      printf("\nSYNTAX:   ID expected found %s", get_lexeme());
      is_parse_ok = 0;
   }
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
   match(var);
   var_dec_list();
   if (DEBUG) out("var_part\n");
}

/*--------------------------- Statement Part --------------------------*/
static toktyp expr();

static toktyp operand() {
   if (DEBUG) in("operand");
   toktyp var_type;
   if (lookahead == id) {
      char* var_name = get_lexeme();
      if (find_name(var_name)) {
         var_type = get_ntype(var_name);
         match(id);
      }
      else {
         printf("\nSEMANTIC: ID NOT declared: %s", get_lexeme());
         var_type = undef;
         match(id);
      }
   } else if (lookahead == number) {
      var_type = integer;
      match(number);
   }
   else {
      printf("\nSYNTAX: Operand Expected");
      is_parse_ok = 0;
      var_type = error;
   }
   if (DEBUG) out("operand");
   return var_type;
}

static toktyp factor() {
   if (DEBUG) in("factor");
   toktyp var_type;  

   if (lookahead == '(') {
      match('(');
      var_type = expr();
      match(')');
   } else {
      var_type = operand();
   }
   if (DEBUG) out("factor");
   return var_type;
}

static toktyp term() {
   if (DEBUG) in("term");

   toktyp left_term = factor();
   if (lookahead == '*') {
      match('*');
      left_term = get_otype('*', left_term, term());
   }
   if (DEBUG) out("term");
   return left_term;
}

static toktyp expr() {
   if (DEBUG) in("expr");
   toktyp left_term = term();
   if (lookahead == '+') {
      match('+');
      left_term = get_otype('+', left_term, expr());
   }
   if (DEBUG) out("expr");
   return left_term;
}

static void assign_stat() {
   if (DEBUG) in("assign_stat");

   char* left_lexeme = get_lexeme();
   toktyp left_side = error;
   toktyp right_side = error;

   if (lookahead == id) {
      if (find_name(left_lexeme)) {
         left_side = get_ntype(left_lexeme);
      }
      else { 
         printf("\nSEMANTIC: ID NOT declared: %s", get_lexeme());
      }
      match(id);
   }
   else {
      printf("\nSYNTAX: ID expected found %s", get_lexeme());
      is_parse_ok = 0;
   }
   match(assign);
   right_side = expr();
   if (left_side != right_side) {
      printf("\nSEMANTIC: Assign types: %s := %s", tok2lex(left_side), 
                                                 tok2lex(right_side));
      is_parse_ok = 0;
   }
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

int parser() {
   if (DEBUG) printf("\n *** In  Parser");
   lookahead = get_token();            // get the first token
   if (lookahead == '$') {
      printf("\nSYNTAX: Input file is empty");
      is_parse_ok = 0;              
   }
   else {
      program_header();               // call the first grammar rule
      var_part();                     // call the second grammar rule
      stat_part();                    // call the third grammar rule
      
      if (lookahead != '$') {
         get_extra_symbs();
         is_parse_ok = 0;
      }                              
   }
   if (is_parse_ok) {
      printf("\nPARSE SUCCESSFUL!");
   }
   printf("\n________________________________________________________");
   p_symtab();
   return is_parse_ok;                // status indicator
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
        