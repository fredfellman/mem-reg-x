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

/*
 * Overridable function call names
 */

/*Function call to create a new element*/
#ifndef MEM_REG_NEW_FUNC
#define MEM_REG_NEW_FUNC(name) mem_reg_ ## name ## _new
#endif

/*
 * Definitions that should NOT be overridden
 */

#define MEM_INST mem

#define MEM_REG_NEW_FUNC_DECL(type, name) \
    type * MEM_REG_NEW_FUNC(name)(mem_reg_t * MEM_INST)

#endif
