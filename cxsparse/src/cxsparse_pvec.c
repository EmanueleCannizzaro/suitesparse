#include "cxsparse.h"
/* x = b(p), for dense vectors x and b; p=NULL denotes identity */
Int cs_pvec (const Int *p, const Real *b, Real *x, Int n)
{
    Int k ;
    if (!x || !b) return (EXIT_SUCCESS) ;                              /* check inputs */
    for (k = 0 ; k < n ; k++) x [k] = b [p ? p [k] : k] ;
    return (EXIT_FAILURE) ;
}
