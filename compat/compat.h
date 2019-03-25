/*
 * compat.h
 * Local prototype definitions for functions put together in this library.
 * We don't have the full OpenBSD system headers, so use this header file
 * to be a placeholder.
 */

/* setmode.c */
mode_t getmode(const void *, mode_t);
void *setmode(const char *);

/* strtonum.c */
long long strtonum(const char *, long long, long long, const char **);

/* strmode.c */
void strmode(int, char *);

/* pwcache.c */
char *user_from_uid(uid_t, int);
char *group_from_gid(gid_t, int);

/* logwtmp.c */
void logwtmp(const char *, const char *, const char *);

/* fmt_scaled.c */
int scan_scaled(char *, long long *);
int fmt_scaled(long long, char *);

/* getbsize.c */
char *getbsize(int *, long *);

/* devname.c */
char *devname(dev_t, mode_t);

/* merge.c */
int mergesort(void *, size_t, size_t, int (*)(const void *, const void *));

/* heapsort.c */
int heapsort(void *, size_t, size_t, int (*)(const void *, const void *));

/* recallocarray.c */
void *recallocarray(void *, size_t, size_t, size_t);

/*
 * MAXBSIZE does not exist on Linux because filesystem block size
 * limits are per filesystem and not consistently enforced across
 * the different filesystems.  If you look at e2fsprogs and its
 * header files, you'll see the max block size is defined as 65536
 * via (1 << EXT2_MAX_BLOCK_LOG_SIZE) where EXT2_MAX_BLOCK_LOG_SIZE
 * is 16.  On OpenBSD, MAXBSIZE is simply (64 * 1024), which is
 * 65536.  So we'll just define that here so as to avoid having
 * bsdutils depend on e2fsprogs to compile.
 */
#define MAXBSIZE (64 * 1024)

/*
 * fmt_scaled(3) specific flags.
 * This comes from lib/libutil/util.h in the OpenBSD source.
 */
#define	FMT_SCALED_STRSIZE	7	/* minus sign, 4 digits, suffix, null byte */
