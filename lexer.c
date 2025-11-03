/**********************************************************************/
/* lab 1 DVG C01 - Lexer OBJECT                                       */
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
#include "keytoktab.h"

/**********************************************************************/
/* OBJECT ATTRIBUTES FOR THIS OBJECT (C MODULE)                       */
/**********************************************************************/
#define BUFSIZE 1024
#define LEXSIZE   30
static char buffer[BUFSIZE];
static char lexbuf[LEXSIZE];
static int  pbuf  = 0;               /* current index program buffer  */
static int  plex  = 0;               /* current index lexeme  buffer  */
typedef unsigned char uchar;

/**********************************************************************/
/*  PRIVATE METHODS for this OBJECT  (using "static" in C)            */
/**********************************************************************/

static int is_special_case(char c) {
   return !isalnum((uchar)c) &&
          (isalpha((uchar)c) || 
          isdigit((uchar)c));
}

static int is_alphanumeric(char c) {
   return !isspace((uchar)c) && 
          (isalpha((uchar)c) || 
          isdigit((uchar)c));
}

static int is_numeric(char c)  {
   return !isspace((uchar)c) && 
          isdigit((uchar)c);
}

/**********************************************************************/
/* buffer functions                                                   */
/**********************************************************************/
/**********************************************************************/
/* Read the input file into the buffer                                */
/**********************************************************************/

static void get_prog() {
   int ch, i = 0;
   while ((ch = fgetc(stdin)) !=  EOF && i < BUFSIZ - 2) {
      buffer[i++] = ch; 
   }
   buffer[i++] = '$';
   buffer[i] = '\0';
}     

/**********************************************************************/
/* Display the buffer                                                 */
/**********************************************************************/  

static void pbuffer() {
   printf("\n________________________________________________________");
   printf("\nTHE PROGRAM TEXT"); 
   printf("\n________________________________________________________");  
   printf("\n%s", buffer);
   printf("\n________________________________________________________");
}

/**********************************************************************/
/* Copy a character from the program buffer to the lexeme buffer      */
/**********************************************************************/

static void get_char() {   
   if (pbuf < BUFSIZ && plex < LEXSIZE) {
      lexbuf[plex++] = buffer[pbuf++];
   }
}

/**********************************************************************/
/* End of buffer handling functions                                   */
/**********************************************************************/

/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/
/**********************************************************************/
/* Return a token                                                     */
/**********************************************************************/
int get_token() {
   // 0.0 Read from stdin into buffer and print prog code. 
   if (pbuf == 0) { get_prog(); pbuffer(); }

   // 0.1 Reset lexbuf for next get_token() calls. 
   memset(lexbuf, 0, LEXSIZE); plex = 0;
   
   // 1. Skip whitespaces (tab, newline, ..) & cpy
   // the first non-ws char from buffer to lexbuff
   while (isspace((uchar) buffer[pbuf])) { pbuf++; }
   get_char();

   // 2. Check if stdin stream is numeric, ex: 0123
   if (isdigit((uchar) lexbuf[0])) {
      while (is_numeric(buffer[pbuf])) { get_char(); }
      return number;
   }

   // 3. Check if stdin stream is alphanumeric, ex: testok1
   // Then it is either keyword or id. call key2tok(lexbuf)
   else if (isalpha((uchar) lexbuf[0])) {
      while (is_alphanumeric(buffer[pbuf])) { get_char(); }
      return key2tok(lexbuf);
   }

   // 4. Other cases. call lex2tok(lexbuf);
   else {
      if (lexbuf[0] == ':' && buffer[pbuf] == '=') { get_char(); }
      else if (lexbuf[0] == '(' || lexbuf[0] == ')') {
         while (is_special_case(buffer[pbuf])) {
            get_char();
         }
      }
      return lex2tok(lexbuf);
   }
   return 0;
}

/**********************************************************************/
/* Return a lexeme                                                    */
/**********************************************************************/
char * get_lexeme() {  
   return lexbuf;
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
