#include <string.h> //Memset
#include "test-common.h"

#define MEM_REGIONS_LINEAR_INC \
    MEM_REG(int, foo, 12)

#define foo_init_func(size) _M_NODE_INIT_FUNC(foo)(size)
#define foo_free_func(f) _M_NODE_FREE_FUNC(foo)(f)
#define foo_struct _M_NODE_STRUCT(foo)
#define foo_get_next_elem(f) _M_NODE_GET_ELEM_FUNC(foo)(&f)
#define foo_head(mem) mem._M_NODE_NAME(foo).head
#define foo_index(mem) mem._M_NODE_NAME(foo).index

#include "mem-reg.c"

void test_init_free_func(void)
{
    foo_struct * foo_var = NULL;
    INFO("Testing Private X-Macro Initialization Functions");

    foo_var = foo_init_func(7);
    assert(foo_var);
    INFO("Allocation successful");

    assert(_REGION_SIZE(foo_var) == 7);
    INFO("Allocation was of correct size");

    foo_free_func(foo_var);
    INFO("Region node freed");
}

void test_get_elems(void)
{
    int i, k, * new_elem[6];
    foo_struct * foos;
    mem_reg_t mem_mgr;
    memset(&mem_mgr, 0, sizeof(mem_reg_t));

    foo_head(mem_mgr) = foo_init_func(5);
    foo_index(mem_mgr) = foo_head(mem_mgr);

    assert(foo_head(mem_mgr)==foo_index(mem_mgr));

    /*Request more elements than Initialized in region*/
    for(i=0; i<6; i++){
        new_elem[i] = foo_get_next_elem(mem_mgr);

        /*The head and index should only be equal in the first region*/
        if(i<4)
            assert(foo_head(mem_mgr)==foo_index(mem_mgr));
        else
            assert(foo_head(mem_mgr)!=foo_index(mem_mgr));
    }
    INFO("New region correctly instantiated");

    /*Check that each pointer is unique*/
    for(i=0; i<6; i++){
        for(k=0; k<6; k++){
            assert(i==k ||new_elem[i] != new_elem[k]);
        }
    }
    INFO("Each new allocated pointer is distinct");

    /*Make sure that total region size incremented linearly*/
    assert(_REGION_SIZE(foo_index(mem_mgr))==5);
    INFO("Total region size increased linearly");

    /*Make sure that we only have two regions*/
    i = 0;
    foos = foo_head(mem_mgr);
    while(foos){
        i++;
        foos = foos->next;
    }
    assert(i == 2);

    /*Clean Up*/
    foo_free_func(foo_head(mem_mgr));
    foo_free_func(foo_index(mem_mgr));
}

int main(void)
{
    INFO("Beginning basic initialization tests");
    test_init_free_func();
    test_get_elems();
    return 0;
}
