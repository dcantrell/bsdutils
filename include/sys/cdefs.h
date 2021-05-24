#ifndef CDEFS_H
#define CDEFS_H

#define __FBSDID(x)
#define __SCCSID(x)

#ifdef  __cplusplus
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS }
#else
# define __BEGIN_DECLS
# define __END_DECLS
#endif

#define __dead2
#define __printf0like(x, y)

#endif
