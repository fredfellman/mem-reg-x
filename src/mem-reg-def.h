/*
 * mem-reg-x - Memory Region Manager
 * Copyright © 2016 Ryan Jones <ryan@rjones.io>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
#ifndef _MEM_REG_DEF_H
#define _MEM_REG_DEF_H

/*
 * Override the following pre-processor definitions to use
 * custom memory allocation functions.
 */
#ifndef MEM_REG_MALLOC
#include <stdlib.h>
#define MEM_REG_MALLOC malloc
#endif

#ifndef MEM_REG_CALLOC
#include <stdlib.h>
#define MEM_REG_CALLOC calloc
#endif

#ifndef MEM_REG_FREE
#include <stdlib.h>
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
