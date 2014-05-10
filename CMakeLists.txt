
project(SUITESPARSE)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE Debug)

include_directories ("${PROJECT_SOURCE_DIR}/src/SuiteSparse_config")

add_definitions ("-std=c11 -Wall -Wno-long-long -pedantic -DG_MESSAGES_DEBUG")
add_definitions ("-O3 -fexceptions -fPIC")
add_definitions ("-DNTIMER")

# CF = $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH)


set(ENV{G_MESSAGES_DEBUG} all)

#===============================================================================
# SuiteSparse_config.mk:  common configuration file for the SuiteSparse
#===============================================================================

# This file contains all configuration settings for all packages authored or
# co-authored by Tim Davis:
#
# Package Version       Description
# ------- -------       -----------
# AMD	  1.2 or later  approximate minimum degree ordering
# COLAMD  2.4 or later  column approximate minimum degree ordering
# CCOLAMD 1.0 or later  constrained column approximate minimum degree ordering
# CAMD    any		constrained approximate minimum degree ordering
# UMFPACK 4.5 or later	sparse LU factorization, with the BLAS
# CHOLMOD any		sparse Cholesky factorization, update/downdate
# KLU	  0.8 or later  sparse LU factorization, BLAS-free
# BTF	  0.8 or later  permutation to block triangular form
# LDL	  1.2 or later	concise sparse LDL'
# CXSparse any		extended version of CSparse (int/long, real/complex)
# SuiteSparseQR	any	sparse QR factorization
# RBio    2.0 or later  read/write sparse matrices in Rutherford-Boeing format
#
# By design, this file is NOT included in the CSparse makefile.
# That package is fully stand-alone.  CSparse is primarily for teaching;
# production code should use CXSparse.
#
# The SuiteSparse_config directory and the above packages should all appear in
# a single directory, in order for the Makefile's within each package to find
# this file.
#
# To enable an option of the form "# OPTION = ...", edit this file and
# delete the "#" in the first column of the option you wish to use.
#
# The use of METIS 4.0.1 is optional.  To exclude METIS, you must compile with
# CHOLMOD_CONFIG set to -DNPARTITION.  See below for details.  However, if you
# do not have a metis-4.0 directory inside the SuiteSparse directory, the
# */Makefile's that optionally rely on METIS will automatically detect this
# and compile without METIS.

#------------------------------------------------------------------------------
# Generic configuration
#------------------------------------------------------------------------------

# Using standard definitions from the make environment, typically:
#
#   CC              cc      C compiler
#   CXX             g++     C++ compiler
#   CFLAGS          [ ]     flags for C and C++ compiler
#   CPPFLAGS        [ ]     flags for C and C++ compiler
#   TARGET_ARCH     [ ]     target architecture
#   FFLAGS          [ ]     flags for Fortran compiler
#   RM              rm -f   delete a file
#   AR              ar      create a static *.a library archive
#   ARFLAGS         rv      flags for ar
#   MAKE            make    make itself (sometimes called gmake)
#
# You can redefine them here, but by default they are used from the
# default make environment.

# C and C++ compiler flags.  The first three are standard for *.c and *.cpp
# Add -DNTIMER if you do use any timing routines (otherwise -lrt is required).


#------------------------------------------------------------------------------
# BLAS and LAPACK configuration:
#------------------------------------------------------------------------------

# UMFPACK and CHOLMOD both require the BLAS.  CHOLMOD also requires LAPACK.
# See Kazushige Goto's BLAS at http://www.cs.utexas.edu/users/flame/goto/ or
# http://www.tacc.utexas.edu/~kgoto/ for the best BLAS to use with CHOLMOD.
# LAPACK is at http://www.netlib.org/lapack/ .  You can use the standard
# Fortran LAPACK along with Goto's BLAS to obtain very good performance.
# CHOLMOD gets a peak numeric factorization rate of 3.6 Gflops on a 3.2 GHz
# Pentium 4 (512K cache, 4GB main memory) with the Goto BLAS, and 6 Gflops
# on a 2.5Ghz dual-core AMD Opteron.

# These settings will probably not work, since there is no fixed convention for
# naming the BLAS and LAPACK library (*.a or *.so) files.

# This is probably slow ... it might connect to the Standard Reference BLAS:
##BLAS = -lblas -lgfortran
##LAPACK = -llapack

# NOTE: this next option for the "Goto BLAS" has nothing to do with a "goto"
# statement.  Rather, the Goto BLAS is written by Dr. Kazushige Goto.
# Using the Goto BLAS:
# BLAS = -lgoto -lgfortran -lgfortranbegin
# BLAS = -lgoto2 -lgfortran -lgfortranbegin -lpthread

# Using non-optimized versions:
# BLAS = -lblas_plain -lgfortran -lgfortranbegin
# LAPACK = -llapack_plain

# BLAS = -lblas_plain -lgfortran -lgfortranbegin
# LAPACK = -llapack

# The BLAS might not contain xerbla, an error-handling routine for LAPACK and
# the BLAS.  Also, the standard xerbla requires the Fortran I/O library, and
# stops the application program if an error occurs.  A C version of xerbla
# distributed with this software (SuiteSparse_config/xerbla/libcerbla.a)
# includes a Fortran-callable xerbla routine that prints nothing and does not
# stop the application program.  This is optional.

# XERBLA = ../../SuiteSparse_config/xerbla/libcerbla.a 

# If you wish to use the XERBLA in LAPACK and/or the BLAS instead,
# use this option:
# XERBLA = 

# If you wish to use the Fortran SuiteSparse_config/xerbla/xerbla.f instead,
# use this:

# XERBLA = ../../SuiteSparse_config/xerbla/libxerbla.a 


#------------------------------------------------------------------------------
# Linux
#------------------------------------------------------------------------------

# Using default compilers:
# CC = gcc
# CF = $(CFLAGS) -O3 -fexceptions

# alternatives:
# CF = $(CFLAGS) -g -fexceptions \
#   	-Wall -W -Wshadow -Wmissing-prototypes -Wstrict-prototypes \
#    	-Wredundant-decls -Wnested-externs -Wdisabled-optimization -ansi \
#        -funit-at-a-time
# CF = $(CFLAGS) -O3 -fexceptions \
#   	-Wall -W -Werror -Wshadow -Wmissing-prototypes -Wstrict-prototypes \
#    	-Wredundant-decls -Wnested-externs -Wdisabled-optimization -ansi
# CF = $(CFLAGS) -O3 -fexceptions -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE
# CF = $(CFLAGS) -O3
# CF = $(CFLAGS) -O3 -g -fexceptions
# CF = $(CFLAGS) -g -fexceptions \
#   	-Wall -W -Wshadow \
#    	-Wredundant-decls -Wdisabled-optimization -ansi

# consider:
# -fforce-addr -fmove-all-movables -freduce-all-givs -ftsp-ordering
# -frename-registers -ffast-math -funroll-loops

# Using the Goto BLAS:
# BLAS = -lgoto -lfrtbegin -lg2c $(XERBLA) -lpthread

# Using Intel's icc and ifort compilers:
#   (does not work for mexFunctions unless you add a mexopts.sh file)
# F77 = ifort
# CC = icc
# CF = $(CFLAGS) -O3 -xN -vec_report=0
# CF = $(CFLAGS) -g

# 64bit:
# F77FLAGS = -O -m64
# CF = $(CFLAGS) -O3 -fexceptions -m64
# BLAS = -lgoto64 -lfrtbegin -lg2c -lpthread $(XERBLA)
# LAPACK = -llapack64

# SUSE Linux 10.1, AMD Opteron, with GOTO Blas
# F77 = gfortran
# BLAS = -lgoto_opteron64 -lgfortran

# SUSE Linux 10.1, Intel Pentium, with GOTO Blas
# F77 = gfortran
# BLAS = -lgoto -lgfortran

#------------------------------------------------------------------------------
# Mac
#------------------------------------------------------------------------------

# As recommended by macports, http://suitesparse.darwinports.com/
# I've tested them myself on Mac OSX 10.6.1 and 10.6.8 (Snow Leopard),
# on my MacBook Air, and they work fine.

# F77 = gfortran
# CF = $(CFLAGS) -O3 -fno-common -fexceptions -DNTIMER
# BLAS = -framework Accelerate
# LAPACK = -framework Accelerate
# LIB = -lm

#------------------------------------------------------------------------------
# Solaris
#------------------------------------------------------------------------------

# 32-bit
# CF = $(CFLAGS) -KPIC -dalign -xc99=%none -Xc -xlibmieee -xO5 -xlibmil -m32

# 64-bit
# CF = $(CFLAGS) -fast -KPIC -xc99=%none -xlibmieee -xlibmil -m64 -Xc

# FFLAGS = -fast -KPIC -dalign -xlibmil -m64

# The Sun Performance Library includes both LAPACK and the BLAS:
# BLAS = -xlic_lib=sunperf
# LAPACK =


#------------------------------------------------------------------------------
# Compaq Alpha
#------------------------------------------------------------------------------

# 64-bit mode only
# CF = $(CFLAGS) -O2 -std1
# BLAS = -ldxml
# LAPACK =

#------------------------------------------------------------------------------
# IBM RS 6000
#------------------------------------------------------------------------------

# BLAS = -lessl
# LAPACK =

# 32-bit mode:
# CF = $(CFLAGS) -O4 -qipa -qmaxmem=16384 -qproto
# F77FLAGS = -O4 -qipa -qmaxmem=16384

# 64-bit mode:
# CF = $(CFLAGS) -O4 -qipa -qmaxmem=16384 -q64 -qproto
# F77FLAGS = -O4 -qipa -qmaxmem=16384 -q64

#------------------------------------------------------------------------------
# SGI IRIX
#------------------------------------------------------------------------------

# BLAS = -lscsl
# LAPACK =

# 32-bit mode
# CF = $(CFLAGS) -O

# 64-bit mode (32 bit int's and 64-bit long's):
# CF = $(CFLAGS) -64
# F77FLAGS = -64

# SGI doesn't have ranlib
# RANLIB = echo

#------------------------------------------------------------------------------
# AMD Opteron (64 bit)
#------------------------------------------------------------------------------

# BLAS = -lgoto_opteron64 -lg2c
# LAPACK = -llapack_opteron64

# SUSE Linux 10.1, AMD Opteron
# F77 = gfortran
# BLAS = -lgoto_opteron64 -lgfortran
# LAPACK = -llapack_opteron64

add_subdirectory(src)

add_subdirectory(test)

##add_subdirectory(doc)

if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # This is tested
  ##set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
  ##set_property( TARGET main APPEND_STRING PROPERTY COMPILE_FLAGS -Wall )
endif (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

if(MSVC)
    # This is untested
    ##set_property( TARGET main APPEND_STRING PROPERTY COMPILE_FLAGS /W3 )
endif (MSVC)
