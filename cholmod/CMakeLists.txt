# -----------------------------------------------------------------
# CMake build system for SuiteSparse
#  http://code.google.com/p/suitesparse-metis-for-windows/
# Created by Jose Luis Blanco (University of Almeria) 2013-2014
# Updated by jesnault (jerome.esnault@inria.fr) 2014-01-21
# Updated by Emanuele Cannizzaro () 2014-05-21
# -----------------------------------------------------------------

PROJECT(cholmod)


#------------------------------------------------------------------------------
# CHOLMOD configuration
#------------------------------------------------------------------------------

# CHOLMOD Library Modules, which appear in libcholmod.a:
# Core		requires: none
# Check		requires: Core
# Cholesky	requires: Core, AMD, COLAMD.  optional: Partition, Supernodal
# MatrixOps	requires: Core
# Modify	requires: Core
# Partition	requires: Core, CCOLAMD, METIS.  optional: Cholesky
# Supernodal	requires: Core, BLAS, LAPACK
#
# CHOLMOD test/demo Modules (all are GNU GPL, do not appear in libcholmod.a):
# Tcov		requires: Core, Check, Cholesky, MatrixOps, Modify, Supernodal
#		optional: Partition
# Valgrind	same as Tcov
# Demo		requires: Core, Check, Cholesky, MatrixOps, Supernodal
#		optional: Partition
#
# Configuration flags:
# -DNCHECK	    do not include the Check module.	   License GNU LGPL
# -DNCHOLESKY	    do not include the Cholesky module.	   License GNU LGPL
# -DNPARTITION	    do not include the Partition module.   License GNU LGPL
#		    also do not include METIS.
# -DNCAMD           do not use CAMD, etc from Partition module.    GNU LGPL
# -DNGPL	    do not include any GNU GPL Modules in the CHOLMOD library:
# -DNMATRIXOPS	    do not include the MatrixOps module.   License GNU GPL
# -DNMODIFY	    do not include the Modify module.      License GNU GPL
# -DNSUPERNODAL     do not include the Supernodal module.  License GNU GPL
#
# -DNPRINT	    do not print anything.
# -D'LONGBLAS=long' or -DLONGBLAS='long long' defines the integers used by
#  		    	LAPACK and the BLAS (defaults to 'int')
# -DNSUNPERF	    for Solaris only.  If defined, do not use the Sun
#			Performance Library

##CHOLMOD_CONFIG = $(GPU_CONFIG)

# uncomment this line to compile CHOLMOD without METIS:
# cholmod_CONFIG = -DNPARTITION

#------------------------------------------------------------------------------
# METIS, optionally used by CHOLMOD
#------------------------------------------------------------------------------

# If you do not have METIS, or do not wish to use it in CHOLMOD, you must
# compile CHOLMOD with the -DNPARTITION flag.

# The path is relative to where it is used, in CHOLMOD/Lib, CHOLMOD/MATLAB, etc.
# You may wish to use an absolute path.  METIS is optional.  Compile
# CHOLMOD with -DNPARTITION if you do not wish to use METIS.
##METIS_PATH = ../../metis-4.0
##METIS = ../../metis-4.0/libmetis.a

#------------------------------------------------------------------------------
# GPU configuration for CHOLMOD, using the CUDA BLAS
#------------------------------------------------------------------------------

# no cuda
##GPU_BLAS_PATH =
##GPU_CONFIG =

# with cuda BLAS acceleration for CHOLMOD
# GPU_BLAS_PATH=/usr/local/cuda
# GPU_CONFIG=-DGPU_BLAS -I$(GPU_BLAS_PATH)/include

#(__sun) || defined (MSOL2) || defined (ARCH_SOL2)
#(__MINGW32__) || defined (__MINGW32__)
#(CHOLMOD_SOL2) && !defined(NSUNPERF) && defined(BLAS64)
#SUN64
#(LONGBLAS) || defined (BLAS64)
##GPU_BLAS
#NCAMD
#NCHECK
#NCHOLESKY
#NGPL
#NMATRIXOPS
#NMODIFY
#NPARTITION
#NSUPERNODAL
#CHOLMOD_WINDOWS
#NDEBUG
#NPRINT
#DLONG
#DINT
#NLARGEFILE
#PATTERN
#NCONJUGATE


option(CHOLMOD_HAS_VERSION_FUNCTION OFF)
option(CHOLMOD_DATE "Jun 20, 2012")

set(CHOLMOD_VERSION_MAJOR 2)
set(CHOLMOD_VERSION_MINOR 1)
set(CHOLMOD_VERSION_PATCH 2)

set(CHOLMOD_MAIN_VERSION 2)
set(CHOLMOD_SUB_VERSION 1)
set(CHOLMOD_SUBSUB_VERSION 2)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(doc)
