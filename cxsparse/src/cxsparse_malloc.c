#include "cxsparse.h"
#ifdef MATLAB_MEX_FILE
#define malloc mxMalloc
#define free mxFree
#define realloc mxRealloc
#define calloc mxCalloc
#endif

/* wrapper for malloc */
void *CXSPARSE(malloc) (Int n, size_t size)
{
    return (malloc (CS_MAX (n,1) * size)) ;
}

/* wrapper for calloc */
void *CXSPARSE(calloc) (Int n, size_t size)
{
    return (calloc (CS_MAX (n,1), size)) ;
}

/* wrapper for free */
void *CXSPARSE(free) (void *p)
{
    if (p) free (p) ;       /* free p if it is not already NULL */
    return (NULL) ;         /* return NULL to simplify the use of CXSPARSE(free) */
}

/* wrapper for realloc */
void *CXSPARSE(realloc) (void *p, Int n, size_t size, Int *ok)
{
    void *pnew ;
    pnew = realloc (p, CS_MAX (n,1) * size) ; /* realloc the block */
    *ok = (pnew != NULL) ;                  /* realloc fails if pnew is NULL */
    return ((*ok) ? pnew : p) ;             /* return original p if failure */
}
