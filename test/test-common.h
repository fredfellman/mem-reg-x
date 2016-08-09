#ifndef _TEST_COMMON_H
#define _TEST_COMMON_H

#include <assert.h>
#include <stdio.h>

#define DBG(fmt, ...) printf("DEBUG   : %-20s "fmt"\n", __PRETTY_FUNCTION__, ##__VA_ARGS__)
#define INFO(fmt, ...) printf("INFO    : %-20s "fmt"\n", __PRETTY_FUNCTION__, ##__VA_ARGS__)
#define WARN(fmt, ...) printf("WARNING : %-20s "fmt"\n", __PRETTY_FUNCTION__, ##__VA_ARGS__)
#define ERR(fmt, ...) fprintf(stderr, "WARNING : %-20s "fmt"\n", __PRETTY_FUNCTION__, ##__VA_ARGS__)

#endif
