
/* ========================================================================== */
/* === colamd_set_defaults ================================================== */
/* ========================================================================== */

/*
    The colamd_set_defaults routine sets the default values of the user-
    controllable parameters for colamd and symamd:

    Colamd: rows with more than max (16, knobs [0] * sqrt (n_col))
    entries are removed prior to ordering.  Columns with more than
    max (16, knobs [1] * sqrt (MIN (n_row,n_col))) entries are removed
    prior to ordering, and placed last in the output column ordering.

    Symamd: Rows and columns with more than max (16, knobs [0] * sqrt (n))
    entries are removed prior to ordering, and placed last in the
    output ordering.

    knobs [0]	dense row control

    knobs [1]	dense column control

    knobs [2]	if nonzero, do aggresive absorption

    knobs [3..19]	unused, but future versions might use this

*/

#include "colamd.h"

PUBLIC void colamd_set_defaults
(
        /* === Parameters ======================================================= */

        double knobs [COLAMD_KNOBS]		/* knob array */
        )
{
    /* === Local variables ================================================== */

    Int i ;

    if (!knobs) {
        return ;			/* no knobs to initialize */
    }
    for (i = 0 ; i < COLAMD_KNOBS ; i++) {
        knobs [i] = 0 ;
    }
    knobs [COLAMD_DENSE_ROW] = 10 ;
    knobs [COLAMD_DENSE_COL] = 10 ;
    knobs [COLAMD_AGGRESSIVE] = TRUE ;	/* default: do aggressive absorption*/
}

