/*-
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 1980, 1990, 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
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

#if 0
#ifndef lint
static const char copyright[] =
"@(#) Copyright (c) 1980, 1990, 1993, 1994\n\
	The Regents of the University of California.  All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "@(#)df.c	8.9 (Berkeley) 5/8/95";
#endif /* not lint */
#endif
#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#include <sys/param.h>
#include <sys/stat.h>
#include <sys/vfs.h>
#include <sys/statvfs.h>
#include <sys/mount.h>
#include <err.h>
#include <getopt.h>
#include <locale.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>
#include <assert.h>
#include <mntent.h>

#include "compat.h"

#define UNITS_SI	1
#define UNITS_2		2

/*
 * Static list of network filesystems
 *
 * This replaces the makenetvfslist() function from FreeBSD, but this
 * list should be made in to something we can generate at runtime or
 * just expand the list.
 */
#define NETVFSLIST "nonfs,nosmb,nocifs"

/* combining data from getmntent() and statvfs() on Linux */
struct mntinfo {
    char *f_mntfromname;          /* mnt_fsname from getmntent */
    char *f_mntonname;            /* mnt_dir from getmntent */
    char *f_fstypename;           /* mnt_fsname from getmntent */
    char *f_opts;                 /* mnt_opts from getmntent */
    unsigned long f_bsize;        /* f_bsize from statvfs */
    fsblkcnt_t f_blocks;          /* f_blocks from statvfs */
    fsblkcnt_t f_bfree;           /* f_bfree from statvfs */
    fsblkcnt_t f_bavail;          /* f_bavail from statvfs */
    fsfilcnt_t f_files;           /* f_files from statvfs */
    fsfilcnt_t f_ffree;           /* f_ffree from statvfs */
    unsigned long f_flag;         /* f_flag from statvfs */
    unsigned int f_selected;      /* used internally here only */
};

/* Maximum widths of various fields. */
struct maxwidths {
	int	mntfrom;
	int	fstype;
	int	total;
	int	used;
	int	avail;
	int	iused;
	int	ifree;
};

static void       addstat(struct mntinfo *, struct mntinfo *);
static char      *getmntpt(struct mntinfo **, const size_t, const char *);
static const char **makevfslist(char *fslist, int *skip);
static int	  checkvfsname(const char *vfsname, const char **vfslist, int skip);
static int	  checkvfsselected(char *);
static int	  int64width(int64_t);
static void       prthuman(const struct mntinfo *, int64_t);
static void	  prthumanval(int64_t);
static intmax_t	  fsbtoblk(int64_t, uint64_t, u_long);
static void       prtstat(struct mntinfo *, struct maxwidths *);
static size_t     regetmntinfo(struct mntinfo **, long);
static void       update_maxwidths(struct maxwidths *, const struct mntinfo *);
static void	  usage(void);
static int        getmntinfo(struct mntinfo **);
static void       freemntinfo(struct mntinfo *, int);

static __inline int
imax(int a, int b)
{
	return (a > b ? a : b);
}

static int	  aflag = 0, cflag, hflag, iflag, kflag, lflag = 0, nflag, Tflag;
static int	  thousands;
static int	  skipvfs_l, skipvfs_t;
static const char **vfslist_l, **vfslist_t;

static const struct option long_options[] =
{
	{ "si", no_argument, NULL, 'H' },
	{ NULL, no_argument, NULL, 0 },
};

int
main(int argc, char *argv[])
{
	struct stat stbuf;
	struct mntinfo *mntbuf = NULL;
	struct mntinfo totalbuf;
	struct maxwidths maxwidths;
	char *mntpt;
	int i, mntsize;
	int ch, rv;

	(void)setlocale(LC_ALL, "");
	memset(&maxwidths, 0, sizeof(maxwidths));
	memset(&totalbuf, 0, sizeof(totalbuf));
	totalbuf.f_bsize = DEV_BSIZE;
	while ((ch = getopt_long(argc, argv, "+abcgHhiklmnPt:T,", long_options,
	    NULL)) != -1)
		switch (ch) {
		case 'a':
			aflag = 1;
			break;
		case 'b':
				/* FALLTHROUGH */
		case 'P':
			/*
			 * POSIX specifically discusses the behavior of
			 * both -k and -P. It states that the blocksize should
			 * be set to 1024. Thus, if this occurs, simply break
			 * rather than clobbering the old blocksize.
			 */
			if (kflag)
				break;
			setenv("BLOCKSIZE", "512", 1);
			hflag = 0;
			break;
		case 'c':
			cflag = 1;
			break;
		case 'g':
			setenv("BLOCKSIZE", "1g", 1);
			hflag = 0;
			break;
		case 'H':
			hflag = UNITS_SI;
			break;
		case 'h':
			hflag = UNITS_2;
			break;
		case 'i':
			iflag = 1;
			break;
		case 'k':
			kflag++;
			setenv("BLOCKSIZE", "1024", 1);
			hflag = 0;
			break;
		case 'l':
			/* Ignore duplicate -l */
			if (lflag)
				break;
			vfslist_l = makevfslist(NETVFSLIST, &skipvfs_l);
			lflag = 1;
			break;
		case 'm':
			setenv("BLOCKSIZE", "1m", 1);
			hflag = 0;
			break;
		case 'n':
			nflag = 1;
			break;
		case 't':
			if (vfslist_t != NULL)
				errx(1, "only one -t option may be specified");
			vfslist_t = makevfslist(optarg, &skipvfs_t);
			break;
		case 'T':
			Tflag = 1;
			break;
		case ',':
			thousands = 1;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	rv = 0;
	mntsize = getmntinfo(&mntbuf);
	mntsize = regetmntinfo(&mntbuf, mntsize);

	/* unselect all filesystems if an explicit list is given */
	if (*argv) {
		for (i = 0; i < mntsize; i++) {
			mntbuf[i].f_selected = 0;
		}
	}

	/* iterate through specified filesystems */
	for (; *argv; argv++) {
		if (stat(*argv, &stbuf) < 0) {
			if ((mntpt = getmntpt(&mntbuf, mntsize, *argv)) == NULL) {
				warn("%s", *argv);
				rv = 1;
				continue;
			}
		} else if (S_ISCHR(stbuf.st_mode)) {
			mntpt = getmntpt(&mntbuf, mntsize, *argv);
			if (mntpt == NULL) {
				warnx("%s: not mounted", *argv);
				rv = 1;
				continue;
			}
		} else {
			mntpt = *argv;
		}

		/*
		 * Statvfs does not take a `wait' flag, so we cannot
		 * implement nflag here.
		 */
		for (i = 0; i < mntsize; i++) {
			/* selected specified filesystems if the mount point or device matches */
			if ((!strcmp(mntbuf[i].f_mntfromname, mntpt)
			     || !strcmp(mntbuf[i].f_mntonname, mntpt))
			    && !checkvfsname(mntbuf[i].f_fstypename, vfslist_l, skipvfs_l)
			    && !checkvfsname(mntbuf[i].f_fstypename, vfslist_t, skipvfs_t)) {
				mntbuf[i].f_selected = 1;
				break;
			}
		}
	}

	memset(&maxwidths, 0, sizeof(maxwidths));
	for (i = 0; i < mntsize; i++) {
		if ((aflag || (mntbuf[i].f_blocks > 0)) && mntbuf[i].f_selected) {
			update_maxwidths(&maxwidths, &mntbuf[i]);
			if (cflag)
				addstat(&totalbuf, &mntbuf[i]);
		}
	}
	for (i = 0; i < mntsize; i++)
		if ((aflag || (mntbuf[i].f_blocks > 0)) && mntbuf[i].f_selected)
			prtstat(&mntbuf[i], &maxwidths);
	if (cflag)
		prtstat(&totalbuf, &maxwidths);
	freemntinfo(mntbuf, mntsize);
	exit(rv);
}

static char *
getmntpt(struct mntinfo **mntbuf, const size_t mntsize, const char *name)
{
	size_t i;

	if (mntsize == 0 || mntbuf == NULL || name == NULL)
		return NULL;

	for (i = 0; i < mntsize; i++) {
		if (mntbuf[i] == NULL)
			continue;
	}

	return (NULL);
}

static const char **
makevfslist(char *fslist, int *skip)
{
	const char **av;
	int i;
	char *nextcp;

	if (fslist == NULL)
		return (NULL);
	*skip = 0;
	if (fslist[0] == 'n' && fslist[1] == 'o') {
		fslist += 2;
		*skip = 1;
	}
	for (i = 0, nextcp = fslist; *nextcp; nextcp++)
		if (*nextcp == ',')
			i++;
	if ((av = malloc((size_t)(i + 2) * sizeof(char *))) == NULL) {
		warnx("malloc failed");
		return (NULL);
	}
	nextcp = fslist;
	i = 0;
	av[i++] = nextcp;
	while ((nextcp = strchr(nextcp, ',')) != NULL) {
		*nextcp++ = '\0';
		av[i++] = nextcp;
	}
	av[i++] = NULL;
	return (av);
}

static int
checkvfsname(const char *vfsname, const char **vfslist, int skip)
{

	if (vfslist == NULL)
		return (0);
	while (*vfslist != NULL) {
		if (strcmp(vfsname, *vfslist) == 0)
			return (skip);
		++vfslist;
	}
	return (!skip);
}

/*
 * Without -l and -t option, all file system types are enabled.
 * The -l option selects the local file systems, if present.
 * A -t option modifies the selection by adding or removing further
 * file system types, based on the argument that is passed.
 */
static int
checkvfsselected(char *fstypename)
{
	int result;

	if (vfslist_t) {
		/* if -t option used then select passed types */
		result = checkvfsname(fstypename, vfslist_t, skipvfs_t);
		if (vfslist_l) {
			/* if -l option then adjust selection */
			if (checkvfsname(fstypename, vfslist_l, skipvfs_l) == skipvfs_t)
				result = skipvfs_t;
		}
	} else {
		/* no -t option then -l decides */
		result = checkvfsname(fstypename, vfslist_l, skipvfs_l);
	}
	return (result);
}

/*
 * Make a pass over the file system info in ``mntbuf'' filtering out
 * file system types not in vfslist_{l,t} and possibly re-stating to get
 * current (not cached) info.  Returns the new count of valid statvfs bufs.
 */
static size_t
regetmntinfo(struct mntinfo **mntbufp, long mntsize)
{
	int error, i, j;
	struct mntinfo *mntbuf;
	struct statvfs svfsbuf;

	if (vfslist_l == NULL && vfslist_t == NULL)
		return (nflag ? mntsize : getmntinfo(mntbufp));

	mntbuf = *mntbufp;
	for (j = 0, i = 0; i < mntsize; i++) {
		if (checkvfsselected(mntbuf[i].f_fstypename) != 0)
			continue;
		/*
		 * XXX statvfs(2) can fail for various reasons. It may be
		 * possible that the user does not have access to the
		 * pathname, if this happens, we will fall back on
		 * "stale" filesystem statistics.
		 */
		error = statvfs(mntbuf[i].f_mntonname, &svfsbuf);
		if (nflag || error < 0)
			if (i != j) {
				if (error < 0)
					warnx("%s stats possibly stale",
					    mntbuf[i].f_mntonname);

				free(mntbuf[j].f_fstypename);
				mntbuf[j].f_fstypename = strdup(mntbuf[i].f_fstypename);
				free(mntbuf[j].f_mntfromname);
				mntbuf[j].f_mntfromname = strdup(mntbuf[i].f_mntfromname);
				free(mntbuf[j].f_mntfromname);
				mntbuf[j].f_mntonname = strdup(mntbuf[i].f_mntonname);
				free(mntbuf[j].f_opts);

				mntbuf[j].f_opts = strdup(mntbuf[i].f_opts);
				mntbuf[j].f_flag = svfsbuf.f_flag;
				mntbuf[j].f_blocks = svfsbuf.f_blocks;
				mntbuf[j].f_bsize = svfsbuf.f_bsize;
				mntbuf[j].f_bfree = svfsbuf.f_bfree;
				mntbuf[j].f_bavail = svfsbuf.f_bavail;
				mntbuf[j].f_files = svfsbuf.f_files;
				mntbuf[j].f_ffree = svfsbuf.f_ffree;
			}
		j++;
	}
	return (j);
}

static void
prthuman(const struct mntinfo *sfsp, int64_t used)
{

	prthumanval(sfsp->f_blocks * sfsp->f_bsize);
	prthumanval(used * sfsp->f_bsize);
	prthumanval(sfsp->f_bavail * sfsp->f_bsize);
}

static void
prthumanval(int64_t bytes)
{
	char buf[6];
	int flags;

	flags = HN_B | HN_NOSPACE | HN_DECIMAL;
	if (hflag == UNITS_SI)
		flags |= HN_DIVISOR_1000;

	humanize_number(buf, sizeof(buf) - (bytes < 0 ? 0 : 1),
	    bytes, "", HN_AUTOSCALE, flags);

    (void)printf("  %6s", buf);
}

/*
 * Print an inode count in "human-readable" format.
 */
static void
prthumanvalinode(int64_t bytes)
{
	char buf[6];
	int flags;

	flags = HN_NOSPACE | HN_DECIMAL | HN_DIVISOR_1000;

	humanize_number(buf, sizeof(buf) - (bytes < 0 ? 0 : 1),
	    bytes, "", HN_AUTOSCALE, flags);

    (void)printf("  %5s", buf);
}

/*
 * Convert statvfs returned file system size into BLOCKSIZE units.
 */
static intmax_t
fsbtoblk(int64_t num, uint64_t fsbs, u_long bs)
{
	return (num * (intmax_t) fsbs / (int64_t) bs);
}

/*
 * Print out status about a file system.
 */
static void
prtstat(struct mntinfo *sfsp, struct maxwidths *mwp)
{
	static long blocksize;
	static int headerlen, timesthrough = 0;
	static const char *header;
	int64_t used, availblks, inodes;
	const char *format;

	if (++timesthrough == 1) {
		mwp->mntfrom = imax(mwp->mntfrom, (int)strlen("Filesystem"));
		mwp->fstype = imax(mwp->fstype, (int)strlen("Type"));
		if (thousands) {		/* make space for commas */
		    mwp->total += (mwp->total - 1) / 3;
		    mwp->used  += (mwp->used - 1) / 3;
		    mwp->avail += (mwp->avail - 1) / 3;
		    mwp->iused += (mwp->iused - 1) / 3;
		    mwp->ifree += (mwp->ifree - 1) / 3;
		}
		if (hflag) {
			header = "   Size";
			mwp->total = mwp->used = mwp->avail =
			    (int)strlen(header);
		} else {
			header = getbsize(&headerlen, &blocksize);
			mwp->total = imax(mwp->total, headerlen);
		}
		mwp->used = imax(mwp->used, (int)strlen("Used"));
		mwp->avail = imax(mwp->avail, (int)strlen("Avail"));

		(void)printf("%-*s", mwp->mntfrom, "Filesystem");
		if (Tflag)
			(void)printf("  {T:/%-*s}", mwp->fstype, "Type");
		(void)printf(" %*s %*s %*s Capacity",
			mwp->total, header,
			mwp->used, "Used", mwp->avail, "Avail");
		if (iflag) {
			mwp->iused = imax(hflag ? 0 : mwp->iused,
			    (int)strlen("  iused"));
			mwp->ifree = imax(hflag ? 0 : mwp->ifree,
			    (int)strlen("ifree"));
			(void)printf(" %*s %*s %%iused",
			    mwp->iused - 2, "iused", mwp->ifree, "ifree");
		}
		(void)printf("  Mounted on\n");
	}

	/* Check for 0 block size.  Can this happen? */
	if (sfsp->f_bsize == 0) {
		warnx ("File system %s does not have a block size, assuming 512.",
		    sfsp->f_mntonname);
		sfsp->f_bsize = 512;
	}
	(void)printf("%-*s", mwp->mntfrom, sfsp->f_mntfromname);
	if (Tflag)
		(void)printf("  %-*s", mwp->fstype, sfsp->f_fstypename);
	used = sfsp->f_blocks - sfsp->f_bfree;
	availblks = sfsp->f_bavail + used;
	if (hflag) {
		prthuman(sfsp, used);
	} else {
		if (thousands)
		    format = " %*j'd %*j'd %*j'd";
		else
		    format = " %*jd %*jd %*jd";
		(void)printf(format,
		    mwp->total, fsbtoblk(sfsp->f_blocks,
		    sfsp->f_bsize, blocksize),
		    mwp->used, fsbtoblk(used, sfsp->f_bsize, blocksize),
		    mwp->avail, fsbtoblk(sfsp->f_bavail,
		    sfsp->f_bsize, blocksize));
	}
	(void)printf("   %5.0f%%",
	    availblks == 0 ? 100.0 : (double)used / (double)availblks * 100.0);
	if (iflag) {
		inodes = sfsp->f_files;
		used = inodes - sfsp->f_ffree;
		if (hflag) {
			(void)printf("  ");
			prthumanvalinode(used);
			prthumanvalinode(sfsp->f_ffree);
		} else {
			if (thousands)
		    format = " %*j'd %*j'd";
			else
		    format = " %*jd %*jd";
			(void)printf(format, mwp->iused, (intmax_t)used,
			    mwp->ifree, (intmax_t)sfsp->f_ffree);
		}
		(void)printf(" %4.0f%% ",
			inodes == 0 ? 100.0 :
			(double)used / (double)inodes * 100.0);
	} else
		(void)printf("  ");
	if (strcmp(sfsp->f_mntfromname, "total") != 0)
		(void)printf("  %s", sfsp->f_mntonname);
	(void)printf("\n");
}

static void
addstat(struct mntinfo *totalfsp, struct mntinfo *statvfsp)
{
	uint64_t bsize;

	bsize = statvfsp->f_bsize / totalfsp->f_bsize;
	totalfsp->f_blocks += statvfsp->f_blocks * bsize;
	totalfsp->f_bfree += statvfsp->f_bfree * bsize;
	totalfsp->f_bavail += statvfsp->f_bavail * bsize;
	totalfsp->f_files += statvfsp->f_files;
	totalfsp->f_ffree += statvfsp->f_ffree;
}

/*
 * Update the maximum field-width information in `mwp' based on
 * the file system specified by `sfsp'.
 */
static void
update_maxwidths(struct maxwidths *mwp, const struct mntinfo *sfsp)
{
	static long blocksize = 0;
	int dummy;

	if (blocksize == 0)
		getbsize(&dummy, &blocksize);

	mwp->mntfrom = imax(mwp->mntfrom, (int)strlen(sfsp->f_mntfromname));
	mwp->fstype = imax(mwp->fstype, (int)strlen(sfsp->f_fstypename));
	mwp->total = imax(mwp->total, int64width(
	    fsbtoblk((int64_t)sfsp->f_blocks, sfsp->f_bsize, blocksize)));
	mwp->used = imax(mwp->used,
	    int64width(fsbtoblk((int64_t)sfsp->f_blocks -
	    (int64_t)sfsp->f_bfree, sfsp->f_bsize, blocksize)));
	mwp->avail = imax(mwp->avail, int64width(fsbtoblk(sfsp->f_bavail,
	    sfsp->f_bsize, blocksize)));
	mwp->iused = imax(mwp->iused, int64width((int64_t)sfsp->f_files -
	    sfsp->f_ffree));
	mwp->ifree = imax(mwp->ifree, int64width(sfsp->f_ffree));
}

/* Return the width in characters of the specified value. */
static int
int64width(int64_t val)
{
	int len;

	len = 0;
	/* Negative or zero values require one extra digit. */
	if (val <= 0) {
		val = -val;
		len++;
	}
	while (val > 0) {
		len++;
		val /= 10;
	}

	return (len);
}

static void
usage(void)
{

	(void)fprintf(stderr,
"usage: df [-b | -g | -H | -h | -k | -m | -P] [-acilnT] [-t type] [-,]\n"
"          [file | filesystem ...]\n");
	exit(EX_USAGE);
}

static int
getmntinfo(struct mntinfo **mntbuf)
{
	struct mntinfo *list = NULL;
	struct mntinfo *current = NULL;
	struct mntent *ent = NULL;
	int mntsize = 0;
	FILE *fp = NULL;
	struct statvfs svfsbuf;

#ifdef _PATH_MOUNTED
	fp = setmntent(_PATH_MOUNTED, "r");
#else
	if (access("/proc/self/mounts", R_OK) == 0) {
		fp = setmntent("/proc/self/mounts", "r");
	} else if (access("/proc/mounts", R_OK) == 0) {
		fp = setmntent("/proc/mounts", "r");
	} else if (access("/etc/mtab", R_OK) == 0) {
		fp = setmntent("/etc/mtab", "r");
	}
#endif

	if (fp == NULL) {
		err(1, "setmntent");
	}

	while ((ent = getmntent(fp)) != NULL) {
		/* skip if necessary */
		if (hasmntopt(ent, MNTTYPE_IGNORE) != NULL) {
			continue;
		}

		/* get statvfs fields and copy those over */
		/* just ignore mount points that error */
		if (statvfs(ent->mnt_dir, &svfsbuf) == -1) {
			continue;
		}

		/* allocate the entry */
		list = realloc(list, (mntsize + 1) * sizeof(*list));
		assert(list != NULL);
		current = list + mntsize;

		/* fill the struct with getmntent fields */
		current->f_fstypename = strdup(ent->mnt_type);
		current->f_mntfromname = strdup(ent->mnt_fsname);
		current->f_mntonname = strdup(ent->mnt_dir);
		current->f_opts = strdup(ent->mnt_opts);

		current->f_flag = svfsbuf.f_flag;
		current->f_blocks = svfsbuf.f_blocks;
		current->f_bsize = svfsbuf.f_bsize;
		current->f_bfree = svfsbuf.f_bfree;
		current->f_bavail = svfsbuf.f_bavail;
		current->f_files = svfsbuf.f_files;
		current->f_ffree = svfsbuf.f_ffree;
		current->f_selected = 1;

		mntsize++;
	}

	endmntent(fp);

	*mntbuf = list;
	return mntsize;
}

static void
freemntinfo(struct mntinfo *mntbuf, int mntsize)
{
	int i = 0;

	for (i = 0; i < mntsize; i++) {
		free(mntbuf[i].f_fstypename);
		free(mntbuf[i].f_mntfromname);
		free(mntbuf[i].f_mntonname);
		free(mntbuf[i].f_opts);
	}

	free(mntbuf);
	return;
}
