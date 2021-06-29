/*-
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Edward Sze-Tyan Wang.
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

#include <sys/cdefs.h>

__FBSDID("$FreeBSD$");

#ifndef lint
static const char sccsid[] = "@(#)forward.c	8.1 (Berkeley) 6/6/93";
#endif

#include <sys/param.h>
#include <sys/mount.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/inotify.h>
#include <sys/vfs.h>

#include <linux/magic.h>

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "extern.h"

static void rlines(FILE *, const char *fn, off_t, struct stat *);
static int show(file_info_t *);
static void set_events(file_info_t *files);

/* defines for inner loop actions */
#define USE_SLEEP	0
#define USE_INOTIFY	1
#define ADD_EVENTS	2

static int *ev;
static int action = USE_SLEEP;
static int ifd;

static const file_info_t *last;

/*
 * forward -- display the file, from an offset, forward.
 *
 * There are eight separate cases for this -- regular and non-regular
 * files, by bytes or lines and from the beginning or end of the file.
 *
 * FBYTES	byte offset from the beginning of the file
 *	REG	seek
 *	NOREG	read, counting bytes
 *
 * FLINES	line offset from the beginning of the file
 *	REG	read, counting lines
 *	NOREG	read, counting lines
 *
 * RBYTES	byte offset from the end of the file
 *	REG	seek
 *	NOREG	cyclically read characters into a wrap-around buffer
 *
 * RLINES
 *	REG	mmap the file and step back until reach the correct offset.
 *	NOREG	cyclically read lines into a wrap-around array of buffers
 */
void
forward(FILE *fp, const char *fn, enum STYLE style, off_t off, struct stat *sbp)
{
	int ch;

	switch(style) {
	case FBYTES:
		if (off == 0)
			break;
		if (S_ISREG(sbp->st_mode)) {
			if (sbp->st_size < off)
				off = sbp->st_size;
			if (fseeko(fp, off, SEEK_SET) == -1) {
				ierr(fn);
				return;
			}
		} else while (off--)
			if ((ch = getc(fp)) == EOF) {
				if (ferror(fp)) {
					ierr(fn);
					return;
				}
				break;
			}
		break;
	case FLINES:
		if (off == 0)
			break;
		for (;;) {
			if ((ch = getc(fp)) == EOF) {
				if (ferror(fp)) {
					ierr(fn);
					return;
				}
				break;
			}
			if (ch == '\n' && !--off)
				break;
		}
		break;
	case RBYTES:
		if (S_ISREG(sbp->st_mode)) {
			if (sbp->st_size >= off &&
			    fseeko(fp, -off, SEEK_END) == -1) {
				ierr(fn);
				return;
			}
		} else if (off == 0) {
			while (getc(fp) != EOF);
			if (ferror(fp)) {
				ierr(fn);
				return;
			}
		} else
			if (bytes(fp, fn, off))
				return;
		break;
	case RLINES:
		if (S_ISREG(sbp->st_mode))
			if (!off) {
				if (fseeko(fp, (off_t)0, SEEK_END) == -1) {
					ierr(fn);
					return;
				}
			} else
				rlines(fp, fn, off, sbp);
		else if (off == 0) {
			while (getc(fp) != EOF);
			if (ferror(fp)) {
				ierr(fn);
				return;
			}
		} else
			if (lines(fp, fn, off))
				return;
		break;
	default:
		break;
	}

	while ((ch = getc(fp)) != EOF)
		if (putchar(ch) == EOF)
			oerr();
	if (ferror(fp)) {
		ierr(fn);
		return;
	}
	(void)fflush(stdout);
}

/*
 * rlines -- display the last offset lines of the file.
 */
static void
rlines(FILE *fp, const char *fn, off_t off, struct stat *sbp)
{
	struct mapinfo map;
	off_t curoff, size;
	int i;

	if (!(size = sbp->st_size))
		return;
	map.start = NULL;
	map.fd = fileno(fp);
	map.mapoff = map.maxoff = size;

	/*
	 * Last char is special, ignore whether newline or not. Note that
	 * size == 0 is dealt with above, and size == 1 sets curoff to -1.
	 */
	curoff = size - 2;
	while (curoff >= 0) {
		if (curoff < map.mapoff && maparound(&map, curoff) != 0) {
			ierr(fn);
			return;
		}
		for (i = curoff - map.mapoff; i >= 0; i--)
			if (map.start[i] == '\n' && --off == 0)
				break;
		/* `i' is either the map offset of a '\n', or -1. */
		curoff = map.mapoff + i;
		if (i >= 0)
			break;
	}
	curoff++;
	if (mapprint(&map, curoff, size - curoff) != 0) {
		ierr(fn);
		exit(1);
	}

	/* Set the file pointer to reflect the length displayed. */
	if (fseeko(fp, sbp->st_size, SEEK_SET) == -1) {
		ierr(fn);
		return;
	}
	if (map.start != NULL && munmap(map.start, map.maplen)) {
		ierr(fn);
		return;
	}
}

static int
show(file_info_t *file)
{
	int ch;

	while ((ch = getc(file->fp)) != EOF) {
		if (last != file && no_files > 1) {
			if (!qflag)
				printfn(file->file_name, 1);
			last = file;
		}
		if (putchar(ch) == EOF)
			oerr();
	}
	(void)fflush(stdout);
	if (ferror(file->fp)) {
		fclose(file->fp);
		file->fp = NULL;
		ierr(file->file_name);
		return 0;
	}
	clearerr(file->fp);
	return 1;
}

/* a rather ugly list of filesystems from linux/magic.h specifying whether
 * we can watch them with inotify; explicitly specify them as we can still
 * fall back to sleep for the other filesystems, while the opposite would
 * cause actual practical problems
 */
static int
fs_is_local(unsigned long magic)
{
	switch (magic) {
	case ADFS_SUPER_MAGIC:
	case AFFS_SUPER_MAGIC:
	case ANON_INODE_FS_MAGIC:
	case BDEVFS_MAGIC:
	case BINFMTFS_MAGIC:
	case BPF_FS_MAGIC:
	case BTRFS_SUPER_MAGIC:
	case BTRFS_TEST_MAGIC:
	case CGROUP_SUPER_MAGIC:
	case CGROUP2_SUPER_MAGIC:
	case CRAMFS_MAGIC:
	case DEBUGFS_MAGIC:
	case DEVPTS_SUPER_MAGIC:
	case ECRYPTFS_SUPER_MAGIC:
	case EFS_SUPER_MAGIC:
	case EXT2_SUPER_MAGIC:
	case F2FS_SUPER_MAGIC:
	case FUTEXFS_SUPER_MAGIC:
	case HOSTFS_SUPER_MAGIC:
	case HPFS_SUPER_MAGIC:
	case HUGETLBFS_MAGIC:
	case ISOFS_SUPER_MAGIC:
	case JFFS2_SUPER_MAGIC:
	case MINIX_SUPER_MAGIC:
	case MINIX_SUPER_MAGIC2:
	case MINIX2_SUPER_MAGIC:
	case MINIX2_SUPER_MAGIC2:
	case MINIX3_SUPER_MAGIC:
	case MSDOS_SUPER_MAGIC:
	case MTD_INODE_FS_MAGIC:
	case NILFS_SUPER_MAGIC:
	case NSFS_MAGIC:
	case OPENPROM_SUPER_MAGIC:
	case OVERLAYFS_SUPER_MAGIC:
	case PROC_SUPER_MAGIC:
	case PSTOREFS_MAGIC:
	case QNX4_SUPER_MAGIC:
	case QNX6_SUPER_MAGIC:
	case RAMFS_MAGIC:
	case REISERFS_SUPER_MAGIC:
	case SECURITYFS_MAGIC:
	case SELINUX_MAGIC:
	case SMACK_MAGIC:
	case SOCKFS_MAGIC:
	case SQUASHFS_MAGIC:
	case SYSFS_MAGIC:
	case TMPFS_MAGIC:
	case TRACEFS_MAGIC:
	case UDF_SUPER_MAGIC:
	case USBDEVICE_SUPER_MAGIC:
	case V9FS_MAGIC:
	case XENFS_SUPER_MAGIC:
	case XFS_SUPER_MAGIC:
		return 1;
	default:
		break;
	}
	return 0;
}

/* in addition to handling the watches, this also keeps a mapping of inotify
 * watches to the actual file descriptors, it does so by keeping fixed indexes
 * for each file; watches are registered so that they do not replace each other
 */
static void
set_events(file_info_t *files)
{
	int i;
	file_info_t *file;
	struct statfs sf;

	action = USE_INOTIFY;
	for (i = 0, file = files; i < no_files; i++, file++) {
		if (! file->fp)
			continue;

		if (fstatfs(fileno(file->fp), &sf) == 0 && !fs_is_local(sf.f_type)) {
			action = USE_SLEEP;
			return;
		}

		if (fileno(file->fp) == STDIN_FILENO) {
			action = USE_SLEEP;
			return;
		}
	}

	for (i = 0, file = files; i < no_files; i++, file++) {
		uint32_t mask = IN_MODIFY | IN_MASK_ADD;

		if (! file->fp) {
			ev[i * 2 + 1] = 0;
			continue;
		}

		ev[i * 2 + 1] = fileno(file->fp);

		if (Fflag)
			mask |= IN_DELETE_SELF | IN_MOVE_SELF;

		ev[i * 2] = inotify_add_watch(ifd, file->file_name, mask);
		if (ev[i * 2] < 0)
			err(1, "inotify_add_watch");
	}
}

/*
 * follow -- display the file, from an offset, forward.
 *
 */
void
follow(file_info_t *files, enum STYLE style, off_t off)
{
	int active, ev_change, i, n = -1;
	struct stat sb2;
	file_info_t *file;
	FILE *ftmp;
	struct pollfd fd;

	/* Position each of the files */

	file = files;
	active = 0;
	n = 0;
	for (i = 0; i < no_files; i++, file++) {
		if (file->fp) {
			active = 1;
			n++;
			if (no_files > 1 && !qflag)
				printfn(file->file_name, 1);
			forward(file->fp, file->file_name, style, off, &file->st);
			if (Fflag && fileno(file->fp) != STDIN_FILENO)
				n++;
		}
	}
	if (!Fflag && !active)
		return;

	last = --file;

	ifd = inotify_init1(IN_NONBLOCK);
	if (ifd < 0)
		err(1, "inotify");

	ev = calloc(no_files * 2, sizeof(int));
	if (! ev)
		err(1, "Couldn't allocate memory for watch descriptors.");

	set_events(files);

	fd.fd = ifd;
	fd.events = POLLIN;

	for (;;) {
		ev_change = 0;
		if (Fflag) {
			for (i = 0, file = files; i < no_files; i++, file++) {
				if (!file->fp) {
					file->fp =
					    fopen(file->file_name, "r");
					if (file->fp != NULL &&
					    fstat(fileno(file->fp), &file->st)
					    == -1) {
						fclose(file->fp);
						file->fp = NULL;
					}
					if (file->fp != NULL)
						ev_change++;
					continue;
				}
				if (fileno(file->fp) == STDIN_FILENO)
					continue;
				ftmp = fopen(file->file_name, "r");
				if (ftmp == NULL ||
				    fstat(fileno(file->fp), &sb2) == -1) {
					if (errno != ENOENT)
						ierr(file->file_name);
					show(file);
					if (file->fp != NULL) {
						fclose(file->fp);
						file->fp = NULL;
					}
					if (ftmp != NULL) {
						fclose(ftmp);
					}
					ev_change++;
					continue;
				}

				if (sb2.st_ino != file->st.st_ino ||
				    sb2.st_dev != file->st.st_dev ||
				    sb2.st_nlink == 0) {
					show(file);
					fclose(file->fp);
					file->fp = ftmp;
					memcpy(&file->st, &sb2,
					    sizeof(struct stat));
					ev_change++;
				} else {
					fclose(ftmp);
				}
			}
		}

		for (i = 0, file = files; i < no_files; i++, file++)
			if (file->fp && !show(file))
				ev_change++;

		if (ev_change)
			set_events(files);

		switch (action) {
		case USE_INOTIFY: {
			/*
			 * In the -F case we set a timeout to ensure that
			 * we re-stat the file at least once every second.
			 */
			n = poll(&fd, 1, Fflag ? 1000 : -1);
			if (n < 0)
				err(1, "poll");
			if (n == 0) {
				/* timeout */
				break;
			} else if (fd.revents & POLLIN) {
				struct inotify_event iev;
				ssize_t len = read(ifd, &iev, sizeof(iev));

				if (len < 0 && errno != EAGAIN)
					err(1, "read");

				if (len != sizeof(iev))
					break;

				/* skip name field */
				for (; iev.len > 0; --iev.len) {
					char c;
					if (read(ifd, &c, 1) != 1)
						err(1, "read");
				}

				/* we only care about the file shrinking here */
				if (!(iev.mask & IN_MODIFY))
					break;

				/* locate the event source */
				for (i = 0; i < n; ++i) {
					struct stat st;
					if (ev[i * 2] != iev.wd)
						continue;
					/* ignore watches with a cleared file descriptor */
					if (ev[i * 2 + 1] == 0)
						continue;
					/* located a file, re-stat it and if it's smaller
					 * than its current position, reposition to end */
					if (fstat(ev[i * 2 + 1], &st) < 0)
						err(1, "stat");
					/* all is ok */
					if (st.st_size > lseek(ev[i * 2 + 1], 0, SEEK_CUR))
						break;
					/* reposition */
					if (lseek(ev[i * 2 + 1], 0, SEEK_END) < 0)
						err(1, "lseek");
					break;
				}
			}
			break;
		}
		case USE_SLEEP:
			(void) usleep(250000);
			break;
		}
	}
}
