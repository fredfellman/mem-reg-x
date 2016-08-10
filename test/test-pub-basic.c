#include "test-pub-basic-def.h"
#include "test-common.h"
#include "mem-reg.h"

void test_basic(void)
{
    mem_reg_t * mem = NULL;
    mem = mem_reg_new();
    assert(mem);
    assert(mem_reg_foo_new(mem));
    mem_reg_free(mem);
    INFO("Basic allocation / freeing test successful");
}

void test_many_allocs(void)
{
#define NUM_ALLOCS 10000000
    unsigned int i;
    mem_reg_t * mem = NULL;

    mem = mem_reg_new();
    assert(mem);

    for(i=0; i<NUM_ALLOCS; i++){
        assert(mem_reg_bar_new(mem));
    }

    INFO("Successfully allocated %d structures", NUM_ALLOCS);

    mem_reg_free(mem);
}

int main(void)
{
    test_basic();
    test_many_allocs();
    return 0;
}
