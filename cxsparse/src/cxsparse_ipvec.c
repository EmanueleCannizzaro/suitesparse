#include "cxsparse.h"
/* x(p) = b, for dense vectors x and b; p=NULL denotes identity */
Int cs_ipvec (const Int *p, const Real *b, Real *x, Int n)
{
    Int k ;
    if (!x || !b) return (0) ;                              /* check inputs */
    for (k = 0 ; k < n ; k++) x [p ? p [k] : k] = b [k] ;
    return (1) ;
}
