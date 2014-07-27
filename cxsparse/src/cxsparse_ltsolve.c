#include "cxsparse.h"
/* solve L'x=b where x and b are dense.  x=b on input, solution on output. */
Int cs_ltsolve (const cs *L, Real *x)
{
    Int p, j, n, *Lp, *Li ;
    Real *Lx ;
    if (!CS_CSC (L) || !x) return (0) ;                     /* check inputs */
    n = L->n ; Lp = L->p ; Li = L->i ; Lx = L->x ;
    for (j = n-1 ; j >= 0 ; j--)
    {
        for (p = Lp [j]+1 ; p < Lp [j+1] ; p++)
        {
            x [j] -= CS_CONJ (Lx [p]) * x [Li [p]] ;
        }
        x [j] /= CS_CONJ (Lx [Lp [j]]) ;
    }
    return (1) ;
}
