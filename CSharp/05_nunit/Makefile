BUILDDIR := Build
OBJDIR   := $(BUILDDIR)/Obj
LIBDIR   := $(BUILDDIR)/Lib
BINDIR   := $(BUILDDIR)/Bin
SRCDIR   := $(CURDIR)/Src
LIB3DIR  := $(CURDIR)/Lib3

TESTDIRSRC  := $(CURDIR)/Tests
TESTDIROUT  := $(LIBDIR)/Tests

TDS := $(TESTDIRSRC)
TDO := $(TESTDIROUT)

CSC = mcs

TESTS := Concat ConcatEx Anagram
TESTS += DiscountPesel
# TESTS += DiscountPesel_example
TESTS := $(patsubst %, $(TDO)/%.dll, $(TESTS))

NUNIT = $(LIB3DIR)/NUnit
NUNIT_LIB_DIR = $(lastword $(wildcard $(NUNIT).*/lib/net??))
NUNIT_RUN_TOOLS = $(wildcard $(NUNIT).ConsoleRunner.*/tools)
NUNIT_FW_DLL = $(NUNIT_LIB_DIR)/nunit.framework.dll

export MONO_PATH = $(NUNIT_RUN_TOOLS):$(NUNIT_LIB_DIR)

ifeq ($(MONO_PATH), :)
	GUARD := @exit;
endif


all: $(TESTS)

$(TDO)/%.dll: $(NUNIT).* $(TDS)/%.cs
	@mkdir -p $(TDO)
	$(GUARD) $(CSC) -target:library -r:$(NUNIT_FW_DLL) -out:$@ \
		$(filter-out $(wildcard $(NUNIT).*), $^)

$(TDO)/Concat.dll: $(TDS)/Concat.cs \
	$(SRCDIR)/Concatenator.cs

$(TDO)/ConcatEx.dll: $(TDS)/ConcatEx.cs \
	$(SRCDIR)/Concatenator.cs

$(TDO)/Anagram.dll: $(TDS)/Anagram.cs \
	$(SRCDIR)/AnagramChecker.cs $(SRCDIR)/IAnagramChecker.cs

$(TDO)/DiscountPesel.dll: $(TDS)/DiscountPesel.cs \
	$(SRCDIR)/DiscountFromPeselComputer.cs $(SRCDIR)/IDiscountFromPeselComputer.cs

$(TDO)/DiscountPesel_example.dll: $(TDS)/DiscountPesel_example.cs \
	$(SRCDIR)/DiscountFromPeselComputer_example.cs


$(NUNIT).*:
	nuget install -OutputDirectory $(LIB3DIR) NUnit
	nuget install -OutputDirectory $(LIB3DIR) NUnit.ConsoleRunner -Version 3.12.0
	$(MAKE) --no-print-directory $(filter-out clear, $(MAKECMDGOALS))


.PHONY: test
test: $(TESTS)
	@ $(GUARD) mono $(NUNIT_RUN_TOOLS)/nunit*-console.exe $^ -noresult


.PHONY: clear clear-full

clear:
	$(RM) -r $(BUILDDIR)

clear-full: clear
	$(RM) -r $(LIB3DIR)
