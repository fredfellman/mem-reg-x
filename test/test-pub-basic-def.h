#ifndef _TEST_PUB_BASIC_H
#define _TEST_PUB_BASIC_H

#define MEM_REGIONS_LINEAR_INC \
    MEM_REG(int, foo, 12)

struct baz { int a; };
#define MEM_REGIONS_BINEXP_INC \
    MEM_REG(struct baz, bar, 4)

#endif
