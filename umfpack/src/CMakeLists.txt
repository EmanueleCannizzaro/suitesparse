
PROJECT(umfpack)

#------------------------------------------------------------------------------
# UMFPACK configuration:
#------------------------------------------------------------------------------

# Configuration flags for UMFPACK.  See UMFPACK/Source/umf_config.h for details.
#
# -DNBLAS	do not use the BLAS.  UMFPACK will be very slow.
# -D'LONGBLAS=long' or -DLONGBLAS='long long' defines the integers used by
#  		LAPACK and the BLAS (defaults to 'int')
# -DNSUNPERF	do not use the Sun Perf. Library (default is use it on Solaris)
# -DNRECIPROCAL	do not multiply by the reciprocal
# -DNO_DIVIDE_BY_ZERO	do not divide by zero
# -DNCHOLMOD    do not use CHOLMOD as a ordering method.  If -DNCHOLMOD is
#               included in UMFPACK_CONFIG, then UMFPACK  does not rely on
#               CHOLMOD, CAMD, CCOLAMD, COLAMD, and METIS.

##UMFPACK_CONFIG =

# uncomment this line to compile UMFPACK without CHOLMOD:
# UMFPACK_CONFIG = -DNCHOLMOD

set(SUITESPARSE_UMFPACK_VERSION_MAJOR 5)
set(SUITESPARSE_UMFPACK_VERSION_MINOR 6)
set(SUITESPARSE_UMFPACK_VERSION_PATCH 2)

include_directories(./)
include_directories("../amd")
include_directories("../cholmod")


FILE(GLOB HEADER_FILES "*.h")
FILE(GLOB SRC_LIST "*.c")

add_library(umfpack_di SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(umfpack_di PROPERTIES COMPILE_FLAGS "-DDINT=ON")
target_link_libraries(umfpack_di m)

add_library(umfpack_dl SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(umfpack_dl PROPERTIES COMPILE_FLAGS "-DDLONG=ON")
target_link_libraries(umfpack_dl m)

add_library(umfpack_zi SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(umfpack_zi PROPERTIES COMPILE_FLAGS "-DZINT=ON")
target_link_libraries(umfpack_zi m)

add_library(umfpack_zl SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(umfpack_zl PROPERTIES COMPILE_FLAGS "-DZLONG=ON")
target_link_libraries(umfpack_zl m)
