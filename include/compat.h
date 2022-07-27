/*
 * Copyright (c) 2021 David Cantrell <david.l.cantrell@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided
 * with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _COMPAT_H
#define _COMPAT_H

#include <stdint.h>
#include <sys/stat.h>

/* FreeBSD kernel stuff */

/* from <sys/param.h> on FreeBSD */
/* max raw I/O transfer size */
/*
 * XXX: this is _probably_ going to be 1M on the system if it were
 * running FreeBSD.  What is the corresponding Linux parameter here
 * and the sanctioned way to retrieve it?
 */
#define MAXPHYS (1024 * 1024)
/* #define MAXPHYS (128 * 1024)    <--- could be this on 32-bit systems */

/*
 * File system parameters and macros.
 *
 * MAXBSIZE - Filesystems are made out of blocks of at most MAXBSIZE
 *            bytes per block.  MAXBSIZE may be made larger without
 *            effecting any existing filesystems as long as it does
 *            not exceed MAXPHYS, and may be made smaller at the
 *            risk of not being able to use filesystems which
 *            require a block size exceeding MAXBSIZE.
 */
#define MAXBSIZE        65536   /* must be power of 2 */

/* from <sys/param.h> in FreeBSD */
/* Macros for counting and rounding. */
#define roundup2(x, y)  (((x)+((y)-1))&(~((y)-1))) /* if y is powers of two */
#define nitems(x)       (sizeof((x)) / sizeof((x)[0]))

/* FreeBSD libc stuff */

/* from <wchar.h> in FreeBSD */
#define iswascii(wc) (((wc) & ~0x7F) == 0)

mode_t getmode(const void *, mode_t);
void *setmode(const char *);
void strmode(int, char *);
int mergesort(void *, size_t, size_t, int (*)(const void *, const void *));
int heapsort(void *, size_t, size_t, int (*)(const void *, const void *));
char *getbsize(int *, long *);

/* FreeBSD libutil stuff */

/* from <libutil.h> in FreeBSD */
/* Values for humanize_number(3)'s flags parameter. */
#define HN_DECIMAL              0x01
#define HN_NOSPACE              0x02
#define HN_B                    0x04
#define HN_DIVISOR_1000         0x08
#define HN_IEC_PREFIXES         0x10

/* Values for humanize_number(3)'s scale parameter. */
#define HN_GETSCALE             0x10
#define HN_AUTOSCALE            0x20

/* functions from libutil in FreeBSD */
int humanize_number(char *, size_t, int64_t, const char *, int, int);
int expand_number(const char *, uint64_t *);

#ifndef HAVE_STRLCPY
size_t strlcpy(char *d, const char *s, size_t n);
#endif
#ifndef HAVE_STRLCAT
size_t strlcat(char *d, const char *s, size_t n);
#endif

/* we use SIGUSR1 in place of SIGINFO */
#define SIGINFO SIGUSR1

int signame_to_signum(const char *sig);
const char *signum_to_signame(int signum);
int get_signame_by_idx(size_t idx, const char **signame, int *signum);

#endif /* _COMPAT_H */
