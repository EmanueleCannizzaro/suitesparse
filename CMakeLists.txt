# -----------------------------------------------------------------
# CMake build system for SuiteSparse
#  http://code.google.com/p/suitesparse-metis-for-windows/
# Created by Jose Luis Blanco (University of Almeria) 2013-2014
# Updated by jesnault (jerome.esnault@inria.fr) 2014-01-21
# -----------------------------------------------------------------

project(suitesparse)

option(SUITESPARSE_HAS_VERSION_FUNCTION OFF)
option(SUITESPARSE_DATE "April 25, 2013")

set(SUITESPARSE_VERSION_MAJOR 4)
set(SUITESPARSE_VERSION_MINOR 2)
set(SUITESPARSE_VERSION_PATCH 1)

cmake_minimum_required(VERSION 2.8.10)

##include(checkGetSuiteSparse.cmake)
##set(CMAKE_BUILD_TYPE Debug)

include_directories ("${PROJECT_SOURCE_DIR}/src/SuiteSparse_config")

option(BUILD_SHARED ON)
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "x86_64")
set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib64/linux" CACHE PATH "Output directory for libraries")
set(CMAKE_SHARED_LIBRARY_SUFFIX "-x86-64.so")
set(CMAKE_STATIC_LIBRARY_SUFFIX "-x86-64.a")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin/linux" CACHE PATH "Output directory for applications")
set(CMAKE_EXECUTABLE_SUFFIX "-x86-64")

#------------------------------------------------------------------------------
# AMD Opteron (64 bit)
#------------------------------------------------------------------------------
# BLAS = -lgoto_opteron64 -lg2c
# LAPACK = -llapack_opteron64
# SUSE Linux 10.1, AMD Opteron
# F77 = gfortran
# BLAS = -lgoto_opteron64 -lgfortran
# LAPACK = -llapack_opteron64
elseif(${CMAKE_SYSTEM_PROCESSOR} MATCHES "x86")
set(LIBRARY_OUTPUT_PATH "${PROJECT_BNARY_DIR}/lib32/linux")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BNARY_DIR}/bin/linux")
endif(${CMAKE_SYSTEM_PROCESSOR} MATCHES "x86_64")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
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
elseif(${CMAKE_SYSTEM_NAME} MATCHES "SunOS")
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
elseif(${CMAKE_SYSTEM_NAME} MATCHES "SunOS")
#------------------------------------------------------------------------------
# Compaq Alpha
#------------------------------------------------------------------------------
# 64-bit mode only
# CF = $(CFLAGS) -O2 -std1
# BLAS = -ldxml
# LAPACK =
elseif(${CMAKE_SYSTEM_NAME} MATCHES "SunOS")
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
elseif(${CMAKE_SYSTEM_NAME} MATCHES "IRIX")
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
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")


if(CMAKE_SYSTEM_VERSION)
endif(CMAKE_SYSTEM_VERSION)

if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # This is tested
  ##set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
# -O3 -fexceptions
#add_definitions ("-std=c11 -Wall -Wno-long-long -pedantic -DG_MESSAGES_DEBUG")
#add_definitions ("-O3 -fexceptions -fPIC")
#-g -fexceptions \
#   	-Wall -W -Wshadow -Wmissing-prototypes -Wstrict-prototypes \
#    	-Wredundant-decls -Wnested-externs -Wdisabled-optimization -ansi \
#        -funit-at-a-time
#-O3 -fexceptions \
#   	-Wall -W -Werror -Wshadow -Wmissing-prototypes -Wstrict-prototypes \
#    	-Wredundant-decls -Wnested-externs -Wdisabled-optimization -ansi
#-O3 -fexceptions -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE
#-O3
#-O3 -g -fexceptions
#-g -fexceptions \
#   	-Wall -W -Wshadow \
#    	-Wredundant-decls -Wdisabled-optimization -ansi

# consider:
# -fforce-addr -fmove-all-movables -freduce-all-givs -ftsp-ordering
# -frename-registers -ffast-math -funroll-loops
#elseif(ICC)
    # This is untested
    ##set_property( TARGET main APPEND_STRING PROPERTY COMPILE_FLAGS /W3 )
# Using Intel's icc and ifort compilers:
#   (does not work for mexFunctions unless you add a mexopts.sh file)
#-O3 -xN -vec_report=0
#-g
# 64bit:
#-O -m64
#-O3 -fexceptions -m64
elseif(MSVC)
    # This is untested
    ##set_property( TARGET main APPEND_STRING PROPERTY COMPILE_FLAGS /W3 )
endif (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)


# Add -DNTIMER if you do use any timing routines (otherwise -lrt is required).
add_definitions ("-DNTIMER")

option(NDEBUG "-DNDEBUG=ON")
option(NMALLOC "-DNMALLOC=ON")
option(NPRINT "-DNPRINT=ON")

set(ENV{G_MESSAGES_DEBUG} all)


# UMFPACK and CHOLMOD both require the BLAS.  
#CHOLMOD also requires LAPACK.
# Using the Goto BLAS:
# BLAS = -lgoto -lgfortran -lgfortranbegin
# BLAS = -lgoto2 -lgfortran -lgfortranbegin -lpthread
# BLAS = -lgoto -lfrtbegin -lg2c $(XERBLA) -lpthread
# BLAS = -lgoto64 -lfrtbegin -lg2c -lpthread $(XERBLA)

# SUSE Linux 10.1, AMD Opteron, with GOTO Blas
# BLAS = -lgoto_opteron64 -lgfortran
# BLAS = -lgoto -lgfortran

# Using non-optimized versions:
# BLAS = -lblas_plain -lgfortran -lgfortranbegin
# LAPACK = -llapack_plain
# BLAS = -lblas_plain -lgfortran -lgfortranbegin
# LAPACK = -llapack
# LAPACK = -llapack64

# The BLAS might not contain xerbla, an error-handling routine for LAPACK and
# the BLAS.  Also, the standard xerbla requires the Fortran I/O library, and
# stops the application program if an error occurs.  A C version of xerbla
# distributed with this software (SuiteSparse_config/xerbla/libcerbla.a)
# includes a Fortran-callable xerbla routine that prints nothing and does not
# stop the application program.  This is optional.
# XERBLA = ../../SuiteSparse_config/xerbla/libcerbla.a 


add_subdirectory(src)
add_subdirectory(test)
#add_subdirectory(doc)


#INSTALL_LIB = /usr/local/lib
#INSTALL_INCLUDE = /usr/local/include
