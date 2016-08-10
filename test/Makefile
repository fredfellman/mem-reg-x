.PHONY: all clean
HERE:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

include $(HERE)/../Makefile.common

CFLAGS += -I$(HERE)

all: test

TEST_TARGETS = test-priv-xfuncs test-pub-basic

test: test-unit test-mem

test-unit: $(TEST_TARGETS)
	@cd $(BUILDDIR) && for t in $^; do $(BUILDDIR)/$$t || exit 1; done
	@echo "\t***********************************"
	@echo "\t*      Unit Tests Successful      *"
	@echo "\t***********************************"

test-mem: $(TEST_TARGETS)
	@cd $(BUILDDIR) && for t in $^; do $(VALGRIND) $(BUILDDIR)/$$t || exit 1; done
	@echo "\t***********************************"
	@echo "\t*     Memory Tests Successful     *"
	@echo "\t***********************************"

test-priv-%: test-priv-%.c test-priv-%-def.h
	$(CC) $(CFLAGS) -DMEM_REG_INCLUDE="$@-def.h" $< -o $(BUILDDIR)/$@

test-pub-%: test-pub-%.c test-pub-%-def.h
	$(CC) $(CFLAGS) $(SRCFILES) -DMEM_REG_INCLUDE="$@-def.h" $< -o $(BUILDDIR)/$@

clean:
	cd $(BUILDDIR) && rm -f $(TEST_TARGETS)
