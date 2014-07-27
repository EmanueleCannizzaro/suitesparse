/* ========================================================================== */
/* === CCOLAMD/ccolamd.h ==================================================== */
/* ========================================================================== */

/* ----------------------------------------------------------------------------
 * CCOLAMD Copyright (C), Univ. of Florida.  Authors: Timothy A. Davis,
 * Sivasankaran Rajamanickam, and Stefan Larimore
 * See License.txt for the Version 2.1 of the GNU Lesser General Public License
 * -------------------------------------------------------------------------- */

/*
 *  You must include this file (ccolamd.h) in any routine that uses ccolamd,
 *  csymamd, or the related macros and definitions.
 */

#ifndef CCOLAMD_H
#define CCOLAMD_H

/* make it easy for C++ programs to include CCOLAMD */
#ifdef __cplusplus
extern "C" {
#endif

/* for size_t definition: */
#include <stdlib.h>

/* ========================================================================== */
/* === Prototypes of user-callable routines ================================= */
/* ========================================================================== */

#include "SuiteSparse_config.h"

#if defined (DLONG)
#define CCOLAMD(name) ccolamd ## _l_ ## name
#define CSYMAMD(name) csymamd ## _l_ ## name
#else
#define CCOLAMD(name) ccolamd ## _i_ ## name
#define CSYMAMD(name) csymamd ## _i_ ## name
#endif

/* Ensure that debugging is turned off: */
#ifndef NDEBUG
#define NDEBUG
#endif

/* size of the Col and Row structures */
#define CCOLAMD_C(n_col,ok) \
    ((t_mult (t_add (n_col, 1, ok), sizeof (CColamd_Col), ok) / sizeof (Int)))

#define CCOLAMD_R(n_row,ok) \
    ((t_mult (t_add (n_row, 1, ok), sizeof (CColamd_Row), ok) / sizeof (Int)))

/*
#define CCOLAMD_RECOMMENDED(nnz, n_row, n_col) \
        MAX (2 * nnz, 4 * n_col) + \
        CCOLAMD_C (n_col) + CCOLAMD_R (n_row) + n_col + (nnz / 5) \
        + ((3 * n_col) + 1) + 5 * (n_col + 1) + n_row
 */


/* ========================================================================== */
/* === Row and Column structures ============================================ */
/* ========================================================================== */

typedef struct CColamd_Col_struct
{
    /* size of this struct is 8 integers if no padding occurs */

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
    Int score ;
    Int order ;
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

    Int nextcol ;       /* next column in this supercolumn */
    Int lastcol ;       /* last column in this supercolumn */

} CColamd_Col ;


typedef struct CColamd_Row_struct
{
    /* size of this struct is 6 integers if no padding occurs */

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

    Int thickness ;     /* number of original rows represented by this row */
                        /* that are not yet pivotal */
    Int front ;         /* -1 if an original row */
                /* k if this row represents the kth frontal matrix */
                        /* where k goes from 0 to at most n_col-1 */

} CColamd_Row ;

/* ========================================================================== */
/* === basic definitions ==================================================== */
/* ========================================================================== */

#define EMPTY (-1)
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))

/* Routines are either PUBLIC (user-callable) or PRIVATE (not user-callable) */
#define GLOBAL
#define PUBLIC
#define PRIVATE static

#define DENSE_DEGREE(alpha,n) \
    ((Int) MAX (16.0, (alpha) * sqrt ((double) (n))))

#define CMEMBER(c) ((cmember == (Int *) NULL) ? (0) : (cmember [c]))

/* True if x is NaN */
#define SCALAR_IS_NAN(x)        ((x) != (x))

/* true if an integer (stored in double x) would overflow (or if x is NaN) */
#define INT_OVERFLOW(x) ((!((x) * (1.0+1e-8) <= (double) Int_MAX)) \
                        || SCALAR_IS_NAN (x))

#define ONES_COMPLEMENT(r) (-(r)-1)
#undef TRUE
#undef FALSE
#define TRUE (1)
#define FALSE (0)

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
/* === ccolamd reporting mechanism ========================================== */
/* ========================================================================== */

#if defined (MATLAB_MEX_FILE) || defined (MATHWORKS)
/* In MATLAB, matrices are 1-based to the user, but 0-based internally */
#define INDEX(i) ((i)+1)
#else
/* In C, matrices are 0-based and indices are reported as such in *_report */
#define INDEX(i) (i)
#endif

/* All output goes through the PRINTF macro.  */
#define PRINTF(params) { if (ccolamd_printf != NULL) (void) ccolamd_printf params ; }


/* ========================================================================== */
/* === Debugging prototypes and definitions ================================= */
/* ========================================================================== */

#ifndef NDEBUG

#include <assert.h>

/* debug print level, present only when debugging */
PRIVATE Int ccolamd_debug ;

/* debug print statements */
#define DEBUG0(params) { PRINTF (params) ; }
#define DEBUG1(params) { if (ccolamd_debug >= 1) PRINTF (params) ; }
#define DEBUG2(params) { if (ccolamd_debug >= 2) PRINTF (params) ; }
#define DEBUG3(params) { if (ccolamd_debug >= 3) PRINTF (params) ; }
#define DEBUG4(params) { if (ccolamd_debug >= 4) PRINTF (params) ; }

#ifdef MATLAB_MEX_FILE
#define ASSERT(expression) (mxAssert ((expression), ""))
#else
#define ASSERT(expression) (assert (expression))
#endif

PRIVATE void ccolamd_get_debug
(
    char *method
) ;

PRIVATE void debug_mark
(
    Int n_row,
    CColamd_Row Row [],
    Int tag_mark,
    Int max_mark
) ;

PRIVATE void debug_matrix
(
    Int n_row,
    Int n_col,
    CColamd_Row Row [],
    CColamd_Col Col [],
    Int A []
) ;

PRIVATE void debug_structures
(
    Int n_row,
    Int n_col,
    CColamd_Row Row [],
    CColamd_Col Col [],
    Int A [],
    Int in_cset [],
    Int cset_start []
) ;

PRIVATE void dump_super
(
    Int super_c,
    CColamd_Col Col [],
    Int n_col
) ;

PRIVATE void debug_deg_lists
(
    Int n_row,
    Int n_col,
    CColamd_Row Row [ ],
    CColamd_Col Col [ ],
    Int head [ ],
    Int min_score,
    Int should,
    Int max_deg
) ;

#else

/* === No debugging ========================================================= */

#define DEBUG0(params) ;
#define DEBUG1(params) ;
#define DEBUG2(params) ;
#define DEBUG3(params) ;
#define DEBUG4(params) ;

#define ASSERT(expression)

#endif

/* ========================================================================== */
/* === Prototypes of PRIVATE routines ======================================= */
/* ========================================================================== */

PRIVATE Int init_rows_cols
(
    Int n_row,
    Int n_col,
    CColamd_Row Row [ ],
    CColamd_Col Col [ ],
    Int A [ ],
    Int p [ ],
    Int stats []
) ;

PRIVATE void init_scoring
(
    Int n_row,
    Int n_col,
    CColamd_Row Row [ ],
    CColamd_Col Col [ ],
    Int A [ ],
    Int head [ ],
    double knobs [],
    Int *p_n_row2,
    Int *p_n_col2,
    Int *p_max_deg,
    Int cmember [ ],
    Int n_cset,
    Int cset_start [ ],
    Int dead_cols [ ],
    Int *p_ndense_row,		/* number of dense rows */
    Int *p_nempty_row,		/* number of original empty rows */
    Int *p_nnewlyempty_row,	/* number of newly empty rows */
    Int *p_ndense_col,		/* number of dense cols (excl "empty" cols) */
    Int *p_nempty_col,		/* number of original empty cols */
    Int *p_nnewlyempty_col	/* number of newly empty cols */
) ;

PRIVATE Int find_ordering
(
    Int n_row,
    Int n_col,
    Int Alen,
    CColamd_Row Row [ ],
    CColamd_Col Col [ ],
    Int A [ ],
    Int head [ ],
#ifndef NDEBUG
    Int n_col2,
#endif
    Int max_deg,
    Int pfree,
    Int cset [ ],
    Int cset_start [ ],
#ifndef NDEBUG
    Int n_cset,
#endif
    Int cmember [ ],
    Int Front_npivcol [ ],
    Int Front_nrows [ ],
    Int Front_ncols [ ],
    Int Front_parent [ ],
    Int Front_cols [ ],
    Int *p_nfr,
    Int aggressive,
    Int InFront [ ],
    Int order_for_lu
) ;

PRIVATE void detect_super_cols
(
#ifndef NDEBUG
    Int n_col,
    CColamd_Row Row [ ],
#endif
    CColamd_Col Col [ ],
    Int A [ ],
    Int head [ ],
    Int row_start,
    Int row_length,
    Int in_set [ ]
) ;

PRIVATE Int garbage_collection
(
    Int n_row,
    Int n_col,
    CColamd_Row Row [ ],
    CColamd_Col Col [ ],
    Int A [ ],
    Int *pfree
) ;

PRIVATE Int clear_mark
(
    Int tag_mark,
    Int max_mark,
    Int n_row,
    CColamd_Row Row [ ]
) ;

PRIVATE void print_report
(
    char *method,
    Int stats []
) ;


size_t CCOLAMD(recommended)	/* returns recommended value of Alen, */
                /* or 0 if input arguments are erroneous */
(
    Int nnz,			/* nonzeros in A */
    Int n_row,			/* number of rows in A */
    Int n_col			/* number of columns in A */
) ;

void ccolamd_set_defaults	/* sets default parameters */
(				/* knobs argument is modified on output */
    double knobs []	/* parameter settings for ccolamd */
) ;

Int CCOLAMD()			/* returns (1) if successful, (0) otherwise*/
(				/* A and p arguments are modified on output */
    Int n_row,			/* number of rows in A */
    Int n_col,			/* number of columns in A */
    Int Alen,			/* size of the array A */
    Int A [ ],			/* row indices of A, of size Alen */
    Int p [ ],			/* column pointers of A, of size n_col+1 */
    double knobs [],/* parameter settings for ccolamd */
    Int stats [],	/* ccolamd output statistics and error codes */
    Int cmember [ ]		/* Constraint set of A, of size n_col */
) ;

Int CSYMAMD()			/* return (1) if OK, (0) otherwise */
(
    Int n,			/* number of rows and columns of A */
    Int A [ ],			/* row indices of A */
    Int p [ ],			/* column pointers of A */
    Int perm [ ],		/* output permutation, size n_col+1 */
    double knobs [],/* parameters (uses defaults if NULL) */
    Int stats [],	/* output statistics and error codes */
    void * (*allocate) (size_t, size_t), /* pointer to calloc (ANSI C) or */
                /* mxCalloc (for MATLAB mexFunction) */
    void (*release) (void *),	/* pointer to free (ANSI C) or */
                    /* mxFree (for MATLAB mexFunction) */
    Int cmember [ ],		/* Constraint set of A */
    Int stype			/* 0: use both parts, >0: upper, <0: lower */
) ;

void CCOLAMD(report)
(
    Int stats []
) ;

void CSYMAMD(report)
(
    Int stats []
) ;

/* ========================================================================== */
/* === Prototypes of "expert" routines ====================================== */
/* ========================================================================== */

/* These routines are meant to be used internally, or in a future version of
 * UMFPACK.  They appear here so that UMFPACK can use them, but they should not
 * be called directly by the user.
 */

Int CCOLAMD(2)
(				/* A and p arguments are modified on output */
    Int n_row,			/* number of rows in A */
    Int n_col,			/* number of columns in A */
    Int Alen,			/* size of the array A */
    Int A [ ],			/* row indices of A, of size Alen */
    Int p [ ],			/* column pointers of A, of size n_col+1 */
    double knobs [],/* parameter settings for ccolamd */
    Int stats [],	/* ccolamd output statistics and error codes */
    /* each Front_ array is of size n_col+1: */
    Int Front_npivcol [ ],	/* # pivot cols in each front */
    Int Front_nrows [ ],	/* # of rows in each front (incl. pivot rows) */
    Int Front_ncols [ ],	/* # of cols in each front (incl. pivot cols) */
    Int Front_parent [ ],	/* parent of each front */
    Int Front_cols [ ],		/* link list of pivot columns for each front */
    Int *p_nfr,			/* total number of frontal matrices */
    Int InFront [ ],		/* InFront [row] = f if row in front f */
    Int cmember [ ]		/* Constraint set of A */
) ;

void CCOLAMD(apply_order)
(
    Int Front [ ],
    const Int Order [ ],
    Int Temp [ ],
    Int nn,
    Int nfr
) ;

void CCOLAMD(fsize)
(
    Int nn,
    Int MaxFsize [ ],
    Int Fnrows [ ],
    Int Fncols [ ],
    Int Parent [ ],
    Int Npiv [ ]
) ;

void CCOLAMD(postorder)
(
    Int nn,
    Int Parent [ ],
    Int Npiv [ ],
    Int Fsize [ ],
    Int Order [ ],
    Int Child [ ],
    Int Sibling [ ],
    Int Stack [ ],
    Int Front_cols [ ],
    Int cmember [ ]
) ;

Int CCOLAMD(post_tree)
(
    Int root,
    Int k,
    Int Child [ ],
    const Int Sibling [ ],
    Int Order [ ],
    Int Stack [ ]
) ;

/* ========================================================================== */
/* === CCOLAMD version ====================================================== */
/* ========================================================================== */

/* All versions of CCOLAMD will include the following definitions.
 * As an example, to test if the version you are using is 1.3 or later:
 *
 *	if (CCOLAMD_VERSION >= CCOLAMD_VERSION_CODE (1,3)) ...
 *
 * This also works during compile-time:
 *
 *	#if CCOLAMD_VERSION >= CCOLAMD_VERSION_CODE (1,3)
 *	    printf ("This is version 1.3 or later\n") ;
 *	#else
 *	    printf ("This is an early version\n") ;
 *	#endif
 */

#define CCOLAMD_DATE "Jun 1, 2012"
#define CCOLAMD_VERSION_CODE(main,sub) ((main) * 1000 + (sub))
#define CCOLAMD_MAIN_VERSION 2
#define CCOLAMD_SUB_VERSION 8
#define CCOLAMD_SUBSUB_VERSION 0
#define CCOLAMD_VERSION \
	CCOLAMD_VERSION_CODE(CCOLAMD_MAIN_VERSION,CCOLAMD_SUB_VERSION)

/* ========================================================================== */
/* === Knob and statistics definitions ====================================== */
/* ========================================================================== */

/* size of the knobs [ ] array.  Only knobs [0..3] are currently used. */
#define CCOLAMD_KNOBS 20

/* number of output statistics.  Only stats [0..10] are currently used. */
#define CCOLAMD_STATS 20

/* knobs [0] and stats [0]: dense row knob and output statistic. */
#define CCOLAMD_DENSE_ROW 0

/* knobs [1] and stats [1]: dense column knob and output statistic. */
#define CCOLAMD_DENSE_COL 1

/* knobs [2]: aggressive absorption option */
#define CCOLAMD_AGGRESSIVE 2

/* knobs [3]: LU or Cholesky factorization option */
#define CCOLAMD_LU 3

/* stats [2]: memory defragmentation count output statistic */
#define CCOLAMD_DEFRAG_COUNT 2

/* stats [3]: ccolamd status:  zero OK, > 0 warning or notice, < 0 error */
#define CCOLAMD_STATUS 3

/* stats [4..6]: error info, or info on jumbled columns */ 
#define CCOLAMD_INFO1 4
#define CCOLAMD_INFO2 5
#define CCOLAMD_INFO3 6

/* stats [7]: number of originally empty rows */
#define CCOLAMD_EMPTY_ROW 7
/* stats [8]: number of originally empty cols */
#define CCOLAMD_EMPTY_COL 8
/* stats [9]: number of rows with entries only in dense cols */
#define CCOLAMD_NEWLY_EMPTY_ROW 9
/* stats [10]: number of cols with entries only in dense rows */
#define CCOLAMD_NEWLY_EMPTY_COL 10

/* error codes returned in stats [3]: */
#define CCOLAMD_OK				(0)
#define CCOLAMD_OK_BUT_JUMBLED			(1)
#define CCOLAMD_ERROR_A_not_present		(-1)
#define CCOLAMD_ERROR_p_not_present		(-2)
#define CCOLAMD_ERROR_nrow_negative		(-3)
#define CCOLAMD_ERROR_ncol_negative		(-4)
#define CCOLAMD_ERROR_nnz_negative		(-5)
#define CCOLAMD_ERROR_p0_nonzero		(-6)
#define CCOLAMD_ERROR_A_too_small		(-7)
#define CCOLAMD_ERROR_col_length_negative	(-8)
#define CCOLAMD_ERROR_row_index_out_of_bounds	(-9)
#define CCOLAMD_ERROR_out_of_memory		(-10)
#define CCOLAMD_ERROR_invalid_cmember		(-11)
#define CCOLAMD_ERROR_internal_error		(-999)

#ifndef EXTERN
#define EXTERN extern
#endif

EXTERN int (*ccolamd_printf) (const char *, ...) ;

#ifdef __cplusplus
}
#endif

#endif
