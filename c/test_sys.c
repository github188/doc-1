/*
 * test.c--
 *
 * Copyright (C) 2014,2015,  <li_yunteng@163.com>
 * Auther: liyunteng
 * License: GPL
 * Update time:
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */
#include <stdio.h>


int main(int argc, char *argv[])
{

#define __STRICT_ANSI__
	
	printf("__STRICT_ANSI__\n");
	
// // __STRICT_ANSI__

#define _ISOC99_SOURCE
	
	printf("_ISOC99_SOURCE\n");
	
// // _ISOC99_SOURCE

#define _ISOC11_SOURCE
	
	printf("_ISOC11_SOURCE\n");
	
// // _ISOC11_SOURCE

#define _POSIX_SOURCE
	
	printf("_POSIX_SOURCE\n");
	
// // _POSIX_SOURCE

#define _POSIX_C_SOURCE
	
	printf("_POSIX_C_SOURCE\n");
	
// // _POSIX_C_SOURCE

#define _XOPEN_SOURCE
	
	printf("_XOPEN_SOURCE\n");
	
// // _XOPEN_SOURCE

#define _XOPEN_SOURCE_EXTENDED
	
	printf("_XOPEN_SOURCE_EXTENDED\n");
	
// // _XOPEN_SOURCE_EXTENDED

#define _LARGEFILE_SOURCE
	
	printf("_LARGEFILE_SOURCE\n");
	
// // _LARGEFILE_SOURCE

#define _LARGEFILE64_SOURCE

	printf("_LARGEFILE64_SOURCE\n");
	
// // _LARGEFILE64_SOURCE

#define _BSD_SOURCE
	
	printf("_BSD_SOURCE\n");
	
// // _BSD_SOURCE

#define _SVID_SOURCE
	
	printf("_SVID_SOURCE\n");
	
// // _SVID_SOURCE

#define _ATFILE_SOURCE
	
	printf("_ATFILE_SOURCE\n");
	
// // _ATFILE_SOURCE

#define _GNU_SOURCE
	
	printf("_GNU_SOURCE\n");
	
// // _GNU_SOURCE

#define _DEFAULT_SOURCE
	
	printf("_DEFUALT_SOURCE\n");
	
// // _DEFAULT_SOURCE

#define _REENTRANT
	
	printf("_REENTRANT\n");
	
// // _REENTRANT

#define _THREAD_SAFE
	
	printf("_THREAD_SAFE\n");
	
// // _THREAD_SAFE

#define _FORTIFY_SOURCE
	
	printf("_FORTIFY_SOURCE\n");
	
// // _FORTIFY_SOURCE

#define __USE_ISOC11
	
	printf("__USE_ISOC11\n");
	
// // __USE_ISOC11

#define __USE_ISOC99
	
	printf("__USE_ISOC99\n");
	
// // __USE_ISOC99

#define __USE_ISOC95
	
	printf("__USE_ISOC95\n");
	
// // __USE_ISOC95
	
#define __USE_POSIX
	
	printf("__USE_POSIX\n");
	
// // __USE_POXIS	

#define __USE_POSIX2
	
	printf("__USE_POSIX2\n");
	
// // __USE_POSIX2

#define __USE_POSIX199309
	
	printf("__USE_POSIX199309\n");
	
// // __USE_POSIX199309
#define __USE_POSIX199506
	
	printf("__USE_POSIX199506\n");
	
// // __USE_POSIX199506

#define __USE_XOPEN
	
	printf("__USE_XOPEN\n");
	
// // __USE_XOPEN

#define __USE_XOPEN_EXTENDED
	
	printf("__USE_XOPEN_EXTENDED\n");
	
// // __USE_XOPEN_EXTENDED

#define __USE_UNIX98
	
	printf("__USE_UNI98\n");
	
// // __USE_UNIX98

#define __USE_XOPEN2K
	
	printf("__USE_XOPEN2K\n");
	
// // __USE_XOPEN2K

#define __USE_XOPEN2KXSI
	
	printf("__USE_XOPEN2KXSI\n");
	
// // __USE_XOPEN2KXSI
#define __USE_XOPEN2K8
	
	printf("__USE_XOPEN2K8\n");
	
// // __USE_XOPEN2K8

#define __USE_XOPEN2K8XSI
	
	printf("__USE_XOPEN2K8XSI\n");
	
// // __USE_XOPEN2K8XSI

#define __USE_LARGEFILE
	
	printf("__USE_LARGEFILE\n");
	
// // __USE_LARGEFILE

#define __USE_LARGEFILE64
	
	printf("__USE_LARGEFILE64\n");
	
// // __USE_LARGEFILE64

#define __USE_FILE_OFFSET64
	
	printf("__USE_FILE_OFFSET64\n");
	
// // __USE_FILE_OFFSET64

#define __USE_BSD
	
	printf("__USE_BSD\n");
	
// // __USE_BSD

#define __USE_SVID
	
	printf("__USE_SVID\n");
	
// // __USE_SVID

#define __USE_MISC
	
	printf("__USE_MISC\n");
	
// // __USE_MISC
#define __USE_ATFILE
	
	printf("__USE_ATFILE\n");
	
// // __USE_ATFILE
#define __USE_GNU
	
	printf("__USE_GNU\n");
	
// // __USE_GNU
#define __USE_REENTRANT
	
	printf("__USE_REENTRANT\n");
	
#define __USE_FORTIFY_LEVEL

#include <signal.h>
	sigqueue(__pid_t __pid, int __sig, const union sigval __val);
	return 0;
}


