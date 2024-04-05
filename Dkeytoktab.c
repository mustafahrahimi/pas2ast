/**********************************************************************/
/* lab 1 DVG C01 - Driver OBJECT                                      */
/**********************************************************************/

/**********************************************************************/
/* Include files                                                      */
/**********************************************************************/
#include <stdio.h>

/**********************************************************************/
/* Other OBJECT's METHODS (IMPORTED)                                  */
/**********************************************************************/
#include "keytoktab.h"

/**********************************************************************/
/* The main function (the driver)                                     */
/**********************************************************************/
int main() {
   int i;
   
   p_toktab();
   
   /**********************************************************************/
   
   printf("\n Test token table (for (i=tstart+1; i <tend; i++))");
   printf("\n Test tok2lex(i), lex2tok(tok2lex(i)) for non-keyword tokens \n");

   for (i=tstart+1; i <tend; i++)
   printf("\n tok2lex(%3d) = %10s;    lex2tok(tok2lex(%3d)) = %4d ",
            i, tok2lex(i), i, lex2tok(tok2lex(i)));
   printf("\n\n");
   
   /**********************************************************************/
   
   printf("\n Test token table (for (i=kstart+1; i <kend; i++))");
   printf("\n Test tok2lex(i), lex2tok(tok2lex(i)) for keyword tokens \n");

   for (i=kstart+1; i <kend; i++)
   printf("\n tok2lex(%3d) = %10s;    lex2tok(tok2lex(%3d)) = %4d ",
           i, tok2lex(i), i, lex2tok(tok2lex(i)));
   printf("\n\n");
   
   /**********************************************************************/

   printf("\n Test token table for 1 char tokens)");
   printf("\n Test tok2lex('x'), lex2tok(tok2lex('x')) 1 char tokens \n");

   printf("\n tok2lex(%c)   = %10s;    lex2tok(tok2lex(%c))   = %4d ",
           '$', tok2lex('$'), '$', lex2tok(tok2lex('$')));
   printf("\n tok2lex(%c)   = %10s;    lex2tok(tok2lex(%c))   = %4d ",
           '(', tok2lex('('), '(', lex2tok(tok2lex('(')));
   printf("\n tok2lex(%c)   = %10s;    lex2tok(tok2lex(%c))   = %4d ",
           ')', tok2lex(')'), ')', lex2tok(tok2lex(')')));
   printf("\n tok2lex(%c)   = %10s;    lex2tok(tok2lex(%c))   = %4d ",
           '*', tok2lex('*'), '*', lex2tok(tok2lex('*')));
   printf("\n tok2lex(%c)   = %10s;    lex2tok(tok2lex(%c))   = %4d ",
           '+', tok2lex('+'), '+', lex2tok(tok2lex('+')));
   printf("\n tok2lex(%c)   = %10s;    lex2tok(tok2lex(%c))   = %4d ",
           ',', tok2lex(','), ',', lex2tok(tok2lex(',')));
   printf("\n tok2lex(%c)   = %10s;    lex2tok(tok2lex(%c))   = %4d ",
           '-', tok2lex('-'), '-', lex2tok(tok2lex('-')));
   printf("\n tok2lex(%c)   = %10s;    lex2tok(tok2lex(%c))   = %4d ",
           '.', tok2lex('.'), '.', lex2tok(tok2lex('.')));
   printf("\n tok2lex(%c)   = %10s;    lex2tok(tok2lex(%c))   = %4d ",
           '/', tok2lex('/'), '/', lex2tok(tok2lex('/')));
   printf("\n tok2lex(%c)   = %10s;    lex2tok(tok2lex(%c))   = %4d ",
           ':', tok2lex(':'), ':', lex2tok(tok2lex(':')));
   printf("\n tok2lex(%c)   = %10s;    lex2tok(tok2lex(%c))   = %4d ",
           ';', tok2lex(';'), ';', lex2tok(tok2lex(';')));
   printf("\n tok2lex(%c)   = %10s;    lex2tok(tok2lex(%c))   = %4d ",
           '=', tok2lex('='), '=', lex2tok(tok2lex('=')));        

   printf("\n\n");
   
   /**********************************************************************/
   
   printf("\n Test keyword table (for (i=kstart+1; i <kend; i++))");
   printf("\n Test tok2lex(i), key2tok(tok2lex(i)) for keyword tokens \n");

   for (i=kstart+1; i <kend; i++)
   printf("\n tok2lex(%3d) = %10s;    key2tok(tok2lex(%3d)) = %4d;",
             i, tok2lex(i), i, key2tok(tok2lex(i)));

   printf("\n\n");
   
   /**********************************************************************/
   
   printf("\n Test keyword table for specific values (non-keywords):-");
   printf("\n Lexemes:- test1, id, number, :=, undef, predef, tempty, error, type, !?*; \n");
      
   printf("\n key2tok(\"test1\")   = %4d;    tok2lex(key2tok(\"test1\"))  = %5s ",
           key2tok("test1"), tok2lex(key2tok("test1")));
   printf("\n key2tok(\"id\")      = %4d;    tok2lex(key2tok(\"id\"))     = %5s ",
           key2tok("id"),     tok2lex(key2tok("id")));
   printf("\n key2tok(\"number\")  = %4d;    tok2lex(key2tok(\"number\")) = %5s ",
           key2tok("number"), tok2lex(key2tok("number")));
   printf("\n key2tok(\":=\")      = %4d;    tok2lex(key2tok(\":=\"))     = %5s ",
           key2tok(":="),     tok2lex(key2tok(":=")));
   printf("\n key2tok(\"undef\")   = %4d;    tok2lex(key2tok(\"undef\"))  = %5s ",
           key2tok("undef"),  tok2lex(key2tok("undef")));
   printf("\n key2tok(\"predef\")  = %4d;    tok2lex(key2tok(\"predef\")) = %5s ",
           key2tok("predef"), tok2lex(key2tok("predef")));
   printf("\n key2tok(\"tempty\")  = %4d;    tok2lex(key2tok(\"tempty\")) = %5s ",
           key2tok("tempty"), tok2lex(key2tok("tempty")));
   printf("\n key2tok(\"error\")   = %4d;    tok2lex(key2tok(\"error\"))  = %5s ",
           key2tok("error"),  tok2lex(key2tok("error")));
   printf("\n key2tok(\"type\")    = %4d;    tok2lex(key2tok(\"type\"))   = %5s ",
           key2tok("type"),   tok2lex(key2tok("type")));
   printf("\n key2tok(\"!?*;\")    = %4d;    tok2lex(key2tok(\"!?*;\"))   = %5s ",
           key2tok("!?*;"),   tok2lex(key2tok("!?*;")));
   printf("\n\n");
   

   /**********************************************************************/
   
   printf("\n Test lex2tok (both tables) for specific values (non keywords):-");
   printf("\n Lexemes:- test1, id, number, :=, undef, predef, tempty, error, type \n");
   

   printf("\n lex2tok(\"test1\")   = %4d;    tok2lex(lex2tok(\"test1\"))  = %10s ",
           lex2tok("test1"), tok2lex(lex2tok("test1")));
   printf("\n lex2tok(\"id\")      = %4d;    tok2lex(lex2tok(\"id\"))     = %10s ",
           lex2tok("id"), tok2lex(lex2tok("id")));
   printf("\n lex2tok(\"number\")  = %4d;    tok2lex(lex2tok(\"number\")) = %10s ",
           lex2tok("number"), tok2lex(lex2tok("number")));
   printf("\n lex2tok(\":=\")      = %4d;    tok2lex(lex2tok(\":=\"))     = %10s ",
           lex2tok(":="), tok2lex(lex2tok(":=")));
   printf("\n lex2tok(\"undef\")   = %4d;    tok2lex(lex2tok(\"undef\"))  = %10s ",
           lex2tok("undef"), tok2lex(lex2tok("undef")));
   printf("\n lex2tok(\"predef\")  = %4d;    tok2lex(lex2tok(\"predef\")) = %10s ",
           lex2tok("predef"), tok2lex(lex2tok("predef")));
   printf("\n lex2tok(\"tempty\")  = %4d;    tok2lex(lex2tok(\"tempty\")) = %10s ",
           lex2tok("tempty"), tok2lex(lex2tok("tempty")));
   printf("\n lex2tok(\"error\")   = %4d;    tok2lex(lex2tok(\"error\"))  = %10s ",
           lex2tok("error"), tok2lex(lex2tok("error")));
   printf("\n lex2tok(\"type\")    = %4d;    tok2lex(lex2tok(\"type\"))   = %10s ",
           lex2tok("type"), tok2lex(lex2tok("type")));
   printf("\n\n");


   /**********************************************************************/

   printf("\n Test lex2tok (both tables) for specific values (keywords):-");
   printf("\n Lexemes:- program input output var begin boolean integer real \n");


   printf("\n lex2tok(\"program\") = %4d;     tok2lex(lex2tok(\"program\")) = %10s ",
           lex2tok("program"), tok2lex(lex2tok("program")));
   printf("\n lex2tok(\"input\")   = %4d;     tok2lex(lex2tok(\"input\"))   = %10s ",
           lex2tok("input"),  tok2lex(lex2tok("input")));
   printf("\n lex2tok(\"output\")  = %4d;     tok2lex(lex2tok(\"output\"))  = %10s ",
           lex2tok("output"),  tok2lex(lex2tok("output")));
   printf("\n lex2tok(\"var\")     = %4d;     tok2lex(lex2tok(\"var\"))     = %10s ",
           lex2tok("var"), tok2lex(lex2tok("var")));
   printf("\n lex2tok(\"begin\")   = %4d;     tok2lex(lex2tok(\"begin\"))   = %10s ",
           lex2tok("begin"), tok2lex(lex2tok("begin")));
   printf("\n lex2tok(\"boolean\") = %4d;     tok2lex(lex2tok(\"boolean\")) = %10s ",
           lex2tok("boolean"),  tok2lex(lex2tok("boolean")));
   printf("\n lex2tok(\"integer\"  = %4d;     tok2lex(lex2tok(\"integer\")) = %10s ",
           lex2tok("integer"), tok2lex(lex2tok("integer")));
   printf("\n lex2tok(\"real\")    = %4d;     tok2lex(lex2tok(\"real\"))    = %10s ",
           lex2tok("real"), tok2lex(lex2tok("real")));
   printf("\n\n");

   /**********************************************************************/
   
   printf("\n End of tests\n");
   return 1;
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
