#include <string.h> //Memset
#include "test-common.h"

#define MEM_REGIONS_LINEAR_INC \
    MEM_REG(int, foo, 12)

struct baz { int a; };
#define MEM_REGIONS_BINEXP_INC \
    MEM_REG(struct baz, bar, 4)

#define foo_init_func(size) _M_NODE_INIT_FUNC(foo)(size)
#define foo_free_func(f) _M_NODE_FREE_FUNC(foo)(f)
#define foo_struct _M_NODE_STRUCT(foo)
#define foo_get_next_elem(f) _M_NODE_GET_ELEM_FUNC(foo)(&f)
#define foo_head(mem) mem._M_NODE_NAME(foo).head
#define foo_index(mem) mem._M_NODE_NAME(foo).index
#define foo_next_region_size(foos) \
    _M_NODE_NEXT_REG_SIZE_FUNC(foo)(foos)

#define bar_init_func(size) _M_NODE_INIT_FUNC(bar)(size)
#define bar_free_func(f) _M_NODE_FREE_FUNC(bar)(f)
#define bar_struct _M_NODE_STRUCT(bar)
#define bar_get_next_elem(f) _M_NODE_GET_ELEM_FUNC(bar)(&f)
#define bar_head(mem) mem._M_NODE_NAME(bar).head
#define bar_index(mem) mem._M_NODE_NAME(bar).index
#define bar_next_region_size(bars) \
    _M_NODE_NEXT_REG_SIZE_FUNC(bar)(bars)

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

void test_inc_functions(void)
{
    foo_struct * foos;
    bar_struct * bars;

    foos = foo_init_func(105);
    assert(foos);

    bars = bar_init_func(67);
    assert(bars);

    /*Linearly incrementing function should stay the same*/
    assert(foo_next_region_size(foos) == 105);
    INFO("Linear incrementing region size successful");

    /*Binary exp incrementing function should double*/
    assert(bar_next_region_size(bars) == 67*2);
    INFO("Binary exponential incrementing region size successful");

    /*Clean up*/
    foo_free_func(foos);
    bar_free_func(bars);
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

void test_mem_public_mem_init(void)
{
    mem_reg_t * mem = NULL;

    INFO("Testing that public allocation was correct");

    mem = mem_reg_new();
    assert(mem);
    INFO("Allocation successful");

    /*Check that both types of regions were allocated*/
    assert(mem->_M_NODE_NAME(foo).head);
    assert(mem->_M_NODE_NAME(bar).head);

    /*Check that indices are in the right place*/
    assert(mem->_M_NODE_NAME(foo).head ==
            mem->_M_NODE_NAME(foo).index);
    assert(mem->_M_NODE_NAME(bar).head ==
            mem->_M_NODE_NAME(bar).index);

    mem_reg_free(mem);
}

int main(void)
{
    INFO("Beginning basic initialization tests");
    test_init_free_func();
    test_inc_functions();
    test_get_elems();
    test_mem_public_mem_init();
    return 0;
}
