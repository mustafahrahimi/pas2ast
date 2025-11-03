/**********************************************************************/
/* constants & public functions                                       */
/**********************************************************************/

#ifndef SYMTAB_H
#define SYMTAB_H

/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/
#include "keytoktab.h"

void p_symtab();                   /* display                 the ST  */

void   addp_name(char * fpname);   /* add  a program name  to the ST  */
void   addv_name(char * fpname);   /* add  a variable name to the ST  */

toktyp get_ntype(char * fpname);   /* get  a type        from the ST  */
int    find_name(char * fpname);   /* find a name          in the ST  */

void   setv_type (toktyp ftype);   /* set variable types   in the ST  */

#endif

/**********************************************************************/
/* end of definitions                                                 */
/**********************************************************************/