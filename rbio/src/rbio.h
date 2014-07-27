/* ========================================================================== */
/* === RBio/Include/RBio.h: include file for RBio =========================== */
/* ========================================================================== */

/* Copyright 2009, Timothy A. Davis, All Rights Reserved.
   Refer to RBio/Doc/license.txt for the RBio license. */

#ifndef _RBIO_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined (DLONG)
#define RB(name) rbio ## _l_ ## name
#else
#define RB(name) rbio ## _i_ ## name
#endif

#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define ISNAN(a) ((a) != (a))
#define PRIVATE static
#define PUBLIC

#define SLEN 4096
#define FREE_WORK   { SuiteSparse_free (w,config) ; \
                      SuiteSparse_free (cp,config) ; }

#define FREE_ALL    { FREE_WORK ; \
                      SuiteSparse_free (Ap,config) ; \
                      SuiteSparse_free (Ai,config) ; \
                      SuiteSparse_free (Ax,config) ; \
                      SuiteSparse_free (Az,config) ; \
                      SuiteSparse_free (Zp,config) ; \
                      SuiteSparse_free (Zi,config) ; }

#define FREE_RAW    { SuiteSparse_free (Ap,config) ; \
                      SuiteSparse_free (Ai,config) ; \
                      SuiteSparse_free (Ax,config) ; }


/* -------------------------------------------------------------------------- */
/* include files */
/* -------------------------------------------------------------------------- */

#include "SuiteSparse_config.h"

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* -------------------------------------------------------------------------- */
/* error codes */
/* -------------------------------------------------------------------------- */

#define RBIO_OK (0)               /* matrix is OK */

/* data structure errors */
#define RBIO_CP_INVALID (-1)      /* column pointers are invalid */
#define RBIO_ROW_INVALID (-2)     /* row indices are out of range */
#define RBIO_DUPLICATE (-3)       /* duplicate entry */
#define RBIO_EXTRANEOUS (-4)      /* entries in upper tri part of sym matrix */
#define RBIO_TYPE_INVALID (-5)    /* matrix type (RUA, etc) invalid */
#define RBIO_DIM_INVALID (-6)     /* matrix dimensions invalid */
#define RBIO_JUMBLED (-7)         /* matrix contains unsorted columns */
#define RBIO_ARG_ERROR (-8)       /* input arguments invalid */
#define RBIO_OUT_OF_MEMORY (-9)   /* out of memory */
#define RBIO_MKIND_INVALID (-10)  /* mkind is invalid */
#define RBIO_UNSUPPORTED (-11)    /* finite-element form unsupported */

/* I/O errors */
#define RBIO_HEADER_IOERROR (-91) /* I/O error: header */
#define RBIO_CP_IOERROR (-92)     /* I/O error: column pointers */
#define RBIO_ROW_IOERROR (-93)    /* I/O error: row indices */
#define RBIO_VALUE_IOERROR (-94)  /* I/O error: numerical values */
#define RBIO_FILE_IOERROR (-95)   /* I/O error: cannot read/write the file */

#define RBIO_DATE "Jun 20, 2012"
#define RBIO_VER_CODE(main,sub) ((main) * 1000 + (sub))
#define RBIO_MAIN_VERSION 2
#define RBIO_SUB_VERSION 1
#define RBIO_SUBSUB_VERSION 1
#define RBIO_VERSION RBIO_VER_CODE(RBIO_MAIN_VERSION,RBIO_SUB_VERSION)


/* -------------------------------------------------------------------------- */
/* user-callable functions */
/* -------------------------------------------------------------------------- */

/*
    RBread:         read a Rutherford/Boeing matrix from a file
    RBwrite:        write a matrix to a file in R/B format

    RBkind:         determine the matrix type (RUA, RSA, etc)
    RBreadraw:      read the raw contents of a R/B file

    RBget_entry:    get a single numerical value from a matrix
    RBput_entry:    put a single numerical value into a matrix

    RBmalloc:       malloc-wrapper for RBio
    RBfree:         free-wrapper for RBio
    RBok:           test the validity of a sparse matrix

    Each function comes in two versions: one with "int" integers, the other
    with "SuiteSparse_long" integers.  SuiteSparse_long is "long", except for
    Windows (for which it is __int64).  The default type is SuiteSparse_long.
    Functions for "int" integers have the _i suffix appended to their names.
*/

Int RB(kind)        /* 0: OK, < 0: error, > 0: warning */
(
    /* input */
    Int nrow,       /* A is nrow-by-ncol */
    Int ncol,
    Int *Ap,        /* Ap [0...ncol]: column pointers */
    Int *Ai,        /* Ai [0...nnz-1]: row indices */
    double *Ax,     /* Ax [0...nnz-1]: real values.  Az holds imaginary part */
    double *Az,     /* if real, Az is NULL. if complex, Az is non-NULL */
    Int mkind_in,   /* 0:R, 1:P: 2:Csplit, 3:I, 4:Cmerged */

    /* output */
    Int *mkind,     /* 0:R, 1:P: 2:Csplit, 3:I, 4:Cmerged */
    Int *skind,     /* r: -1 (rectangular), u: 0 (unsymmetric), s: 1 symmetric,
                       h: 2 (Hermitian), z: 3 (skew symmetric) */
    char mtype [4], /* rua, psa, rra, cha, etc */
    double *xmin,   /* smallest value */
    double *xmax,   /* largest value */

    /* workspace: allocated internally if NULL */
    Int *cp,        /* workspace of size ncol+1, undefined on input and output*/

    SuiteSparse_config *config    /* SuiteSparse configuration parameters */
) ;


Int RB(read)            /* 0: OK, < 0: error, > 0: warning */
(
    /* input */
    char *filename,     /* file to read from */
    Int build_upper,    /* if true, construct upper part for sym. matrices */
    Int zero_handling,  /* 0: do nothing, 1: prune zeros, 2: extract zeros */

    /* output */
    char title [73],
    char key [9],
    char mtype [4],     /* RUA, RSA, PUA, PSA, RRA, etc */
    Int *nrow,          /* A is nrow-by-ncol */
    Int *ncol,
    Int *mkind,         /* R: 0, P: 1, C: 2, I: 3 */
    Int *skind,         /* R: -1, U: 0, S: 1, H: 2, Z: 3 */
    Int *asize,         /* Ai array has size asize*sizeof(double) */
    Int *znz,           /* number of explicit zeros removed from A */

    /* output: these are malloc'ed below and must be freed by the caller */
    Int **Ap,           /* column pointers of A */
    Int **Ai,           /* row indices of A */
    double **Ax,        /* real values (ignored if NULL) of A */
    double **Az,        /* imaginary values (ignored if NULL) of A */
    Int **Zp,           /* column pointers of Z */
    Int **Zi,           /* row indices of Z */

    SuiteSparse_config *config    /* SuiteSparse configuration parameters */
) ;

Int RB(readraw)         /* 0: OK, < 0: error, > 0: warning */
(
    /* input */
    char *filename,     /* file to read from */

    /* output */
    char title [73],
    char key [9],
    char mtype [4],     /* RUA, RSA, PUA, PSA, RRA, etc */
    Int *nrow,          /* A is nrow-by-ncol */
    Int *ncol,
    Int *nnz,           /* size of Ai */
    Int *nelnz,
    Int *mkind,         /* 0:R, 1:P: 2:Csplit, 3:I, 4:Cmerged */
    Int *skind,         /* R: -1, U: 0, S: 1, H: 2, Z: 3 */
    Int *fem,           /* 0:__A, 1:__E */
    Int *xsize,         /* size of Ax */

    /* output: these are malloc'ed below and must be freed by the caller */
    Int **p_Ap,         /* size ncol+1, column pointers of A */
    Int **p_Ai,         /* size nnz, row indices of A */
    double **p_Ax,      /* size xsize, numerical values of A */

    SuiteSparse_config *config    /* SuiteSparse configuration parameters */
) ;

Int RB(write)       /* 0:OK, < 0: error, > 0: warning */
(
    /* input */
    char *filename, /* filename to write to (stdout if NULL) */
    char *title,    /* title (72 char max), may be NULL */
    char *key,      /* key (8 char max), may be NULL */
    Int nrow,       /* A is nrow-by-ncol */
    Int ncol,
    Int *Ap,        /* size ncol+1, column pointers */
    Int *Ai,        /* size anz=Ap[ncol], row indices (sorted) */
    double *Ax,     /* size anz or 2*anz, numerical values (binary if NULL) */
    double *Az,     /* size anz, imaginary part (real if NULL) */
    Int *Zp,        /* size ncol+1, column pointers for Z (or NULL) */
    Int *Zi,        /* size znz=Zp[ncol], row indices for Z (or NULL) */
    Int mkind_in,   /* 0:R, 1:P: 2:Csplit, 3:I, 4:Cmerged */

    /* output */
    char mtype [4], /* matrix type (RUA, RSA, etc), may be NULL */

    SuiteSparse_config *config    /* SuiteSparse configuration parameters */
) ;

void RB(get_entry)
(
    Int mkind,          /* R: 0, P: 1, C: 2, I: 3 */
    double *Ax,         /* real part, or both if merged-complex */
    double *Az,         /* imaginary part if split-complex */
    Int p,              /* index of the entry */
    double *xr,         /* real part */
    double *xz          /* imaginary part */
) ;

void RB(put_entry)
(
    Int mkind,          /* R: 0, P: 1, C: 2, I: 3 */
    double *Ax,         /* real part, or both if merged-complex */
    double *Az,         /* imaginary part if split-complex */
    Int p,              /* index of the entry */
    double xr,          /* real part */
    double xz           /* imaginary part */
) ;

Int RB(ok)          /* 0:OK, < 0: error, > 0: warning */
(
    /* inputs, not modified */
    Int nrow,       /* number of rows */
    Int ncol,       /* number of columns */
    Int nzmax,      /* max # of entries */
    Int *Ap,        /* size ncol+1, column pointers */
    Int *Ai,        /* size nz = Ap [ncol], row indices */
    double *Ax,     /* real part, or both if merged-complex */
    double *Az,     /* imaginary part for split-complex */
    char *As,       /* logical matrices (useful for MATLAB caller only) */
    Int mkind,      /* 0:real, 1:logical/pattern, 2:split-complex, 3:integer,
                       4:merged-complex */

    /* outputs, not defined on input */
    Int *p_njumbled,   /* # of jumbled row indices (-1 if not computed) */
    Int *p_nzeros      /* number of explicit zeros (-1 if not computed) */
) ;

#ifdef MATLAB_MEX_FILE
void RB(error) (int status) ;     /* only for MATLAB mexFunctions */
#endif

#ifdef __cplusplus
}
#endif
#endif
