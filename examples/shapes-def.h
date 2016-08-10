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
