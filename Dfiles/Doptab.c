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
#include "optab.h"
#include "keytoktab.h"

/**********************************************************************/
/* The main function (the driver)                                     */
/**********************************************************************/
int main()
{
   p_optab();                   /* display the operator table         */

   printf("\n + int  int  is %s ", tok2lex(get_otype('+', integer, integer)));
   printf("\n + real real is %s ", tok2lex(get_otype('+', real,    real)));
   printf("\n + int  real is %s ", tok2lex(get_otype('+', integer, real)));
   printf("\n + real int  is %s ", tok2lex(get_otype('+', real,    integer)));
   
   printf("\n * int  int  is %s ", tok2lex(get_otype('*', integer, integer)));
   printf("\n * real real is %s ", tok2lex(get_otype('*', real,    real)));
   printf("\n * int  real is %s ", tok2lex(get_otype('*', integer, real)));
   printf("\n * real int  is %s ", tok2lex(get_otype('*', real,    integer)));
   
   printf("\n + bool bool is %s ", tok2lex(get_otype('+', boolean, boolean)));
   printf("\n * bool bool is %s ", tok2lex(get_otype('*', boolean, boolean)));
   
   printf("\n - int  int  is %s ", tok2lex(get_otype('-', integer, integer)));
   printf("\n / int  int  is %s ", tok2lex(get_otype('/', integer, integer)));

   

   printf("\n\n");
   }

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
