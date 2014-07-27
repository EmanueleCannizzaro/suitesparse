#include "cxsparse.h"
/* load a triplet matrix from a file */
cs *cs_load (FILE *f)
{
    double i, j ;   /* use double for integers to avoid csi conflicts */
    double x ;
#ifdef CS_COMPLEX
    double xi ;
#endif
    cs *T ;
    if (!f) return (NULL) ;                             /* check inputs */
    T = cs_spalloc (0, 0, 1, 1, 1) ;                    /* allocate result */
#ifdef CS_COMPLEX
    while (fscanf (f, "%lg %lg %lg %lg\n", &i, &j, &x, &xi) == 4)
#else
    while (fscanf (f, "%lg %lg %lg\n", &i, &j, &x) == 3)
#endif
    {
#ifdef CS_COMPLEX
        if (!cs_entry (T, (Int) i, (Int) j, x + xi*I)) return (cs_spfree (T)) ;
#else
        if (!cs_entry (T, (Int) i, (Int) j, x)) return (cs_spfree (T)) ;
#endif
    }
    return (T) ;
}
