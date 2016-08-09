.PHONY: all test clean

HERE:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

include $(HERE)/Makefile.common

all: test

test:
	make -C $(TESTDIR) test

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	make -C $(TESTDIR) clean
