#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(src/main.c)
AM_INIT_AUTOMAKE(Take_6,0.1)
AC_CONFIG_SRCDIR([src/game.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([memory.h stdint.h stdlib.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_INT32_T

# Checks for library functions.
AC_CHECK_FUNCS([memset])

AC_OUTPUT(Makefile)
