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
