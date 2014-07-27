/* ========================================================================== */
/* === colamd/symamd prototypes and definitions ============================= */
/* ========================================================================== */

/* COLAMD / SYMAMD include file

    You must include this file (colamd.h) in any routine that uses colamd,
    symamd, or the related macros and definitions.

    Authors:

	The authors of the code itself are Stefan I. Larimore and Timothy A.
	Davis (DrTimothyAldenDavis@gmail.com).  The algorithm was
	developed in collaboration with John Gilbert, Xerox PARC, and Esmond
	Ng, Oak Ridge National Laboratory.

    Acknowledgements:

	This work was supported by the National Science Foundation, under
	grants DMS-9504974 and DMS-9803599.

    Notice:

	Copyright (c) 1998-2007, Timothy A. Davis, All Rights Reserved.

	THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY
	EXPRESSED OR IMPLIED.  ANY USE IS AT YOUR OWN RISK.

	Permission is hereby granted to use, copy, modify, and/or distribute
	this program, provided that the Copyright, this License, and the
	Availability of the original version is retained on all copies and made
	accessible to the end-user of any code or package that includes COLAMD
	or any modified version of COLAMD. 

    Availability:

	The colamd/symamd library is available at http://www.suitesparse.com
	This file is required by the colamd.c, colamdmex.c, and symamdmex.c
	files, and by any C code that calls the routines whose prototypes are
	listed below, or that uses the colamd/symamd definitions listed below.

*/

#ifndef COLAMD_H
#define COLAMD_H

/* make it easy for C++ programs to include COLAMD */
#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/* === Include files ======================================================== */
/* ========================================================================== */

#include <stdlib.h>

/* ========================================================================== */
/* === Prototypes of user-callable routines ================================= */
/* ========================================================================== */

#include "SuiteSparse_config.h"

#if defined (DLONG)
#define COLAMD(name) colamd ## _l_ ## name
#define SYMAMD(name) symamd ## _l_ ## name
#else
#define COLAMD(name) colamd ## _i_ ## name
#define SYMAMD(name) symamd ## _i_ ## name
#endif

/* Ensure that debugging is turned off: */
#ifndef NDEBUG
#define NDEBUG
#endif

/* size of the Col and Row structures */
#define COLAMD_C(n_col,ok) \
    ((t_mult (t_add (n_col, 1, ok), sizeof (Colamd_Col), ok) / sizeof (Int)))

#define COLAMD_R(n_row,ok) \
    ((t_mult (t_add (n_row, 1, ok), sizeof (Colamd_Row), ok) / sizeof (Int)))


/* turn on debugging by uncommenting the following line
 #undef NDEBUG
*/

size_t COLAMD(recommended)	/* returns recommended value of Alen, */
                /* or 0 if input arguments are erroneous */
(
    Int nnz,			/* nonzeros in A */
    Int n_row,			/* number of rows in A */
    Int n_col			/* number of columns in A */
) ;

void colamd_set_defaults	/* sets default parameters */
(				/* knobs argument is modified on output */
    double knobs []	/* parameter settings for colamd */
) ;

Int COLAMD()			/* returns (1) if successful, (0) otherwise*/
(				/* A and p arguments are modified on output */
    Int n_row,			/* number of rows in A */
    Int n_col,			/* number of columns in A */
    Int Alen,			/* size of the array A */
    Int A [],			/* row indices of A, of size Alen */
    Int p [],			/* column pointers of A, of size n_col+1 */
    double knobs [],/* parameter settings for colamd */
    Int stats []	/* colamd output statistics and error codes */
) ;

Int SYMAMD()				/* return (1) if OK, (0) otherwise */
(
    Int n,				/* number of rows and columns of A */
    Int A [],				/* row indices of A */
    Int p [],				/* column pointers of A */
    Int perm [],			/* output permutation, size n_col+1 */
    double knobs [],	/* parameters (uses defaults if NULL) */
    Int stats [],		/* output statistics and error codes */
    void * (*allocate) (size_t, size_t),
                        /* pointer to calloc (ANSI C) or */
                    /* mxCalloc (for MATLAB mexFunction) */
    void (*release) (void *)
                        /* pointer to free (ANSI C) or */
                        /* mxFree (for MATLAB mexFunction) */
) ;

void COLAMD(report)
(
    Int stats []
) ;

void SYMAMD(report)
(
    Int stats []
) ;


#include <limits.h>
#include <math.h>

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#include "matrix.h"
#endif /* MATLAB_MEX_FILE */

#if !defined (NPRINT) || !defined (NDEBUG)
#include <stdio.h>
#endif

/* ========================================================================== */
/* === Row and Column structures ============================================ */
/* ========================================================================== */

/* User code that makes use of the colamd/symamd routines need not directly */
/* reference these structures.  They are used only for colamd_recommended. */

typedef struct Colamd_Col_struct
{
    Int start ;		/* index for A of first row in this column, or DEAD */
            /* if column is dead */
    Int length ;	/* number of rows in this column */
    union
    {
    Int thickness ;	/* number of original columns represented by this */
            /* col, if the column is alive */
    Int parent ;	/* parent in parent tree super-column structure, if */
            /* the column is dead */
    } shared1 ;
    union
    {
    Int score ;	/* the score used to maintain heap, if col is alive */
    Int order ;	/* pivot ordering of this column, if col is dead */
    } shared2 ;
    union
    {
    Int headhash ;	/* head of a hash bucket, if col is at the head of */
            /* a degree list */
    Int hash ;	/* hash value, if col is not in a degree list */
    Int prev ;	/* previous column in degree list, if col is in a */
            /* degree list (but not at the head of a degree list) */
    } shared3 ;
    union
    {
    Int degree_next ;	/* next column, if col is in a degree list */
    Int hash_next ;		/* next column, if col is in a hash list */
    } shared4 ;

} Colamd_Col ;

typedef struct Colamd_Row_struct
{
    Int start ;		/* index for A of first col in this row */
    Int length ;	/* number of principal columns in this row */
    union
    {
    Int degree ;	/* number of principal & non-principal columns in row */
    Int p ;		/* used as a row pointer in init_rows_cols () */
    } shared1 ;
    union
    {
    Int mark ;	/* for computing set differences and marking dead rows*/
    Int first_column ;/* first column in row (used in garbage collection) */
    } shared2 ;

} Colamd_Row ;

/* ========================================================================== */
/* === Definitions ========================================================== */
/* ========================================================================== */

/* Routines are either PUBLIC (user-callable) or PRIVATE (not user-callable) */
#define PUBLIC
#define PRIVATE static

#define DENSE_DEGREE(alpha,n) \
    ((Int) MAX (16.0, (alpha) * sqrt ((double) (n))))

#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))

#define ONES_COMPLEMENT(r) (-(r)-1)

/* -------------------------------------------------------------------------- */
/* Change for version 2.1:  define TRUE and FALSE only if not yet defined */
/* -------------------------------------------------------------------------- */

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

/* -------------------------------------------------------------------------- */

#define EMPTY	(-1)

/* Row and column status */
#define ALIVE	(0)
#define DEAD	(-1)

/* Column status */
#define DEAD_PRINCIPAL		(-1)
#define DEAD_NON_PRINCIPAL	(-2)

/* Macros for row and column status update and checking. */
#define ROW_IS_DEAD(r)			ROW_IS_MARKED_DEAD (Row[r].shared2.mark)
#define ROW_IS_MARKED_DEAD(row_mark)	(row_mark < ALIVE)
#define ROW_IS_ALIVE(r)			(Row [r].shared2.mark >= ALIVE)
#define COL_IS_DEAD(c)			(Col [c].start < ALIVE)
#define COL_IS_ALIVE(c)			(Col [c].start >= ALIVE)
#define COL_IS_DEAD_PRINCIPAL(c)	(Col [c].start == DEAD_PRINCIPAL)
#define KILL_ROW(r)			{ Row [r].shared2.mark = DEAD ; }
#define KILL_PRINCIPAL_COL(c)		{ Col [c].start = DEAD_PRINCIPAL ; }
#define KILL_NON_PRINCIPAL_COL(c)	{ Col [c].start = DEAD_NON_PRINCIPAL ; }

/* ========================================================================== */
/* === Colamd reporting mechanism =========================================== */
/* ========================================================================== */

#if defined (MATLAB_MEX_FILE) || defined (MATHWORKS)
/* In MATLAB, matrices are 1-based to the user, but 0-based internally */
#define INDEX(i) ((i)+1)
#else
/* In C, matrices are 0-based and indices are reported as such in *_report */
#define INDEX(i) (i)
#endif

/* All output goes through the PRINTF macro.  */
#define PRINTF(params) { if (colamd_printf != NULL) (void) colamd_printf params ; }

/* ========================================================================== */
/* === Prototypes of PRIVATE routines ======================================= */
/* ========================================================================== */

PRIVATE Int init_rows_cols
(
    Int n_row,
    Int n_col,
    Colamd_Row Row [],
    Colamd_Col Col [],
    Int A [],
    Int p [],
    Int stats []
) ;

PRIVATE void init_scoring
(
    Int n_row,
    Int n_col,
    Colamd_Row Row [],
    Colamd_Col Col [],
    Int A [],
    Int head [],
    double knobs [],
    Int *p_n_row2,
    Int *p_n_col2,
    Int *p_max_deg
) ;

PRIVATE Int find_ordering
(
    Int n_row,
    Int n_col,
    Int Alen,
    Colamd_Row Row [],
    Colamd_Col Col [],
    Int A [],
    Int head [],
    Int n_col2,
    Int max_deg,
    Int pfree,
    Int aggressive
) ;

PRIVATE void order_children
(
    Int n_col,
    Colamd_Col Col [],
    Int p []
) ;

PRIVATE void detect_super_cols
(

#ifndef NDEBUG
    Int n_col,
    Colamd_Row Row [],
#endif /* NDEBUG */

    Colamd_Col Col [],
    Int A [],
    Int head [],
    Int row_start,
    Int row_length
) ;

PRIVATE Int garbage_collection
(
    Int n_row,
    Int n_col,
    Colamd_Row Row [],
    Colamd_Col Col [],
    Int A [],
    Int *pfree
) ;

PRIVATE Int clear_mark
(
    Int tag_mark,
    Int max_mark,
    Int n_row,
    Colamd_Row Row []
) ;

PRIVATE void print_report
(
    char *method,
    Int stats []
) ;

/* ========================================================================== */
/* === Debugging prototypes and definitions ================================= */
/* ========================================================================== */

#ifndef NDEBUG

#include <assert.h>

/* colamd_debug is the *ONLY* global variable, and is only */
/* present when debugging */

PRIVATE Int colamd_debug = 0 ;	/* debug print level */

#define DEBUG0(params) { PRINTF (params) ; }
#define DEBUG1(params) { if (colamd_debug >= 1) PRINTF (params) ; }
#define DEBUG2(params) { if (colamd_debug >= 2) PRINTF (params) ; }
#define DEBUG3(params) { if (colamd_debug >= 3) PRINTF (params) ; }
#define DEBUG4(params) { if (colamd_debug >= 4) PRINTF (params) ; }

#ifdef MATLAB_MEX_FILE
#define ASSERT(expression) (mxAssert ((expression), ""))
#else
#define ASSERT(expression) (assert (expression))
#endif /* MATLAB_MEX_FILE */

PRIVATE void colamd_get_debug	/* gets the debug print level from getenv */
(
    char *method
) ;

PRIVATE void debug_deg_lists
(
    Int n_row,
    Int n_col,
    Colamd_Row Row [],
    Colamd_Col Col [],
    Int head [],
    Int min_score,
    Int should,
    Int max_deg
) ;

PRIVATE void debug_mark
(
    Int n_row,
    Colamd_Row Row [],
    Int tag_mark,
    Int max_mark
) ;

PRIVATE void debug_matrix
(
    Int n_row,
    Int n_col,
    Colamd_Row Row [],
    Colamd_Col Col [],
    Int A []
) ;

PRIVATE void debug_structures
(
    Int n_row,
    Int n_col,
    Colamd_Row Row [],
    Colamd_Col Col [],
    Int A [],
    Int n_col2
) ;

#else /* NDEBUG */

/* === No debugging ========================================================= */

#define DEBUG0(params) ;
#define DEBUG1(params) ;
#define DEBUG2(params) ;
#define DEBUG3(params) ;
#define DEBUG4(params) ;

#define ASSERT(expression)

#endif /* NDEBUG */

/* ========================================================================== */
/* === COLAMD version ======================================================= */
/* ========================================================================== */

/* COLAMD Version 2.4 and later will include the following definitions.
 * As an example, to test if the version you are using is 2.4 or later:
 *
 * #ifdef COLAMD_VERSION
 *	if (COLAMD_VERSION >= COLAMD_VERSION_CODE (2,4)) ...
 * #endif
 *
 * This also works during compile-time:
 *
 *  #if defined(COLAMD_VERSION) && (COLAMD_VERSION >= COLAMD_VERSION_CODE (2,4))
 *    printf ("This is version 2.4 or later\n") ;
 *  #else
 *    printf ("This is an early version\n") ;
 *  #endif
 *
 * Versions 2.3 and earlier of COLAMD do not include a #define'd version number.
 */

#define COLAMD_DATE "Jun 1, 2012"
#define COLAMD_VERSION_CODE(main,sub) ((main) * 1000 + (sub))
#define COLAMD_MAIN_VERSION 2
#define COLAMD_SUB_VERSION 8
#define COLAMD_SUBSUB_VERSION 0
#define COLAMD_VERSION \
	COLAMD_VERSION_CODE(COLAMD_MAIN_VERSION,COLAMD_SUB_VERSION)

/* ========================================================================== */
/* === Knob and statistics definitions ====================================== */
/* ========================================================================== */

/* size of the knobs [ ] array.  Only knobs [0..1] are currently used. */
#define COLAMD_KNOBS 20

/* number of output statistics.  Only stats [0..6] are currently used. */
#define COLAMD_STATS 20

/* knobs [0] and stats [0]: dense row knob and output statistic. */
#define COLAMD_DENSE_ROW 0

/* knobs [1] and stats [1]: dense column knob and output statistic. */
#define COLAMD_DENSE_COL 1

/* knobs [2]: aggressive absorption */
#define COLAMD_AGGRESSIVE 2

/* stats [2]: memory defragmentation count output statistic */
#define COLAMD_DEFRAG_COUNT 2

/* stats [3]: colamd status:  zero OK, > 0 warning or notice, < 0 error */
#define COLAMD_STATUS 3

/* stats [4..6]: error info, or info on jumbled columns */ 
#define COLAMD_INFO1 4
#define COLAMD_INFO2 5
#define COLAMD_INFO3 6

/* error codes returned in stats [3]: */
#define COLAMD_OK				(0)
#define COLAMD_OK_BUT_JUMBLED			(1)
#define COLAMD_ERROR_A_not_present		(-1)
#define COLAMD_ERROR_p_not_present		(-2)
#define COLAMD_ERROR_nrow_negative		(-3)
#define COLAMD_ERROR_ncol_negative		(-4)
#define COLAMD_ERROR_nnz_negative		(-5)
#define COLAMD_ERROR_p0_nonzero			(-6)
#define COLAMD_ERROR_A_too_small		(-7)
#define COLAMD_ERROR_col_length_negative	(-8)
#define COLAMD_ERROR_row_index_out_of_bounds	(-9)
#define COLAMD_ERROR_out_of_memory		(-10)
#define COLAMD_ERROR_internal_error		(-999)


#ifndef EXTERN
#define EXTERN extern
#endif

EXTERN int (*colamd_printf) (const char *, ...) ;

#ifdef __cplusplus
}
#endif

#endif /* COLAMD_H */
