#include "cxsparse.h"
static Int CXSPARSE(tol) (Int i, Int j, Real aij, void *tol)
{
    return (CS_ABS (aij) > *((double *) tol)) ;
}
Int cs_droptol (cs *A, double tol)
{
    return (cs_fkeep (A, &CXSPARSE(tol), &tol)) ;    /* keep all large entries */
}
