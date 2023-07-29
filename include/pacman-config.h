/**
 *	@file cnf.h
 *	@author your name (you@domain.com)
 *	@brief
 *	@version 0.1
 *	@date 2023-07-19
 *
 *	@copyright Copyright (c) 2023
 *
 */

#if defined(__cplusplus)
#	warning "A C++ compiler has been selected for C."
extern "C"
{
#endif

#if !defined(PM_CONFIG_HEADER_INCLUDED)
#define PM_CONFIG_HEADER_INCLUDED

#if __has_include(<sys/types.h>)
#	include <sys/types.h>
#endif




#if __has_include(<stdio.h>)
#	include <stdio.h>
#endif

#endif // PM_CONFIG_HEADER_INCLUDED

#if defined(__cplusplus)
};
#endif
