/**
 *	@file main.h
 *	@author your name (you@domain.com)
 *	@brief
 *	@version 0.1
 *	@date 2023-07-28
 *
 *	@copyright Copyright (c) 2023
 *
 */

#if !defined(PM_CONFIG_RUNTIME_MAIN_HEADER_INCLUDED)
#define PM_CONFIG_RUNTIME_MAIN_HEADER_INCLUDED

#include "../pacman-config.h"

#if defined(__cplusplus)
extern "C" {
#endif /** __cplusplus */

#if defined(__18CXX)
#	define ID_VOID_MAIN
#endif
#if defined(__CLASSIC_C__)
/* cv-qualifiers did not exist in K&R C */
#	define const
#	define volatile
#endif

#if !defined(__has_include)
/* If the compiler does not have __has_include, pretend the answer is
   always no.  */
#  define __has_include(x) 0
#endif

#if defined(ID_VOID_MAIN)
void main();
#else
#	if defined(__CLASSIC_C__)
int main(argc, argv) int argc; char *argv[];
#	else
int main(int argc, char* argv[]);
#	endif /** __CLASSIC_C__ */
#endif /** ID_VOID_MAIN */

#if defined(__cplusplus)
}
#endif /** __cplusplus */

#endif /** PM_CONFIG_RUNTIME_MAIN_HEADER_INCLUDED */
