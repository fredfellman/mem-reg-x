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
