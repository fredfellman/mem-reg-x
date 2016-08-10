# mem-reg-x - Memory Region Manager
# Copyright © 2016 Ryan Jones <ryan@rjones.io>

# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
# DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
# OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

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
