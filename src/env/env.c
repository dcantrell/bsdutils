/*-
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 1988, 1993, 1994
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
 * 3. Neither the name of the University nor the names of its contributors
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

#ifndef lint
static const char copyright[] =
"@(#) Copyright (c) 1988, 1993, 1994\n\
	The Regents of the University of California.  All rights reserved.\n";
#endif /* not lint */

#if 0
#ifndef lint
static char sccsid[] = "@(#)env.c	8.3 (Berkeley) 4/2/94";
#endif /* not lint */
#endif

#include <sys/cdefs.h>

#include <sys/types.h>

#include <err.h>
#include <errno.h>
#include <pwd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "envopts.h"

extern char **environ;

int	 env_verbosity;

static void usage(void);

/*
 * Exit codes.
 */
#define EXIT_CANCELED      125 /* Internal error prior to exec attempt. */
#define EXIT_CANNOT_INVOKE 126 /* Program located, but not usable. */
#define EXIT_ENOENT        127 /* Could not find program to exec. */

int
main(int argc, char **argv)
{
	char *altpath, **ep, *p, **parg, term;
	char *cleanenv[1];
	char *login_name;
	struct passwd *pw;
	uid_t uid;
	int ch, want_clear;
	int rtrn;

	altpath = NULL;
	login_name = NULL;
	pw = NULL;
	want_clear = 0;
	term = '\n';
	while ((ch = getopt(argc, argv, "0iP:S:u:v")) != -1)
		switch(ch) {
		case '-':
		case 'i':
			want_clear = 1;
			break;
		case '0':
			term = '\0';
			break;
		case 'P':
			altpath = strdup(optarg);
			break;
		case 'S':
			/*
			 * The -S option, for "split string on spaces, with
			 * support for some simple substitutions"...
			 */
			split_spaces(optarg, &optind, &argc, &argv);
			break;
		case 'u':
			if (env_verbosity)
				fprintf(stderr, "#env unset:\t%s\n", optarg);
			rtrn = unsetenv(optarg);
			if (rtrn == -1)
				err(EXIT_FAILURE, "unsetenv %s", optarg);
			break;
		case 'v':
			env_verbosity++;
			if (env_verbosity > 1)
				fprintf(stderr, "#env verbosity now at %d\n",
				    env_verbosity);
			break;
		case '?':
		default:
			usage();
		}
	if (optind < argc && !strcmp(argv[optind], "-")) {
		want_clear = 1;
		++argv; /* skip the initial - during later scan */
	}
	if (want_clear) {
		environ = cleanenv;
		cleanenv[0] = NULL;
		if (env_verbosity)
			fprintf(stderr, "#env clearing environ\n");
	}
	if (login_name != NULL) {
		if (*login_name != '\0' && strcmp(login_name, "-") != 0) {
			pw = getpwnam(login_name);
			if (pw == NULL) {
				char *endp = NULL;
				errno = 0;
				uid = strtoul(login_name, &endp, 10);
				if (errno == 0 && *endp == '\0')
					pw = getpwuid(uid);
			}
			if (pw == NULL)
				errx(EXIT_FAILURE, "no such user: %s", login_name);
		}

		endpwent();
	}
	for (argv += optind; *argv && (p = strchr(*argv, '=')); ++argv) {
		if (env_verbosity)
			fprintf(stderr, "#env setenv:\t%s\n", *argv);
		*p = '\0';
		rtrn = setenv(*argv, p + 1, 1);
		*p = '=';
		if (rtrn == -1)
			err(EXIT_FAILURE, "setenv %s", *argv);
	}
	if (*argv) {
		if (term == '\0')
			errx(EXIT_CANCELED, "cannot specify command with -0");
		if (altpath)
			search_paths(altpath, argv);
		if (env_verbosity) {
			fprintf(stderr, "#env executing:\t%s\n", *argv);
			for (parg = argv, argc = 0; *parg; parg++, argc++)
				fprintf(stderr, "#env    arg[%d]=\t'%s'\n",
				    argc, *parg);
			if (env_verbosity > 1)
				sleep(1);
		}
		execvp(*argv, argv);
		err(errno == ENOENT ? EXIT_ENOENT : EXIT_CANNOT_INVOKE,
		    "%s", *argv);
	}
	for (ep = environ; *ep; ep++)
		(void)printf("%s%c", *ep, term);
	exit(0);
}

static void
usage(void)
{
	(void)fprintf(stderr,
	    "usage: env [-0iv] [-L|-U user[/class]] [-P utilpath] [-S string] [-u name]\n"
	    "           [name=value ...] [utility [argument ...]]\n");
	exit(1);
}
