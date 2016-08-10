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
/*Include user definitions*/
#define _M_STROF_AUX(n) #n
#define _M_STROF(n) _M_STROF_AUX(n)

#ifdef MEM_REG_INCLUDE
#include _M_STROF(MEM_REG_INCLUDE)
#endif

#include "mem-reg.h"

/*Make sure that null has been declared (in case std-lib was not included)*/
#ifndef NULL
#include <stddef.h>
#endif

/*
 * Common macros
 */
#define _free MEM_REG_FREE

#ifdef MEM_REG_NO_CALLOC
#define _alloc(nmemb, size) MEM_REG_MALLOC(nmemb * size)
#else
#define _alloc(nmemb, size) MEM_REG_CALLOC(nmemb, size)
#endif

#define _REGION_SIZE(reg) (((reg)->tail - (reg)->head) + 1)

/*
 * Private X-Macros
 */

#define _M_NODE_VAR node
#define _M_SIZE_VAR size

#define _M_NODE_NAME(name) _node_ ## name
#define _M_NODE_STRUCT_NAME(name) _node_ ## name ## _s
#define _M_NODE_STRUCT(name) struct _M_NODE_STRUCT_NAME(name)

#define _M_NODE_INIT_FUNC(name) _node_ ## name ## _init
#define _M_NODE_INIT_DECL(name) \
    static _M_NODE_STRUCT(name) * _M_NODE_INIT_FUNC(name)(unsigned int _M_SIZE_VAR)

#define _M_NODE_FREE_FUNC(name) _node_ ## name ## _free
#define _M_NODE_FREE_DECL(name) \
    static void _M_NODE_FREE_FUNC(name)(_M_NODE_STRUCT(name) * _M_NODE_VAR)

#define _M_NODE_GET_ELEM_FUNC(name) _node_ ## name ## _get_elem
#define _M_NODE_GET_ELEM_DECL(type, name) \
    static type * _M_NODE_GET_ELEM_FUNC(name)(mem_reg_t * MEM_INST)

#define _M_NODE_NEXT_REG_SIZE_FUNC(name) _node_ ## name ## _next_size
#define _M_NODE_NEXT_REG_SIZE_DECL(name)                 \
    static unsigned int _M_NODE_NEXT_REG_SIZE_FUNC(name) \
        (_M_NODE_STRUCT(name) * _M_NODE_VAR)

#define _MEM_INST_NODE(name) MEM_INST->_M_NODE_NAME(name)
#define _MEM_INST_NODE_HEAD(name) _MEM_INST_NODE(name).head
#define _MEM_INST_NODE_INDEX(name) _MEM_INST_NODE(name).index

/*
 * Private structures
 */

/*Declare a linked-list node structure for each element type*/
#define MEM_REG(type, name, inst)       \
    _M_NODE_STRUCT(name) {              \
        type * head, * tail, * index;   \
        _M_NODE_STRUCT(name) * next;    \
    };

MEM_REGIONS
#undef MEM_REG

struct _mem_reg_s {
/*Declare references to nodes of all element types*/
#define MEM_REG(type, name, inst)               \
    struct {                                    \
        _M_NODE_STRUCT(name) * head, * index;   \
    } _M_NODE_NAME(name);

MEM_REGIONS
#undef MEM_REG
};

/*
 *Private Prototypes
 */

#define MEM_REG(type, name, inst)       \
    _M_NODE_INIT_DECL(name);            \
    _M_NODE_FREE_DECL(name);            \
    _M_NODE_GET_ELEM_DECL(type, name);  \
    _M_NODE_NEXT_REG_SIZE_DECL(name);

MEM_REGIONS
#undef MEM_REG

/*
 * Public External Functions
 */

mem_reg_t * mem_reg_new(void)
{
    mem_reg_t * MEM_INST = NULL;
    int error_status = 0;

    do {
        /*
         * Allocate handle. Note that we directly use calloc regardless
         * of if the user defined MEM_REG_NO_CALLOC
         */
        MEM_INST = MEM_REG_CALLOC(1, sizeof(mem_reg_t));
        if(!MEM_INST){
            error_status = -1;
            continue;
        }

        /*Initialize memory regions*/
#define MEM_REG(type, name, init)   \
        _MEM_INST_NODE_HEAD(name) = _M_NODE_INIT_FUNC(name)(init); \
        \
        if(! (_MEM_INST_NODE_HEAD(name))){  \
            error_status = -1;              \
            continue;                       \
        } \
        /*Set index to head*/           \
        _MEM_INST_NODE_INDEX(name) =    \
            _MEM_INST_NODE_HEAD(name);

MEM_REGIONS
#undef MEM_REG
    } while (0);

    /*Clean up if an error occurred during initialization*/
    if(error_status < 0){
        mem_reg_free(MEM_INST);
        MEM_INST = NULL;
    }

    return MEM_INST;
}

void mem_reg_free(mem_reg_t * mem_mgr)
{
    if(!mem_mgr) return;

    /*Dereference each region node*/
#define MEM_REG(type, name, init)                   \
    while(mem_mgr->_M_NODE_NAME(name).head){        \
        mem_mgr->_M_NODE_NAME(name).index =         \
            mem_mgr->_M_NODE_NAME(name).head;       \
        mem_mgr->_M_NODE_NAME(name).head =          \
            mem_mgr->_M_NODE_NAME(name).head->next; \
        \
        _M_NODE_FREE_FUNC(name)(mem_mgr->_M_NODE_NAME(name).index); \
    }

MEM_REGIONS
#undef MEM_REG
    /*Dereference memory manager*/
    _free(mem_mgr);
}

/*Public "mem_reg_<element>_new()" functions*/
#define MEM_REG(type, name, init)   \
MEM_REG_NEW_FUNC_DECL(type, name)   \
{ \
    /*Check that handle is valid*/  \
    if(!MEM_INST)                   \
        return NULL;                \
    \
    /*Make sure that index as at the tail of the list*/  \
    while(MEM_INST->_M_NODE_NAME(name).index->next) {    \
        MEM_INST->_M_NODE_NAME(name).index =             \
            MEM_INST->_M_NODE_NAME(name).index->next;    \
    } \
    return _M_NODE_GET_ELEM_FUNC(name)(MEM_INST); \
}

MEM_REGIONS
#undef MEM_REG

/*
 * Private Functions
 */

/*Node Initialization*/
#define MEM_REG(type, name, init)   \
_M_NODE_INIT_DECL(name)             \
{ \
    /*Allocate region node*/                                    \
    _M_NODE_STRUCT(name) * new_inst = NULL;                     \
    new_inst = MEM_REG_CALLOC(1, sizeof(_M_NODE_STRUCT(name))); \
    if(!new_inst)                                               \
        return NULL;                                            \
    \
    /*Allocate elements in node*/                   \
    new_inst->head = _alloc(init, sizeof(type));    \
    if(!new_inst->head){                            \
        _free(new_inst);                            \
        return NULL;                                \
    }                                               \
    \
    /*Initialize element references*/                       \
    new_inst->tail = new_inst->head + (_M_SIZE_VAR - 1);    \
    new_inst->index = new_inst->head;                       \
    \
    return new_inst; \
}

MEM_REGIONS
#undef MEM_REG

/*Node de-referencing*/
#define MEM_REG(type, name, init)   \
_M_NODE_FREE_DECL(name)             \
{ \
    /*Check for valid reference*/   \
    if(! _M_NODE_VAR)               \
        return;                     \
    \
    /*Free Elements*/               \
    if(_M_NODE_VAR->head)           \
        _free(_M_NODE_VAR->head);   \
    \
    /*Free Region Node*/    \
    _free(_M_NODE_VAR);     \
}

MEM_REGIONS
#undef MEM_REG

/*Get the next available element in a node*/
#define MEM_REG(type, name, init)   \
_M_NODE_GET_ELEM_DECL(type, name)   \
{ \
    type * ret_elem = NULL; \
    \
    /*Set the return element from index*/ \
    ret_elem = MEM_INST->_M_NODE_NAME(name).index->index; \
    \
    /*Check to see if we are at the end of the region*/ \
    if(_MEM_INST_NODE_INDEX(name)->index ==         \
            _MEM_INST_NODE_INDEX(name)->tail){      \
        _MEM_INST_NODE_INDEX(name)->next =          \
            _M_NODE_INIT_FUNC(name)                 \
                (_M_NODE_NEXT_REG_SIZE_FUNC(name)   \
                    (_MEM_INST_NODE_INDEX(name)));  \
        _MEM_INST_NODE_INDEX(name) =            \
            _MEM_INST_NODE_INDEX(name)->next;   \
    } else { \
        _MEM_INST_NODE_INDEX(name)->index++; \
    } \
    return ret_elem; \
}

MEM_REGIONS
#undef MEM_REG

/*Next region size functions for linear increases*/
#define MEM_REG(type, name, init)   \
_M_NODE_NEXT_REG_SIZE_DECL(name)    \
{ \
    return _REGION_SIZE(_M_NODE_VAR); \
}

MEM_REGIONS_LINEAR_INC
#undef MEM_REG

/*Next region size functions for  increases*/
#define MEM_REG(type, name, init)   \
_M_NODE_NEXT_REG_SIZE_DECL(name)    \
{ \
    return (_REGION_SIZE(_M_NODE_VAR)<<1); \
}

MEM_REGIONS_BINEXP_INC
#undef MEM_REG
