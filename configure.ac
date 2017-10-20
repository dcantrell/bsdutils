AC_PREREQ([2.69])
AC_INIT([bsdutils], [1.0], [david.l.cantrell@gmail.com])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([src/ls/ls.c])
AC_CONFIG_HEADERS([config.h])
LT_INIT
AC_CONFIG_MACRO_DIRS([m4])

# Checks for programs.
AC_PROG_CC
AC_PROG_LN_S

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h langinfo.h limits.h locale.h paths.h stddef.h stdint.h stdlib.h string.h sys/file.h sys/ioctl.h sys/mount.h sys/param.h sys/socket.h sys/time.h syslog.h termios.h unistd.h utmp.h wchar.h wctype.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_UID_T
AC_C_INLINE
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_MODE_T
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_CHECK_MEMBERS([struct stat.st_blksize])
AC_STRUCT_ST_BLOCKS
AC_CHECK_MEMBERS([struct stat.st_rdev])
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_FORK
AC_FUNC_FSEEKO
AC_FUNC_GETGROUPS
AC_FUNC_LSTAT_FOLLOWS_SLASHED_SYMLINK
AC_HEADER_MAJOR
AC_FUNC_MALLOC
AC_FUNC_MBRTOWC
AC_FUNC_MKTIME
AC_FUNC_MMAP
AC_FUNC_REALLOC
AC_FUNC_STRCOLL
AC_FUNC_STRTOD
AC_CHECK_FUNCS([atexit btowc bzero clock_gettime dup2 endpwent ftruncate getcwd getdelim getmntinfo gettimeofday getusershell isascii iswprint lchown localeconv mblen mbrlen memchr memmove memset mkdir mkfifo munmap nl_langinfo realpath regcomp rmdir setenv setlocale strchr strcspn strdup strerror strpbrk strrchr strspn strstr strtol strtoul strtoull uname wcwidth])

# Define UID_MAX from either user-supplied value or /etc/login.defs value.
uid_max=60000
if test -f /etc/login.defs ; then
    new_uid_max="$(grep UID_MAX /etc/login.defs | awk '{ print $2; }')"
    if test ! -z "$new_uid_max" ; then
        uid_max=$new_uid_max
    fi
fi
AC_ARG_WITH([uid_max],
            AS_HELP_STRING([--with-uid_max=VAL],
            [the UID_MAX value for the id command]))
AS_IF([test "x$with_uid_max" != "x"],
      AC_SUBST([UID_MAX], ["$with_uid_max"]),
      AC_SUBST([UID_MAX], ["$uid_max"]))

AC_CONFIG_FILES([Makefile
                 compat/Makefile
                 src/Makefile
                 src/arch/Makefile
                 src/basename/Makefile
                 src/cat/Makefile
                 src/chmod/Makefile
                 src/chroot/Makefile
                 src/comm/Makefile
                 src/cp/Makefile
                 src/csplit/Makefile
                 src/cut/Makefile
                 src/dd/Makefile
                 src/dirname/Makefile
                 src/echo/Makefile
                 src/env/Makefile
                 src/expand/Makefile
                 src/expr/Makefile
                 src/false/Makefile
                 src/fmt/Makefile
                 src/fold/Makefile
                 src/head/Makefile
                 src/id/Makefile
                 src/join/Makefile
                 src/ln/Makefile
                 src/logname/Makefile
                 src/mkdir/Makefile
                 src/mknod/Makefile
                 src/mktemp/Makefile
                 src/mv/Makefile
                 src/nice/Makefile
                 src/nl/Makefile
                 src/nohup/Makefile
                 src/paste/Makefile
                 src/pr/Makefile
                 src/printenv/Makefile
                 src/printf/Makefile
                 src/pwd/Makefile
                 src/readlink/Makefile
                 src/rm/Makefile
                 src/rmdir/Makefile
                 src/sleep/Makefile
                 src/sort/Makefile
                 src/split/Makefile
                 src/stat/Makefile
                 src/stty/Makefile
                 src/sync/Makefile
                 src/tail/Makefile
                 src/tee/Makefile
                 src/test/Makefile
                 src/touch/Makefile
                 src/tr/Makefile
                 src/true/Makefile
                 src/tty/Makefile
                 src/uname/Makefile
                 src/unexpand/Makefile
                 src/uniq/Makefile
                 src/users/Makefile
                 src/who/Makefile
                 src/yes/Makefile])
AC_OUTPUT
