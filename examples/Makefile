.PHONY: all clean
HERE:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

include $(HERE)/../Makefile.common

CFLAGS += -I$(HERE)

all: examples

EXAMPLE_TARGETS = shapes

examples: $(EXAMPLE_TARGETS)

clean:
	rm -f $(EXAMPLE_TARGETS)

%: %.c %-def.h
	$(CC) $(CFLAGS) $(SRCFILES) -DMEM_REG_INCLUDE=$@-def.h $< -o $@

