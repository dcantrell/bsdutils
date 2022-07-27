/* source: musl libc */

#include <string.h>
#include <stddef.h>

#ifndef HAVE_STRLCPY
size_t strlcpy(char *d, const char *s, size_t n) {
    char *d0 = d;

    if (!n--) goto finish;

    for (; n && (*d = *s); n--, s++, d++);
    *d = 0;
finish:
    return d - d0 + strlen(s);
}
#endif

#ifndef HAVE_STRLCAT
size_t strlcat(char *d, const char *s, size_t n) {
    size_t l = strnlen(d, n);
    if (l == n) return l + strlen(s);
    return l + strlcpy(d + l, s, n - l);
}
#endif
