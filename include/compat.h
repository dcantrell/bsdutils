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

/* from sys/param.h on FreeBSD */
/* max raw I/O transfer size */
/*
 * XXX: this is _probably_ going to be 1M on the system if it were
 * running FreeBSD.  What is the corresponding Linux parameter here
 * and the sanctioned way to retrieve it?
 */
#define MAXPHYS (1024 * 1024)
/* #define MAXPHYS (128 * 1024)    <--- could be this on 32-bit systems */

/* Macros for counting and rounding. */
#define roundup2(x, y)  (((x)+((y)-1))&(~((y)-1))) /* if y is powers of two */

/* from wchar.h in FreeBSD */
#define iswascii(wc) (((wc) & ~0x7F) == 0)

/* from libc in FreeBSD */
mode_t getmode(const void *, mode_t);
void *setmode(const char *);
void strmode(int, char *);
int mergesort(void *, size_t, size_t, int (*)(const void *, const void *));
int heapsort(void *, size_t, size_t, int (*)(const void *, const void *));

#endif /* _COMPAT_H */
