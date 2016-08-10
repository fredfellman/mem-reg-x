.PHONY: all test examples clean

HERE:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

include $(HERE)/Makefile.common

all: $(BUILDDIR) test examples

test:
	make -C $(TESTDIR) test

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

examples:
	make -C $(EXAMPLEDIR)

clean:
	make -C $(TESTDIR) clean
	make -C $(EXAMPLEDIR) clean
