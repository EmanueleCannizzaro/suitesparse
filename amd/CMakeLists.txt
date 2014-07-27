# -----------------------------------------------------------------
# CMake build system for SuiteSparse
#  http://code.google.com/p/suitesparse-metis-for-windows/
# Created by Jose Luis Blanco (University of Almeria) 2013-2014
# Updated by jesnault (jerome.esnault@inria.fr) 2014-01-21
# Updated by Emanuele Cannizzaro () 2014-05-21
# -----------------------------------------------------------------

PROJECT(amd)

## ==========================================================================
## === AMD version ==========================================================
## ==========================================================================

#/* AMD Version 1.2 and later include the following definitions.
# * As an example, to test if the version you are using is 1.2 or later:
# *
# * #ifdef AMD_VERSION
# *       if (AMD_VERSION >= AMD_VERSION_CODE (1,2)) ...
# * #endif
# *
# * This also works during compile-time:
# *
# *       #if defined(AMD_VERSION) && (AMD_VERSION >= AMD_VERSION_CODE (1,2))
# *           printf ("This is version 1.2 or later\n") ;
# *       #else
# *           printf ("This is an early version\n") ;
# *       #endif
# *
# * Versions 1.1 and earlier of AMD do not include a #define'd version number.
# */

option(AMD_HAS_VERSION_FUNCTION OFF)
option(AMD_DATE "Jun 20, 2012")

set(AMD_VERSION_MAJOR 2)
set(AMD_VERSION_MINOR 3)
set(AMD_VERSION_PATCH 1)

set(AMD_MAIN_VERSION 2)
set(AMD_SUB_VERSION 3)
set(AMD_SUBSUB_VERSION 1)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(doc)

