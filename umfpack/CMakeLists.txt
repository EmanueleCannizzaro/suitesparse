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

set(UMFPACK_MAIN_VERSION 5)
set(UMFPACK_SUB_VERSION 6)
set(UMFPACK_SUBSUB_VERSION 2)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(doc)
