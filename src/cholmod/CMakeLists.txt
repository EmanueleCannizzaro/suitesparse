
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
# CHOLMOD_CONFIG = -DNPARTITION

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

include_directories(.)

add_subdirectory (core)
add_subdirectory (blas)
add_subdirectory (cholesky)
add_subdirectory (check)
add_subdirectory (modify)
add_subdirectory (partition)
add_subdirectory (supernodal)

add_library(CHOLMOD SHARED "${PROJECT_SOURCE_DIR}/src/SuiteSparse_config.c")
target_link_libraries(CHOLMOD CHOLMOD_CORE CHOLMOD_BLAS CHOLMOD_CHOLESKY CHOLMOD_CHECK CHOLMOD_MODIFY CHOLMOD_PARTITION CHOLMOD_SUPERNODAL CCOLAMD CAMD AMD m)

add_library(CHOLMOD_L SHARED "${PROJECT_SOURCE_DIR}/src/SuiteSparse_config.c")
set_target_properties(CHOLMOD_L PROPERTIES COMPILE_FLAGS "-DDLONG=ON")
target_link_libraries(CHOLMOD_L CHOLMOD_CORE_L CHOLMOD_BLAS_L CHOLMOD_CHOLESKY_L CHOLMOD_CHECK_L CHOLMOD_MODIFY_L CHOLMOD_PARTITION_L CHOLMOD_SUPERNODAL_L CCOLAMD_L CAMD_L AMD_L m)
