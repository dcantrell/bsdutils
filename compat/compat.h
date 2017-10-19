/*
 * compat.h
 * Local prototype definitions for functions put together in this library.
 * We don't have the full OpenBSD system headers, so use this header file
 * to be a placeholder.
 */

/* reallocarray.c */
void *reallocarray(void *, size_t, size_t);

/* setmode.c */
mode_t getmode(const void *, mode_t);
void *setmode(const char *);

/* strtonum.c */
long long strtonum(const char *, long long, long long, const char **);
