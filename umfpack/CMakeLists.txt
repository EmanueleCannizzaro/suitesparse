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

set(UMFPACK_VERSION_MAJOR 5)
set(UMFPACK_VERSION_MINOR 6)
set(UMFPACK_VERSION_PATCH 2)

set(UMFPACK_MAIN_VERSION 2)
set(UMFPACK_SUB_VERSION 3)
set(UMFPACK_SUBSUB_VERSION 1)
set(UMFPACK_VERSION ${UMFPACK_MAIN_VERSION} * 1000 + ${UMFPACK_SUB_VERSION})

add_subdirectory(src)
include_directories("${amd_SOURCE_DIR}/src")
include_directories("${cholmod_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/src")
FILE(GLOB SRC_LIST "*.c")
#add_library(umfpack SHARED ${SRC_LIST} $<TARGET_OBJECTS:umfpack_di> $<TARGET_OBJECTS:umfpack_dl>  $<TARGET_OBJECTS:umfpack_ci> $<TARGET_OBJECTS:umfpack_cl>)
add_library(umfpack SHARED ${SRC_LIST} $<TARGET_OBJECTS:umfpack_di> $<TARGET_OBJECTS:umfpack_dl>)
target_link_libraries(umfpack cholmod colamd amd lapack blas m)
#add_subdirectory(test)
add_subdirectory(doc)
