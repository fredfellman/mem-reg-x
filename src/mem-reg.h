#ifndef _MEM_REG_H
#define _MEM_REG_H

#define MEM_REGIONS_BINEXP_INC \
    MEM_REG(int, foo, 3)

#define MEM_REGIONS_LINEAR_INC \
    MEM_REG(double, bar, 32)

#include "mem-reg-def.h"

/*Memory region manager handler*/
typedef struct _mem_reg_s mem_reg_t;

/*Memory region manager allocation/dereferencing*/
mem_reg_t * mem_reg_new(void);
void mem_reg_free(mem_reg_t *);

/*
 * Declaration of function calls to regions defined
 * in MEM_REGIONS_LINEAR_INC and MEM_REGIONS_BINEXP_INC.
 *
 * Functions in form mem_reg_<element name>_new(mem_reg_t * mem)
 * unless macro MEM_REG_NEW_FUNC is overridden.
 */
#define MEM_REG(type, name, init) \
    MEM_REG_NEW_FUNC_DECL(type, name);

MEM_REGIONS
#undef MEM_REG

#endif
