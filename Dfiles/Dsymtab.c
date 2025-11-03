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
#include "symtab.h"

/**********************************************************************/
/* The main function (the driver)                                     */
/**********************************************************************/
int main()
{
   p_symtab();
   addp_name("abc");
   addv_name("A");
   addv_name("B");
   setv_type(integer);
   addv_name("C");
   addv_name("D");
   setv_type(real);
   addv_name("E");
   addv_name("F");
   setv_type(boolean);
   p_symtab();

   if (find_name("abc")) printf("\n name FOUND ");
   else printf("\n name NOT FOUND ");
   if (find_name("A")) printf("\n name FOUND ");
   else printf("\n name NOT FOUND ");
   if (find_name("B")) printf("\n name FOUND ");
   else printf("\n name NOT FOUND ");
   if (find_name("X")) printf("\n name FOUND ");
   else printf("\n name NOT FOUND ");

   printf("\n\n");
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/