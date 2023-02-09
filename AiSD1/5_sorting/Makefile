# --- INIT --------------------------------------------------------------- {{{1
# dirs {{{2

BUILDDIR := build
OBJDIR   := $(BUILDDIR)/obj
BINDIR   := $(BUILDDIR)/bin
SRCDIR   := $(CURDIR)

# flags  {{{2

CXXFLAGS :=
CXXFLAGS := $(CXXFLAGS) -std=c++17 -O2 -march=native
CXXFLAGS := $(CXXFLAGS) -Wall -Wextra -Wconversion -pedantic

LDFLAGS := -s
LDLIBS  :=

# functions {{{2

define objectify
	$(patsubst %, $(OBJDIR)/%.o, $(1))
endef

# --- RULES -------------------------------------------------------------- {{{1

%.x: $(OBJDIR)/%.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.pdf: %.latex
	@mkdir -p $(OBJDIR)
	xelatex -output-directory=$(OBJDIR) -interaction=nonstopmode $^
	mv $(OBJDIR)/$@ .

$(BINDIR)/%.x: $(OBJDIR)/%.c
	@mkdir -p $(BINDIR)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

# --- TARGETS ------------------------------------------------------------ {{{1

.PHONY: build
SORTS := BubbleSort SelectionSort InsertionSort CountingSort SelectionMinmax
TARGETS := $(addsuffix .x, Generator $(SORTS))
build: $(TARGETS)

Generator.x: $(call objectify, Generator)
BubbleSort.x: $(call objectify, BubbleSort)
SelectionSort.x: $(call objectify, SelectionSort)
InsertionSort.x: $(call objectify, InsertionSort)
CountingSort.x: $(call objectify, CountingSort)
SelectionMinmax.x: $(call objectify, SelectionMinmax)

complexity_InsertionSort.pdf: complexity_InsertionSort.latex

data: build
	@ mkdir -p data
	@ sh gather_data.sh "$(SORTS)"

graph.pdf: data graph.latex

# --- CLEANUP ------------------------------------------------------------ {{{1

RMDIR = rmdir --parents --ignore-fail-on-non-empty

.PHONY: clean
clean:
	$(RM) compile_commands.json
	$(RM) $(TARGETS)
	$(RM) -r build/
	$(RM) complexity_InsertionSort.pdf graph.pdf
	$(RM) -r data/

# --- DEBUG -------------------------------------------------------------- {{{1

SANITIZERS := -fsanitize=address,undefined,leak,signed-integer-overflow

.PHONY: debug
debug: CXXFLAGS := $(CXXFLAGS) -g3 -O0
debug: CXXFLAGS := $(CXXFLAGS) -DDEBUG=1
debug: CXXFLAGS := $(CXXFLAGS) $(SANITIZERS)
debug: CXXFLAGS := $(CXXFLAGS) -fno-omit-frame-pointer
debug: LDFLAGS :=
debug: LDFLAGS := $(LDFLAGS) $(SANITIZERS)
debug: LDFLAGS := $(LDFLAGS) -fno-omit-frame-pointer
debug: compile_commands.json build

# --- COMPILE_COMMANDS.JSON ---------------------------------------------- {{{1

TMPL_IMPLS := $(patsubst %, %.del.cpp, $(wildcard $(SRCDIR)/*.ipp))

.PHONY: $(TMPL_IMPLS) _compile_commands_targets compile_commands.json

_compile_commands_targets: $(TARGETS) $(TMPL_IMPLS)

$(TMPL_IMPLS):
	$(CXX) -include $(@:%.ipp.del.cpp=%.hpp) -x c++-header $@

compile_commands.json:
	@ > $@
	@ compiledb -n $(MAKE) _compile_commands_targets
	@ $(RM) *.ipp.del.cpp
	@ sed -i 's/.ipp.del.cpp/.ipp/' $@
