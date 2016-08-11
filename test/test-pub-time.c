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
#include <time.h>
#include <string.h>
#include "test-pub-time-def.h"
#include "test-common.h"
#include "mem-reg.h"

#define NUM_ITERATIONS 1000

#define GET_TIME(time) assert(clock_gettime(CLOCK_REALTIME, time) == 0)

#define LOG_TIME(method, begin, end) \
    INFO( \
        "Method - %-15s Total Time (ns) - %-15ld Iterations - %d", \
        method, ((long)end.tv_nsec - (long)begin.tv_nsec), NUM_ITERATIONS \
    )

void verify_distinct_buffer(int ** buff, unsigned long size)
{
    int j, k;
    for(j=0; j<size; j++){
        assert(buff[j]);
        for(k=0; k<size; k++){
            if(!(j==k || buff[j]!=buff[k]))
                INFO("j %d k %d @%p", j, k, buff[j]);
            assert(j==k || buff[j]!=buff[k]);
        }
    }
}

void test_malloc_time(int ** buff)
{
    struct timespec start, end;
    unsigned long i;

    GET_TIME(&start);
    for(i=0; i<NUM_ITERATIONS; i++){
        buff[i] = malloc(sizeof(int));
    }
    GET_TIME(&end);

    verify_distinct_buffer(buff, NUM_ITERATIONS);

    for(i=0; i<NUM_ITERATIONS; i++){
        free(buff[i]);
    }

    LOG_TIME("malloc", start, end);

}

void test_calloc_time(int ** buff)
{
    struct timespec start, end;
    unsigned long i;

    GET_TIME(&start);
    for(i=0; i<NUM_ITERATIONS; i++){
        buff[i] = calloc(1, sizeof(int));
    }
    GET_TIME(&end);

    verify_distinct_buffer(buff, NUM_ITERATIONS);

    for(i=0; i<NUM_ITERATIONS; i++){
        free(buff[i]);
    }

    LOG_TIME("calloc", start, end);

}

void test_lin_time(int ** buff)
{
    struct timespec start, end;
    unsigned long i;
    mem_reg_t * mem;

    mem = mem_reg_new();
    GET_TIME(&start);
    for(i=0; i<NUM_ITERATIONS; i++){
        buff[i] = mem_reg_int_type_lin_new(mem);
    }
    GET_TIME(&end);

    verify_distinct_buffer(buff, NUM_ITERATIONS);

    mem_reg_free(mem);

    LOG_TIME("Linear Regions", start, end);

}

void test_bin_time(int ** buff)
{
    struct timespec start, end;
    unsigned long i;
    mem_reg_t * mem;

    mem = mem_reg_new();
    GET_TIME(&start);
    for(i=0; i<NUM_ITERATIONS; i++){
        buff[i] = mem_reg_int_type_bin_new(mem);
    }
    GET_TIME(&end);

    verify_distinct_buffer(buff, NUM_ITERATIONS);

    mem_reg_free(mem);

    LOG_TIME("Binary Regions", start, end);

}

int main(void)
{
    int * buff[NUM_ITERATIONS];
    /*Make first malloc call for fairness*/
    void * tmp;
    tmp = malloc(100);
    free(tmp);

    /*Run tests*/
    test_malloc_time(buff);
    test_calloc_time(buff);
    test_lin_time(buff);
    test_bin_time(buff);
    return 0;
}
