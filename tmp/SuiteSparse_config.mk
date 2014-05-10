
# ranlib, and ar, for generating libraries.  If you don't need ranlib,
# just change it to RANLAB = echo
RANLIB = ranlib
ARCHIVE = $(AR) $(ARFLAGS)

# copy and delete a file
CP = cp -f
MV = mv -f

# Fortran compiler (not required for 'make' or 'make library')
F77 = gfortran
F77FLAGS = $(FFLAGS) -O
F77LIB =

# C and Fortran libraries.  Remove -lrt if you don't have it.
  LIB = -lm -lrt
# Using the following requires CF = ... -DNTIMER on POSIX C systems.
# LIB = -lm

# For "make install"
INSTALL_LIB = /usr/local/lib
INSTALL_INCLUDE = /usr/local/include

# Which version of MAKE you are using (default is "make")
# MAKE = make
# MAKE = gmake

#------------------------------------------------------------------------------
# SuiteSparseQR configuration:
#------------------------------------------------------------------------------

# The SuiteSparseQR library can be compiled with the following options:
#
# -DNPARTITION      do not include the CHOLMOD partition module
# -DNEXPERT         do not include the functions in SuiteSparseQR_expert.cpp
# -DHAVE_TBB        enable the use of Intel's Threading Building Blocks (TBB)

# default, without timing, without TBB:
SPQR_CONFIG =
# with TBB:
# SPQR_CONFIG = -DHAVE_TBB

# This is needed for IBM AIX: (but not for and C codes, just C++)
# SPQR_CONFIG = -DBLAS_NO_UNDERSCORE

# with TBB, you must select this:
# TBB = -ltbb
# without TBB:
TBB =

#------------------------------------------------------------------------------
# remove object files and profile output
#------------------------------------------------------------------------------

CLEAN = *.o *.obj *.ln *.bb *.bbg *.da *.tcov *.gcov gmon.out *.bak *.d *.gcda *.gcno
