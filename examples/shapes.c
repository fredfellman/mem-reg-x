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
#include <stdio.h>

#include "shapes-def.h"
#include "mem-reg.h"

void usage(char * name)
{
    fprintf(
        stderr,
        "Usage:\n"                                              \
        "\t%s <num_triangles> <num_circles> <num_rectangles>\n",
        name
    );
    exit(1);
}


int main(int argc, char ** argv)
{
    int num_triangles, num_rectangles, num_circles, i;

    /*From shapes-def.h*/
    struct triangle * new_triangle;
    struct rectangle * new_rectangle;
    struct circle * new_circle;

    /*Memory manager*/
    mem_reg_t * mem;

    /*Check user input*/
    if(argc != 4)
        usage(argv[0]);

    num_triangles = atoi(argv[1]);
    num_circles = atoi(argv[2]);
    num_rectangles = atoi(argv[3]);

    /*Initialize Memory Region Manager*/
    mem = mem_reg_new();
    if(!mem){
        fprintf(stderr, "Could not allocate region manager");
        exit(1);
    }

    /*Create triangles*/
    for(i=0; i<num_triangles; i++){
        new_triangle = mem_reg_triangle_new(mem);

        /*Make a 3-4-5 right triangle*/
        *new_triangle = (struct triangle){
            .a = i*3,
            .b = i*4,
            .c = i*5
        };
    }
    printf("Created %d 3-4-5 triangles\n", num_triangles);

    /*Create circles*/
    for(i=0; i<num_circles; i++){
        new_circle = mem_reg_circle_new(mem);

        /*Assign the radius*/
        new_circle->radius = i;
    }
    printf("Created %d circles\n", num_circles);

    /*Create rectangles*/
    for(i=0; i<num_rectangles; i++){
        new_rectangle = mem_reg_rectangle_new(mem);

        *new_rectangle = (struct rectangle){
            .a = i,
            .b = i*2
        };
    }
    printf("Created %d rectangles\n", num_rectangles);

    /*Free allocated regions*/
    mem_reg_free(mem);
    return 0;
}
