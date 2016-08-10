# mem-reg-x
Simple and scalable memory region manager by way of X-Macros

## Why use a Region Memory Manager?
Managing dynamic data allocation in C is not always a trivial task.

A developer does not often have a great idea of how much data needs to
be allocated or when that data will be needed.

So why not just use `malloc`? Every call made to `malloc` must of course be freed.
If a user allocates 1,000,000 data structures, each at a different time, then either

- the user must keep references to all structures until they are all freed
(since they are in no way guaranteed to be contiguous), or

- the user must implement a referencing/ de-referencing scheme so that freed
data is no longer accessible.

Memory Regions alleviate these concerns by allocating data on-demand that
does not need to be freed until the region itself is freed.

## Why mem-reg-x?
Memory Regions are generic structures that, due to the statically-typed
nature of C, can be difficult to maintain as more data types are added.
`mem-reg-x` gets around this issue by generating the region functions at
compile-time using X-Macros. Once `mem-reg-x` is set-up within a project,
adding a region for a new data type is a single line of code.

## Dependencies
`mem-reg-x` does not have any dependencies if memory allocation functions
are provided by the user. Otherwise the only dependency is `stdlib` for
access to `malloc`, `calloc`, and `free`.

## Installation
Since most of the code is generated at compile-time, `mem-reg-x` should
be copied into the local project source directory.

```bash
git clone https://github.com/ryaxx/mem-reg-x
cp mem-reg-x/src/* /path/to/my/project
```

## License
See `LICENSE`

## Quick-Start

_See more examples in `examples/`_

Make a project

```bash
#Get project source
git clone https://github.com/ryaxx/mem-reg-x
mkdir triangle
#Copy the mem-reg-x source
cp mem-reg-x/src/* triangle
cd triangle
#Create the files we will need
touch triangle-defs.h triangle.c
```

The working directory (`triangle`) should now contain the files

- mem-reg.c
- mem-reg-def.h
- mem-reg.h
- triangle.c
- triangle-defs.h

First we create some definitions for our project.

```c
//triangle-defs.h
#ifndef _TRI_DEF_H
#define _TRI_DEF_H

struct triangle { int a, b, c; };

#define MEM_REGIONS_LINEAR_INC \
    MEM_REG(struct triangle, triangle, 10)

#endif
```
The pre-processor directive `MEM_REGIONS_LINEAR_INC` is expected by `mem-reg-x`
to contain a list of `MEM_REG` declarations. A `MEM_REG` declaration is in
the format `MEM_REG(<data type>, <reference name>, <initial size>)`.

We then create a main file to use the data structure.

```c
//triangle.c
#include <stdio.h>
#include "triangle-defs.h" //include before mem-reg.h
#include "mem-reg.h" //mem-reg-x header

int main(void)
{
    struct triangle * my_tri;
    mem_reg_t * mem; //Region manager handle
    int i;

    /*Instantiate region manager*/
    mem = mem_reg_new();

    /*Create some new triangles!*/
    for(i=1; i<5; i++){
        /*Get a new triangle reference*/
        my_tri = mem_reg_triangle_new(mem);
        /*Assign some values*/
        *my_tri = (struct triangle){
            .a = i*3,
            .b = i*4,
            .c = i*5
        };
        printf("New Triangle (@%p)\t", my_tri);
        printf("a=%-5d b=%-5d c=%-5d\n",
            my_tri->a, my_tri->b, my_tri->c);
    }

    /*Free all memory regions*/
    mem_reg_free(mem);

    return 0;
}
```

We must then of course compile the project. We might expect to compile using

```bash
gcc mem-reg.c triangle.c -o triangle
```

however doing so returns the error

```
...
triangle.c:(.text+0x25): undefined reference to `mem_reg_triangle_new'
...
```

The issue is that `mem-reg-x` is not aware of the memory region declarations
made in `triangle-defs.h`. We can tell `mem-reg-x` about this file by passing
the `MEM_REG_INCLUDE` directive through the compiler.

```bash
gcc -DMEM_REG_INCLUDE=triangle-defs.h mem-reg.c triangle.c -o triangle
```

Running `./triangle` now outputs
```
New Triangle (@0xe84060)	a=3     b=4     c=5
New Triangle (@0xe8406c)	a=6     b=8     c=10
New Triangle (@0xe84078)	a=9     b=12    c=15
New Triangle (@0xe84084)	a=12    b=16    c=20
```

Run `./triangle` through your favorite memory leak checker (valgrind, perhaps)
to see that no memory was leaked in this program.

##Make Targets
As mentioned above, `mem-reg-x` is built by including the source into your
local source project so there are no libraries to build.

Available make targets include
- `make test` (requires Valgrind)
- `make examples`
- `make clean`
- `make` (build and run tests and build examples)

##Preprocessor Arguments
There are several Preprocessor directives that can be overridden
in order to change the way that `mem-reg-x` behaves.

###MEM_REG
X Macro to declare a memory region.

It expects the form:
`MEM_REG(<type>, <name>, <init_size>)`
where
- `<type>` is the C type that the region should hold
- `<name>` is the interface name
(i.e. `<name>`=foo implies the reference `mem_reg_foo_new(reg_mem_t *)`)
- `<init_size>` is the size of the initial allocated region

###MEM_REGIONS_LINEAR_INC
A list of `MEM_REG` declarations.

Example:
```c
#define MEM_REGIONS_LINEAR_INC      \
    MEM_REG(int, foo, 12)           \
    MEM_REG(struct bar, baz, 20)    \
    MEM_REG(double *, qux, 138)
```

When a new region must be allocated, the total of all regions
is increased in linearly.

That is, the total regions with `<init_size>`=11 would increase
following
```
11, 22, 33, 44, ...
```

Defining regions in this way could result in better memory
utilization compared to `MEM_REGIONS_BINEXP_INC` but could also
result in more allocations and thus slower speeds.

###MEM_REGIONS_BINEXP_INC
A list of `MEM_REG` declarations.

Example:
```c
#define MEM_REGIONS_BINEXP_INC      \
    MEM_REG(int, foo, 12)           \
    MEM_REG(struct bar, baz, 20)    \
    MEM_REG(double *, qux, 138)
```

When a new region must be allocated, the total of all regions
is increased by binary exponentiation.

That is, the total regions with `<init_size>`=11 would increase
following
```
11, 33, 99, 297, ...
```

Defining regions in this way could be faster than
`MEM_REGIONS_LINEAR_INC` if you are expecting a lot of references to
be requested, however large chunks of memory could go unutilized

###MEM_REG_INCLUDE
Include a file before loading `mem-reg-x` definitions and
generating interface.

This directive should most likely be passed through the compiler.

Example
```bash
gcc -DMEM_REG_INCLUDE=my-local-defs.h file1.c file2.c ...
```

###MEM_REG_MALLOC
The `malloc`-compatible memory allocation call.
Default is `malloc` from `stdlib`.

###MEM_REG_CALLOC
The `calloc`-compatible memory allocation call.
Default is `calloc` from `stdlib`.
**NOTE**: Required even when `MEM_REG_NO_CALLOC` is set

###MEM_REG_FREE
The `free`-compatible memory allocation call.
Default is `free` from `stdlib`.

###MEM_REG_NO_CALLOC
By default `mem-reg-x` uses `calloc` to allocate all memory.
Set this directive to use `malloc` instead.

Be aware that, though regions are allocated with malloc under this
directive, internal structures (which are generally much smaller)
are still allocated with `calloc`.

###MEM_REG_NEW_FUNC(name)
Override the default function name to receive a new pointer to an element.

Default is `mem_reg_<name>_new`.

Example:
Consider the following user definitions.

```c
#define MEM_REGIONS_LINEAR_INC      \
    MEM_REG(struct bar, baz, 20)
```
The function `struct bar * mem_reg_baz_new(mem_reg_t *)` will be generated.
After appending
```c
#define MEM_REG_NEW_FUNC(name) create_a_new_ ## name
```
The function `struct bar * create_a_new_baz(mem_reg_t *)` will
instead be generated (though functionality will stay the same).
