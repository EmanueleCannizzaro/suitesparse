
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

set(SUITESPARSE_CHOLMOD_VERSION_MAJOR 2)
set(SUITESPARSE_CHOLMOD_VERSION_MINOR 1)
set(SUITESPARSE_CHOLMOD_VERSION_PATCH 2)

include_directories(.)

FILE(GLOB HEADER_FILES "*.h")

add_subdirectory (core)
add_subdirectory (blas)
add_subdirectory (cholesky)
add_subdirectory (check)
add_subdirectory (modify)
add_subdirectory (partition)
add_subdirectory (supernodal)

add_library(cholmod_di SHARED "../SuiteSparse_config.c")
set_target_properties(cholmod_di PROPERTIES COMPILE_FLAGS "-DDINT=ON -DDLONG=OFF")
target_link_libraries(cholmod_di cholmod_core_di cholmod_blas_di cholmod_cholesky_di cholmod_check_di cholmod_modify_di cholmod_partition_di cholmod_supernodal_di ccolamd_di camd_di amd_di m)

add_library(cholmod_dl SHARED "../SuiteSparse_config.c")
set_target_properties(cholmod_dl PROPERTIES COMPILE_FLAGS "-DDLONG=ON -DDINT=OFF")
target_link_libraries(cholmod_dl cholmod_core_dl cholmod_blas_dl cholmod_cholesky_dl cholmod_check_dl cholmod_modify_dl cholmod_partition_dl cholmod_supernodal_dl ccolamd_dl camd_dl amd_dl m)
