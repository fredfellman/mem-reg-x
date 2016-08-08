#include "mem-reg.h"
#include "mem-reg-def.h"

/*
 * Private structures
 */

struct _mem_reg {
    int ref;
};

/*
 * Common macros
 */
#define _free MEM_REG_FREE

#ifdef MEM_REG_NO_CALLOC
#define _alloc(nmemb, size) MEM_REG_MALLOC(nmemb * size)
#else
#define _alloc(nmemb, size) MEM_REG_CALLOC(nmemb, size)
#endif

/*
 * Public External Functions
 */

mem_reg_t * mem_reg_new(void)
{
    mem_reg_t * mem_mgr = NULL;
    int error_status = 0;

    do {
        /*
         * Allocate handle. Note that we directly use calloc regardless
         * of if the user defined MEM_REG_NO_CALLOC
         */
        mem_mgr = MEM_REG_CALLOC(1, sizeof(mem_reg_t));
        if(mem_mgr){
            error_status = -1;
            continue;
        }
    } while (0);

    /*Clean up if an error occurred during initialization*/
    if(error_status < 0){
        mem_reg_free(mem_mgr);
        mem_mgr = NULL;
    }

    return mem_mgr;
}
void mem_reg_free(mem_reg_t * mem_mgr)
{
    if(!mem_mgr) return;

    _free(mem_mgr);
}
