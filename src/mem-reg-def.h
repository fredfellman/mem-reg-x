#ifndef _MEM_REG_DEF_H
#define _MEM_REG_DEF_H

#include <stdlib.h>

/*
 * Override the following pre-processor definitions to use
 * custom memory allocation functions.
 */
#ifndef MEM_REG_MALLOC
#define MEM_REG_MALLOC malloc
#endif

#ifndef MEM_REG_CALLOC
#define MEM_REG_CALLOC calloc
#endif

#ifndef MEM_REG_FREE
#define MEM_REG_FREE free
#endif

/*
 * User-Defined Memory Regions
 */

#ifndef MEM_REGIONS_LINEAR_INC
#define MEM_REGIONS_LINEAR_INC
#endif

#ifndef MEM_REGIONS_BINEXP_INC
#define MEM_REGIONS_BINEXP_INC
#endif

#define MEM_REGIONS \
    MEM_REGIONS_LINEAR_INC \
    MEM_REGIONS_BINEXP_INC

#endif
