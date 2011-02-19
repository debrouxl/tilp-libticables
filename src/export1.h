/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  libticables2 - link cable library, a part of the TiLP project
 *  Copyright (C) 1999-2005  Romain Lievin
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef __TICABLES_EXPORT__
#define __TICABLES_EXPORT__

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* 
	Calling convention: default 
*/
# define TICALL

/* 
	Symbols exporting 
*/
#if defined(HAVE_FVISIBILITY)	// GCC 4.0 has introduced the -fvisibility flag (similar to declspec)
# define TIEXPORT1	__attribute__ ((visibility("default")))

#elif defined(__WIN32__)
# if defined(__BORLANDC__)		// BCC32 v5.x (or C++Builder)
#  if __BORLANDC__ >= 0x0500	// (c) 2001 Thomas Wolf (two@chello.at)
#   define TIEXPORT1
#  else
#   define TIEXPORT1
#  endif

# elif defined(_MSC_VER)		// MSVC 5.0 mini
#  if defined(TICABLES_EXPORTS)
#   define TIEXPORT1 __declspec(dllexport)
#  else
#   define TIEXPORT1 __declspec(dllimport)
#  endif

# elif defined(__MINGW32__)		// MinGW - GCC for Windows, (c) 2002 Kevin Kofler
#  if defined(TICABLES_EXPORTS)	// defined by the configure script
#   define TIEXPORT1 __declspec(dllexport)
#  else
#   define TIEXPORT1 __declspec(dllimport)
#  endif
# endif

#else
# define TIEXPORT1				// default
#endif

#ifdef __cplusplus
}
#endif

/* 
	Symbols deprecating
*/
#ifndef TILIBS_DEPRECATED
# ifdef __GNUC__
#  if (__GNUC__>3) || (__GNUC__==3 && __GNUC_MINOR__>=3)
#   define TILIBS_DEPRECATED __attribute__((deprecated))
#  else /* not GCC >= 3.3 */
#   define TILIBS_DEPRECATED
#  endif /* GCC >= 3.3 */
# else /* not __GNUC__ */
#  ifdef _MSC_VER
#   if _MSC_VER >= 1300
#    define TILIBS_DEPRECATED __declspec(deprecated)
#   else /* not _MSC_VER >= 1300 */
#    define TILIBS_DEPRECATED
#   endif /* _MSC_VER >= 1300 */
#  else /* not _MSC_VER */
#   define TILIBS_DEPRECATED
#  endif /* _MSC_VER */
# endif /* __GNUC__ */
#endif /* TILIBS_DEPRECATED */

#endif
