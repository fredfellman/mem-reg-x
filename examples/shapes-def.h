#ifndef _SHAPES_DEF_H
#define _SHAPES_DEF_H

struct triangle {
    unsigned int a, b, c;
};

struct rectangle {
    unsigned int a, b;
};

struct circle {
    unsigned int radius;
};

#define MEM_REGIONS_LINEAR_INC \
    MEM_REG(struct triangle, triangle, 5) \
    MEM_REG(struct circle, circle, 20)

#define MEM_REGIONS_BINEXP_INC \
    MEM_REG(struct rectangle, rectangle, 100)

#endif
