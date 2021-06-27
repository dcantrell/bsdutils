/*-
 * SPDX-License-Identifier: BSD-4-Clause
 *
 * Copyright (c) 2002 Juli Mallett.
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>

__FBSDID("$FreeBSD$");

#ifndef lint
static const char copyright[] =
"@(#) Copyright (c) 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
#endif

#ifndef lint
static const char sccsid[] = "@(#)uname.c	8.2 (Berkeley) 5/4/95";
#endif

#include <sys/param.h>
#include <sys/utsname.h>
#include <sys/types.h>

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define	MFLAG	0x01
#define	NFLAG	0x02
#define	PFLAG	0x04
#define	RFLAG	0x08
#define	SFLAG	0x10
#define	VFLAG	0x20
#define	IFLAG	0x40
#define	UFLAG	0x80
#define	KFLAG	0x100
#define	BFLAG	0x200

typedef void (*get_t)(void);
static get_t get_buildid, get_ident, get_platform, get_hostname, get_arch,
    get_release, get_sysname, get_kernvers, get_uservers, get_version;

static void native_ident(void);
static void native_platform(void);
static void native_hostname(void);
static void native_arch(void);
static void native_release(void);
static void native_sysname(void);
static void native_version(void);
static void native_kernvers(void);
static void native_uservers(void);
static void native_buildid(void);
static void print_uname(u_int);
static void setup_get(void);
static void usage(void);

static char *buildid, *ident, *platform, *hostname, *arch, *release, *sysname,
    *version, *kernvers, *uservers;
static int space;

int
main(int argc, char *argv[])
{
	u_int flags;
	int ch;

	setup_get();
	flags = 0;

	while ((ch = getopt(argc, argv, "abiKmnoprsUv")) != -1)
		switch(ch) {
		case 'a':
			flags |= (MFLAG | NFLAG | RFLAG | SFLAG | VFLAG);
			break;
		case 'b':
			flags |= BFLAG;
			break;
		case 'i':
			flags |= IFLAG;
			break;
		case 'K':
			flags |= KFLAG;
			break;
		case 'm':
			flags |= MFLAG;
			break;
		case 'n':
			flags |= NFLAG;
			break;
		case 'p':
			flags |= PFLAG;
			break;
		case 'r':
			flags |= RFLAG;
			break;
		case 's':
		case 'o':
			flags |= SFLAG;
			break;
		case 'U':
			flags |= UFLAG;
			break;
		case 'v':
			flags |= VFLAG;
			break;
		case '?':
		default:
			usage();
		}

	argc -= optind;
	argv += optind;

	if (argc)
		usage();

	if (!flags)
		flags |= SFLAG;

	print_uname(flags);
	exit(0);
}

#define	CHECK_ENV(opt,var)				\
do {							\
	if ((var = getenv("UNAME_" opt)) == NULL) {	\
		get_##var = native_##var;		\
	} else {					\
		get_##var = (get_t)NULL;		\
	}						\
} while (0)

static void
setup_get(void)
{
	CHECK_ENV("s", sysname);
	CHECK_ENV("n", hostname);
	CHECK_ENV("r", release);
	CHECK_ENV("v", version);
	CHECK_ENV("m", platform);
	CHECK_ENV("p", arch);
	CHECK_ENV("i", ident);
	CHECK_ENV("K", kernvers);
	CHECK_ENV("U", uservers);
	CHECK_ENV("b", buildid);
}

#define	PRINT_FLAG(flags,flag,var)		\
	if ((flags & flag) == flag) {		\
		if (space)			\
			printf(" ");		\
		else				\
			space++;		\
		if (get_##var != NULL)		\
			(*get_##var)();		\
		printf("%s", var);		\
	}

static void
print_uname(u_int flags)
{
	PRINT_FLAG(flags, SFLAG, sysname);
	PRINT_FLAG(flags, NFLAG, hostname);
	PRINT_FLAG(flags, RFLAG, release);
	PRINT_FLAG(flags, VFLAG, version);
	PRINT_FLAG(flags, MFLAG, platform);
	PRINT_FLAG(flags, PFLAG, arch);
	PRINT_FLAG(flags, IFLAG, ident);
	PRINT_FLAG(flags, KFLAG, kernvers);
	PRINT_FLAG(flags, UFLAG, uservers);
	PRINT_FLAG(flags, BFLAG, buildid);
	printf("\n");
}

#define NATIVE_UNAME_GET(var,field) \
static void \
native_##var(void) \
{ \
	static char buf[1024]; \
	struct utsname u; \
 \
	if (uname(&u) != 0) \
		err(1, "uname"); \
\
	snprintf(buf, sizeof(buf), "%s", u.field); \
	var = buf; \
}

NATIVE_UNAME_GET(sysname, sysname)
NATIVE_UNAME_GET(hostname, nodename)
NATIVE_UNAME_GET(release, release)
NATIVE_UNAME_GET(version, version)
NATIVE_UNAME_GET(platform, machine)

#define UNKNOWN_GET(var) \
static void \
native_##var(void) \
{ \
	var = "unknown"; \
}

UNKNOWN_GET(arch)
UNKNOWN_GET(ident)
UNKNOWN_GET(buildid)
UNKNOWN_GET(uservers)
UNKNOWN_GET(kernvers)

static void
usage(void)
{
	fprintf(stderr, "usage: uname [-abiKmnoprsUv]\n");
	exit(1);
}
