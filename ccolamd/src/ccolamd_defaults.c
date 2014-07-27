

/* ========================================================================== */
/* === ccolamd_set_defaults ================================================= */
/* ========================================================================== */

/*
 *  The ccolamd_set_defaults routine sets the default values of the user-
 *  controllable parameters for ccolamd.
 */

#include "ccolamd.h"

PUBLIC void ccolamd_set_defaults
(
        /* === Parameters ======================================================= */

        double knobs [CCOLAMD_KNOBS]		/* knob array */
        )
{
    /* === Local variables ================================================== */

    Int i ;

    if (!knobs) {
        return ;			/* no knobs to initialize */
    }
    for (i = 0 ; i < CCOLAMD_KNOBS ; i++) {
        knobs [i] = 0 ;
    }
    knobs [CCOLAMD_DENSE_ROW] = 10 ;
    knobs [CCOLAMD_DENSE_COL] = 10 ;
    knobs [CCOLAMD_AGGRESSIVE] = TRUE ;	/* default: do aggressive absorption*/
    knobs [CCOLAMD_LU] = FALSE ;	/* default: order for Cholesky */
}
