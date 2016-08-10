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
#ifndef _MEM_REG_H
#define _MEM_REG_H

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
