TARGETS := Common BeerProcessor SandwichProcessor Fabryka
.PHONY: $(TARGETS)

export MONO_PATH := $(MONO_PATH):$(PWD)/Common

all: $(TARGETS)

Fabryka: Common
	$(MAKE) -C $@

BeerProcessor: Common
	$(MAKE) -C $@

SandwichProcessor: Common
	$(MAKE) -C $@

Common:
	$(MAKE) -C $@


clean:
	find . -mindepth 2 -name Makefile -exec sh -c 'make -C "$${1%/*}" clean' -- {} \;
