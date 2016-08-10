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

int main(void)
{
    test_basic();
    return 0;
}
