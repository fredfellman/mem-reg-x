.PHONY: all clean
HERE:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

include $(HERE)/../Makefile.common

all: test

TEST_TARGETS = test-priv-xfuncs

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

test-priv-%: test-priv-%.c
	$(CC) $(CFLAGS) $^ -o $(BUILDDIR)/$@

test-pub-%: test-pub-%.c
	$(CC) $(CFLAGS) $^ $(SRCFILES) -o $(BUILDDIR)/$@

clean:
	cd $(BUILDDIR) && rm $(TEST_TARGETS)
