#ifndef _MEM_REG_H
#define _MEM_REG_H

typedef struct _mem_reg mem_reg_t;

mem_reg_t * mem_reg_new(void);
void mem_reg_free(mem_reg_t *);

#endif
