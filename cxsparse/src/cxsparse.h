#ifndef _CXSPARSE_H
#define _CXSPARSE_H

#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define CS_VER 3                    /* CXSparse Version */
#define CS_SUBVER 1
#define CS_SUBSUB 2
#define CS_DATE "April 16, 2013"       /* CXSparse release date */
#define CS_COPYRIGHT "Copyright (c) Timothy A. Davis, 2006-2013"


#include "SuiteSparse_config.h"

#if defined (DCOMPLEX)
#if defined (DLONG)
#define CXSPARSE(name) cxsparse ## _cl_ ## name
#else
#define CXSPARSE(name) cxsparse ## _ci_ ## name
#endif
#else
#if defined (DLONG)
#define CXSPARSE(name) cxsparse ## _dl_ ## name
#else
#define CXSPARSE(name) cxsparse ## _di_ ## name
#endif
#endif

/* -------------------------------------------------------------------------- */
/* double/int version of CXSparse */
/* -------------------------------------------------------------------------- */

/* --- primary CSparse data structures ------------------------- */

typedef struct cs_sparse  /* matrix in compressed-column or triplet form */
{
    Int nzmax ;     /* maximum number of entries */
    Int m ;         /* number of rows */
    Int n ;         /* number of columns */
    Int *p ;        /* column pointers (size n+1) or col indices (size nzmax) */
    Int *i ;        /* row indices, size nzmax */
    Real *x ;     /* numerical values, size nzmax */
    Int nz ;        /* # of entries in triplet matrix, -1 for compressed-col */
} cs ;


/* --- secondary CSparse data structures ----------------------- */

typedef struct cs_symbolic  /* symbolic Cholesky, LU, or QR analysis */
{
    Int *pinv ;     /* inverse row perm. for QR, fill red. perm for Chol */
    Int *q ;        /* fill-reducing column permutation for LU and QR */
    Int *parent ;   /* elimination tree for Cholesky and QR */
    Int *cp ;       /* column pointers for Cholesky, row counts for QR */
    Int *leftmost ; /* leftmost[i] = min(find(A(i,:))), for QR */
    Int m2 ;        /* # of rows for QR, after adding fictitious rows */
    double lnz ;    /* # entries in L for LU or Cholesky; in V for QR */
    double unz ;    /* # entries in U for LU; in R for QR */
} cs_s ;

typedef struct cs_numeric   /* numeric Cholesky, LU, or QR factorization */
{
    cs *L ;      /* L for LU and Cholesky, V for QR */
    cs *U ;      /* U for LU, r for QR, not used for Cholesky */
    Int *pinv ;     /* partial pivoting for LU */
    double *B ;     /* beta [0..n-1] for QR */
} cs_n ;

typedef struct cs_dmperm_results    /* cs_di_dmperm or cs_di_scc output */
{
    Int *p ;        /* size m, row permutation */
    Int *q ;        /* size n, column permutation */
    Int *r ;        /* size nb+1, block k is rows r[k] to r[k+1]-1 in A(p,q) */
    Int *s ;        /* size nb+1, block k is cols s[k] to s[k+1]-1 in A(p,q) */
    Int nb ;        /* # of blocks in fine dmperm decomposition */
    Int rr [5] ;    /* coarse row decomposition */
    Int cc [5] ;    /* coarse column decomposition */
} cs_d ;


/* --- primary CSparse routines ------------------------- */

cs *CXSPARSE(add) (const cs *A, const cs *B, Real alpha, Real beta) ;
gint CXSPARSE(cholsol) (Int order, const cs *A, Real *b) ;
gint CXSPARSE(dupl) (cs *A) ;
gint CXSPARSE(entry) (cs *T, Int i, Int j, Real x) ;
gint CXSPARSE(lusol) (Int order, const cs *A, Real *b, gdouble tol) ;
gint CXSPARSE(gaxpy) (const cs *A, const Real *x, Real *y) ;
cs *CXSPARSE(multiply) (const cs *A, const cs *B) ;
gint CXSPARSE(qrsol) (gint order, const cs *A, Real *b) ;
cs *CXSPARSE(transpose) (const cs *A, Int values) ;
cs *CXSPARSE(compress) (const cs *T) ;
gdouble CXSPARSE(norm) (const cs *A) ;
gint CXSPARSE(print) (const cs *A, Int brief) ;
cs *CXSPARSE(load) (FILE *f) ;

/* utilities */
gpointer CXSPARSE(calloc) (Int n, size_t size) ;
gpointer CXSPARSE(free) (gpointer p) ;
gpointer CXSPARSE(realloc) (gpointer p, Int n, size_t size, Int *ok) ;
cs *CXSPARSE(spalloc) (Int m, Int n, Int nzmax, Int values, Int t) ;
cs *CXSPARSE(spfree) (cs *A) ;
Int CXSPARSE(sprealloc) (cs *A, Int nzmax) ;
gpointer CXSPARSE(malloc) (Int n, size_t size) ;

/* --- secondary CSparse routines ----------------------- */

Int *CXSPARSE(amd) (Int order, const cs *A) ;
cs_n *CXSPARSE(chol) (const cs *A, const cs_s *S) ;
cs_d *CXSPARSE(dmperm) (const cs *A, Int seed) ;
Int CXSPARSE(droptol) (cs *A, gdouble tol) ;
Int CXSPARSE(dropzeros) (cs *A) ;
Int CXSPARSE(happly) (const cs *V, Int i, gdouble beta, Real *x) ;
Int CXSPARSE(ipvec) (const Int *p, const Real *b, Real *x, Int n) ;
Int CXSPARSE(lsolve) (const cs *L, Real *x) ;
Int CXSPARSE(ltsolve) (const cs *L, Real *x) ;
cs_n *CXSPARSE(lu) (const cs *A, const cs_s *S, gdouble tol) ;
cs *CXSPARSE(permute) (const cs *A, const Int *pinv, const Int *q, Int values) ;
Int *CXSPARSE(pinv) (const Int *p, Int n) ;
Int CXSPARSE(pvec) (const Int *p, const Real *b, Real *x, Int n) ;
cs_n *CXSPARSE(qr) (const cs *A, const cs_s *S) ;
cs_s *CXSPARSE(schol) (Int order, const cs *A) ;
cs_s *CXSPARSE(sqr) (Int order, const cs *A, Int qr) ;
cs *CXSPARSE(symperm) (const cs *A, const Int *pinv, Int values) ;
Int CXSPARSE(usolve) (const cs *U, Real *x) ;
Int CXSPARSE(utsolve) (const cs *U, Real *x) ;
Int CXSPARSE(updown) (cs *L, Int sigma, const cs *C, const Int *parent) ;

/* utilities */
cs_s *CXSPARSE(sfree) (cs_s *S) ;
cs_n *CXSPARSE(nfree) (cs_n *N) ;
cs_d *CXSPARSE(dfree) (cs_d *D) ;

/* --- tertiary CSparse routines -------------------------------------------- */

Int *CXSPARSE(counts) (const cs *A, const Int *parent, const Int *post, Int ata) ;
gdouble CXSPARSE(cumsum) (Int *p, Int *c, Int n) ;
Int CXSPARSE(dfs) (Int j, cs *G, Int top, Int *xi, Int *pstack, const Int *pinv) ;
Int *CXSPARSE(etree) (const cs *A, Int ata) ;
Int CXSPARSE(fkeep) (cs *A, Int (*fkeep) (Int, Int, Real, gpointer), gpointer other) ;
Real CXSPARSE(house) (Real *x, gdouble *beta, Int n) ;
Int *CXSPARSE(maxtrans) (const cs *A, Int seed) ;
Int *CXSPARSE(post) (const Int *parent, Int n) ;
cs_d *CXSPARSE(scc) (cs *A) ;
Int CXSPARSE(scatter) (const cs *A, Int j, Real beta, Int *w, Real *x, Int mark, cs *C, Int nz) ;
Int CXSPARSE(tdfs) (Int j, Int k, Int *head, const Int *next, Int *post, Int *stack) ;
Int CXSPARSE(leaf) (Int i, Int j, const Int *first, Int *maxfirst, Int *prevleaf, Int *ancestor, Int *jleaf) ;
Int CXSPARSE(reach) (cs *G, const cs *B, Int k, Int *xi, const Int *pinv) ;
Int CXSPARSE(spsolve) (cs *L, const cs *B, Int k, Int *xi, Real *x, const Int *pinv, Int lo) ;
Int CXSPARSE(ereach) (const cs *A, Int k, const Int *parent, Int *s, Int *w) ;
Int *CXSPARSE(randperm) (Int n, Int seed) ;

/* utilities */
cs_d *CXSPARSE(dalloc) (Int m, Int n) ;
cs *CXSPARSE(done) (cs *C, gpointer w, gpointer x, Int ok) ;
Int *CXSPARSE(idone) (Int *p, cs *C, gpointer w, Int ok) ;
cs_n *CXSPARSE(ndone) (cs_n *N, cs *C, gpointer w, gpointer x, Int ok) ;
cs_d *CXSPARSE(ddone) (cs_d *D, cs *C, gpointer w, Int ok) ;

/* -------------------------------------------------------------------------- */
/* Macros for constructing each version of CSparse */
/* -------------------------------------------------------------------------- */

#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define FLIP(i) (-(i)-2)
#define UNFLIP(i) (((i) < 0) ? CS_FLIP(i) : (i))
#define MARKED(w,j) (w [j] < 0)
#define MARK(w,j) { w [j] = CS_FLIP (w [j]) ; }
#define CSC(A) (A && (A->nz == -1))
#define TRIPLET(A) (A && (A->nz >= 0))

/* -------------------------------------------------------------------------- */
/* Conversion routines */
/* -------------------------------------------------------------------------- */

#ifndef NCOMPLEX
//cs_di *cs_i_real (cs *A, Int real) ;
//cs_ci *cs_i_complex (cs_di *A, int real) ;
//cs_dl *cs_l_real (cs_cl *A, cs_long_t real) ;
//cs_cl *cs_l_complex (cs_dl *A, cs_long_t real) ;
#endif

#ifdef __cplusplus
}
#endif
#endif
