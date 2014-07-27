/* ========================================================================== */
/* === RBio/Demo/RBdemo.c: C demo =========================================== */
/* ========================================================================== */

/* Copyright 2009, Timothy A. Davis, All Rights Reserved.
   Refer to RBio/Doc/license.txt for the RBio license. */

/* This program reads a Rutherford/Boeing file from stdin and uses it
   to test the RBio C-callable functions. */

#include "rbio.h"

#define SLEN 4096

int main (int argc, char **argv)
{
    double xr, xz, xmin, xmax;
    double *Ax, *Az;
    Int nrow, ncol, mkind, skind, *Ap, *Ai, i, *Zp, *Zi, asize, mkind2, skind2,
        znz, j, p, status, njumbled, nzeros, build_upper, zero_handling, fem,
        xsize, nelnz, nnz;
    char title [73], key [9], mtype [4], mtype2 [4], *filename;

    SuiteSparse_config config;
    config.malloc_memory = malloc;
    config.free_memory = free;

    /* read from stdin, or from file given by first argument */
    filename = (argc > 1) ? argv [1] : NULL;

    title [0] = '\0';
    build_upper = 1;
    zero_handling = 2;     /* extract zeros */
    status = RB(read) (filename, build_upper, zero_handling, title, key, mtype,
        &nrow, &ncol, &mkind, &skind, &asize, &znz,
        &Ap, &Ai, &Ax, &Az, &Zp, &Zi, &config);

    printf ("\n===========================================================\n");
    printf ("title: [%s]\n", title);
    printf ("status " ID "\n", status);
    if (status != RBIO_OK) {
        printf ("RBread Error! "ID"\n", status);
        SuiteSparse_free (Ap, &config);
        SuiteSparse_free (Ai, &config);
        SuiteSparse_free (Ax, &config);
        SuiteSparse_free (Az, &config);
        SuiteSparse_free (Zp, &config);
        SuiteSparse_free (Zi, &config);

        if (filename != NULL) {
            status = RB(readraw) (filename, title, key, mtype, &nrow, &ncol, &nnz,
                &nelnz, &mkind, &skind, &fem, &xsize, &Ap, &Ai, &Ax, NULL);
            if (status != RBIO_OK) {
                printf ("RBreadraw error! status "ID"\n", status);
                return(EXIT_FAILURE);
            }
            printf ("raw nrow "ID" ncol "ID" nnz "ID" nelnz "ID" xsize "ID"\n",
                nrow, ncol, nnz, nelnz, xsize);
            SuiteSparse_free (Ap, &config);
            SuiteSparse_free (Ai, &config);
            SuiteSparse_free (Ax, &config);
            return (0);
        }
        return(EXIT_FAILURE);
    }

    printf ("key [%s] nrow "ID" ncol "ID "\n", key, nrow, ncol);
    printf ("mkind "ID" skind "ID" asize "ID" znz "ID"\n", mkind, skind, asize, znz);
    printf ("mtype from file:               [%s]\n", mtype);

    if (Ap [ncol] < 20) {
        for (j = 0; j < ncol; j++) {
            printf ("\ncolumn "ID":\n", j);
            for (p = Ap [j]; p < Ap [j+1]; p++) {
                i = Ai [p];
                RB(get_entry) (mkind, Ax, Az, p, &xr, &xz);
                printf ("  "ID" : %g", i, xr);
                if (xz != 0) printf (" + (%g)i\n", xz);
                printf ("\n");
            }
        }
    }

    status = RB(ok) (nrow, ncol, asize, Ap, Ai, Ax, Az, NULL, mkind, &njumbled, &nzeros);
    printf ("(A) RBok status "ID" "ID" "ID"\n", status, njumbled, nzeros);
    if (status != RBIO_OK || njumbled != 0 || nzeros != 0) {
        printf ("RBok Error!\n");
        return(EXIT_FAILURE);
    }

    status = RB(ok) (nrow, ncol, asize, Zp, Zi, NULL, NULL, NULL, 1, &njumbled, &nzeros);
    printf ("(Z) RBok status "ID" "ID" "ID"\n", status, njumbled, nzeros);
    if (status != RBIO_OK || njumbled != 0 || nzeros != 0) {
        printf ("RBok Error (Z)!\n");
        return(EXIT_FAILURE);
    }

    status = RB(write) ("temp.rb", title, key, nrow, ncol, Ap, Ai, Ax, Az, Zp, Zi, mkind, mtype2, NULL);
    if (status != RBIO_OK) {
        printf ("RBwrite error!\n");
    }

    status = RB(kind) (nrow, ncol, Ap, Ai, Ax, Az, mkind, &mkind2, &skind2, mtype2, &xmin, &xmax, NULL, NULL);
    if (status != RBIO_OK) {
        printf ("RBkind error!\n");
        return(EXIT_FAILURE);
    }

    printf ("mtype from examining matrix:   [%s]\n", mtype2);

    SuiteSparse_free (Ap, &config);
    SuiteSparse_free (Ai, &config);
    SuiteSparse_free (Ax, &config);
    SuiteSparse_free (Az, &config);
    SuiteSparse_free (Zp, &config);
    SuiteSparse_free (Zi, &config);

    zero_handling = 1;     /* prune zeros */
    status = RB(read) ("temp.rb", build_upper, zero_handling, title, key, mtype,
        &nrow, &ncol, &mkind, &skind, &asize, &znz, &Ap, &Ai, &Ax, NULL, NULL, NULL, &config);
    if (status != 0) {
        SuiteSparse_free (Ap, &config);
        SuiteSparse_free (Ai, &config);
        SuiteSparse_free (Ax, &config);
        printf ("RBread Error! "ID"\n", status);
        return(EXIT_FAILURE);
    }

    status = RB(kind) (nrow, ncol, Ap, Ai, Ax, NULL, mkind, &mkind2, &skind2, mtype2, &xmin, &xmax, NULL, NULL);
    if (status != RBIO_OK) {
        printf ("RBkind error!\n");
    }
    printf ("mtype after reading from file: [%s]\n", mtype2);

    SuiteSparse_free (Ap, NULL);
    SuiteSparse_free (Ai, NULL);
    SuiteSparse_free (Ax, NULL);

    status = RB(readraw) ("temp.rb", title, key, mtype, &nrow, &ncol, &nnz,
        &nelnz, &mkind, &skind, &fem, &xsize, &Ap, &Ai, &Ax, NULL);
    if (status != RBIO_OK) {
        printf ("RBreadraw error!\n");
        return(EXIT_FAILURE);
    }
    printf ("raw nrow "ID" ncol "ID" nnz "ID" nelnz "ID" xsize "ID"\n",
        nrow, ncol, nnz, nelnz, xsize);

    if (fem) {
        printf ("FEM matrix\n");
    } else {
        status = RB(kind) (nrow, ncol, Ap, Ai, Ax, NULL, mkind, &mkind2, &skind2,
            mtype2, &xmin, &xmax, NULL, NULL);
        if (status != RBIO_OK) {
            printf ("RBkind error!\n");
        }
        printf ("mtype from raw read from file: [%s]\n", mtype2);
    }

    SuiteSparse_free (Ap, NULL);
    SuiteSparse_free (Ai, NULL);
    SuiteSparse_free (Ax, NULL);

    /* read in just the pattern */
    status = RB(read) ("temp.rb", build_upper, zero_handling, title, key, mtype,
        &nrow, &ncol, &mkind, &skind, &asize, &znz, &Ap, &Ai, NULL, NULL, NULL, NULL, &config);

    status = RB(ok) (nrow, ncol, asize, Ap, Ai, Ax, Az, NULL, mkind, &njumbled, &nzeros);
    printf ("(P) RBok status "ID" "ID" "ID"\n", status, njumbled, nzeros);
    if (status != RBIO_OK || njumbled != 0 || nzeros != 0) {
        printf ("RBok Error!\n");
        return(EXIT_FAILURE);
    }

    status = RB(kind) (nrow, ncol, Ap, Ai, NULL, NULL, mkind, &mkind2, &skind2, mtype2, &xmin, &xmax, NULL, NULL);
    if (status != RBIO_OK) {
        printf ("RBkind error!\n");
        return(EXIT_FAILURE);
    }
    printf ("mtype of pattern:              [%s]\n", mtype2);


    SuiteSparse_free (Ap, NULL);
    SuiteSparse_free (Ai, NULL);

    /* read in just the lower triangular part for symmetric case */
    build_upper = 0;
    zero_handling = 0;     /* ignore zeros */
    status = RB(read) ("temp.rb", build_upper, zero_handling, title, key, mtype,
        &nrow, &ncol, &mkind, &skind, &asize, &znz, &Ap, &Ai, &Ax, NULL, NULL, NULL, &config);
    if (status != RBIO_OK) {
        printf ("RBread error! "ID"\n", status);
        return(EXIT_FAILURE);
    }

    status = RB(kind) (nrow, ncol, Ap, Ai, Ax, NULL, mkind, &mkind2, &skind2, mtype2, &xmin, &xmax, NULL, NULL);
    if (status != RBIO_OK)
    {
        printf ("RBkind error!\n");
        return(EXIT_FAILURE);
    }
    printf ("mtype of tril(A):              [%s]\n", mtype2);

    status = RB(ok) (nrow, ncol, asize, Ap, Ai, Ax, NULL, NULL, mkind,
        &njumbled, &nzeros);
    printf ("(L) RBok status "ID" "ID" "ID"\n", status, njumbled, nzeros);
    if (status != RBIO_OK || njumbled != 0) {
        printf ("RBok Error!\n");
        return(EXIT_FAILURE);
    }

    SuiteSparse_free (Ap, NULL);
    SuiteSparse_free (Ai, NULL);
    SuiteSparse_free (Ax, NULL);

    printf ("RBdemo OK\n");
    return (EXIT_SUCCESS);
}