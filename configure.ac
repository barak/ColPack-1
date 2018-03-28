/************************************************************************************
    Copyright (C) 2005-2008 Assefaw H. Gebremedhin, Arijit Tarafdar, Duc Nguyen,
    Alex Pothen

    This file is part of ColPack.

    ColPack is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.GraphColoring::GraphColoring()

    ColPack is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with ColPack.  If not, see <http://www.gnu.org/licenses/>.
************************************************************************************/

define([COLPACK_VER], [1])
define([COLPACK_SUB], [0])
define([COLPACK_LVL], [10])


AC_INIT([ColPack],[COLPACK_VER.COLPACK_SUB.COLPACK_LVL],[assefaw@eecs.wsu.edu],[ColPack],[http://cscapes.cs.purdue.edu/coloringpage/])
AC_PREREQ([2.57])
AC_CONFIG_SRCDIR([Main/ColPackHeaders.h])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign 1.10 no-define subdir-objects -Wall])
AM_SILENT_RULES([yes])
AC_CONFIG_HEADERS(config.h)
AC_PROG_CXX
AX_CXXFLAGS_WARN_ALL
AC_CONFIG_FILES(Makefile)
AM_PROG_AR
LT_INIT

AC_MSG_CHECKING([Build examples])
AC_ARG_ENABLE([examples],
     [AS_HELP_STRING([--enable-examples],[Build examples])],
     [AS_CASE([${enableval}],
       [yes],[examples=true],
       [no],[examples=false],
       [AC_MSG_ERROR([bad value ${enableval} for --enable-examples])])],
     [examples=false])
AM_CONDITIONAL([EXAMPLES], [test x$examples = xtrue])
AC_MSG_RESULT([$examples])

AC_MSG_CHECKING([OpenMP])
AC_ARG_ENABLE([openmp],
     [AS_HELP_STRING([--disable-openmp],[Disable OpenMP])],
     [AS_CASE([${enableval}],
       [yes],[openmp=true],
       [no],[openmp=false],
       [AC_MSG_ERROR([bad value ${enableval} for --disable-openmp])])],
     [openmp=true])
AM_CONDITIONAL([ENABLE_OPENMP], [test x$openmp = xtrue])
AC_MSG_RESULT([$openmp])

AC_OUTPUT

# echo configuration
AS_ECHO(["-----------------------------------------------------------------------------"])
AS_ECHO(["Configuration:"])
AS_ECHO([""])
AS_ECHO(["  C compiler:                       ${CC}"])
AS_ECHO(["  C++ compiler:                     ${CXX}"])
AS_ECHO(["  Linker:                           ${LD}"])
AS_ECHO(["  Source code location:             `pwd`"])
AS_ECHO(["  Install path:                     ${prefix}"])
AS_ECHO([""])
AS_ECHO(["  CFLAGS:                           ${CFLAGS}"])
AS_ECHO(["  CXXFLAGS:                         ${CXXFLAGS}"])
AS_ECHO([""])
AS_ECHO(["  Use OpenMP:                       ${openmp}"])
AS_ECHO(["  Build examples:                   ${examples}"])
