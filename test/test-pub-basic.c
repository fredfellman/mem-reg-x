#include "test-common.h"

#define MEM_REGIONS_LINEAR_INC \
    MEM_REG(int, foo, 12)

struct baz { int a; };
#define MEM_REGIONS_BINEXP_INC \
    MEM_REG(struct baz, bar, 4)

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

int main(void)
{
    test_basic();
    return 0;
}
