#include "cxsparse.h"
/* allocate a sparse matrix (triplet form or compressed-column form) */
cs *CXSPARSE(spalloc) (Int m, Int n, Int nzmax, Int values, Int triplet)
{
    cs *A = cs_calloc (1, sizeof (cs)) ;    /* allocate the cs struct */
    if (!A) return (NULL) ;                 /* out of memory */
    A->m = m ;                              /* define dimensions and nzmax */
    A->n = n ;
    A->nzmax = nzmax = CS_MAX (nzmax, 1) ;
    A->nz = triplet ? 0 : -1 ;              /* allocate triplet or comp.col */
    A->p = cs_malloc (triplet ? nzmax : n+1, sizeof (Int)) ;
    A->i = cs_malloc (nzmax, sizeof (Int)) ;
    A->x = values ? cs_malloc (nzmax, sizeof (Real)) : NULL ;
    return ((!A->p || !A->i || (values && !A->x)) ? CXSPARSE(spfree) (A) : A) ;
}

/* change the max # of entries sparse matrix */
Int cs_sprealloc (cs *A, Int nzmax)
{
    Int ok, oki, okj = 1, okx = 1 ;
    if (!A) return (0) ;
    if (nzmax <= 0) nzmax = (CS_CSC (A)) ? (A->p [A->n]) : A->nz ;
    A->i = cs_realloc (A->i, nzmax, sizeof (Int), &oki) ;
    if (CS_TRIPLET (A)) A->p = cs_realloc (A->p, nzmax, sizeof (Int), &okj) ;
    if (A->x) A->x = cs_realloc (A->x, nzmax, sizeof (Real), &okx) ;
    ok = (oki && okj && okx) ;
    if (ok) A->nzmax = nzmax ;
    return (ok) ;
}

/* free a sparse matrix */
cs *CXSPARSE(spfree) (cs *A)
{
    if (!A) return (NULL) ;     /* do nothing if A already NULL */
    cs_free (A->p) ;
    cs_free (A->i) ;
    cs_free (A->x) ;
    return ((cs *) cs_free (A)) ;   /* free the cs struct and return NULL */
}

/* free a numeric factorization */
cs_n *cs_nfree (cs_n *N)
{
    if (!N) return (NULL) ;     /* do nothing if N already NULL */
    CXSPARSE(spfree) (N->L) ;
    CXSPARSE(spfree) (N->U) ;
    cs_free (N->pinv) ;
    cs_free (N->B) ;
    return ((cs_n *) cs_free (N)) ;  /* free the cs_n struct and return NULL */
}

/* free a symbolic factorization */
cs_s *cs_sfree (cs_s *S)
{
    if (!S) return (NULL) ;     /* do nothing if S already NULL */
    cs_free (S->pinv) ;
    cs_free (S->q) ;
    cs_free (S->parent) ;
    cs_free (S->cp) ;
    cs_free (S->leftmost) ;
    return ((cs_s *) cs_free (S)) ;  /* free the cs_s struct and return NULL */
}

/* allocate a cs_dmperm or cs_scc result */
cs_d *CXSPARSE(dalloc) (Int m, Int n)
{
    cs_d *D ;
    D = cs_calloc (1, sizeof (cs_d)) ;
    if (!D) return (NULL) ;
    D->p = cs_malloc (m, sizeof (Int)) ;
    D->r = cs_malloc (m+6, sizeof (Int)) ;
    D->q = cs_malloc (n, sizeof (Int)) ;
    D->s = cs_malloc (n+6, sizeof (Int)) ;
    return ((!D->p || !D->r || !D->q || !D->s) ? CXSPARSE(dfree) (D) : D) ;
}

/* free a cs_dmperm or cs_scc result */
cs_d *CXSPARSE(dfree) (cs_d *D)
{
    if (!D) return (NULL) ;     /* do nothing if D already NULL */
    cs_free (D->p) ;
    cs_free (D->q) ;
    cs_free (D->r) ;
    cs_free (D->s) ;
    return ((cs_d *) cs_free (D)) ;  /* free the cs_d struct and return NULL */
}

/* free workspace and return a sparse matrix result */
cs *CXSPARSE(done) (cs *C, void *w, void *x, Int ok)
{
    cs_free (w) ;                       /* free workspace */
    cs_free (x) ;
    return (ok ? C : CXSPARSE(spfree) (C)) ;   /* return result if OK, else free it */
}

/* free workspace and return Int array result */
Int *CXSPARSE(idone) (Int *p, cs *C, void *w, Int ok)
{
    CXSPARSE(spfree) (C) ;                     /* free temporary matrix */
    cs_free (w) ;                       /* free workspace */
    return (ok ? p : (Int *) cs_free (p)) ; /* return result, or free it */
}

/* free workspace and return a numeric factorization (Cholesky, LU, or QR) */
cs_n *cs_ndone (cs_n *N, cs *C, void *w, void *x, Int ok)
{
    CXSPARSE(spfree) (C) ;                     /* free temporary matrix */
    cs_free (w) ;                       /* free workspace */
    cs_free (x) ;
    return (ok ? N : cs_nfree (N)) ;    /* return result if OK, else free it */
}

/* free workspace and return a cs_d result */
cs_d *cs_ddone (cs_d *D, cs *C, void *w, Int ok)
{
    CXSPARSE(spfree) (C) ;                     /* free temporary matrix */
    cs_free (w) ;                       /* free workspace */
    return (ok ? D : CXSPARSE(dfree) (D)) ;    /* return result if OK, else free it */
}
