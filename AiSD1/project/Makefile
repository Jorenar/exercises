# --- INIT --------------------------------------------------------------- {{{1
# dirs {{{2

BUILDDIR := build
OBJDIR   := $(BUILDDIR)/obj
BINDIR   := $(BUILDDIR)/bin
SRCDIR   := $(CURDIR)/src

# flags  {{{2

CXXFLAGS :=
CXXFLAGS := $(CXXFLAGS) -std=c++17 -O2
CXXFLAGS := $(CXXFLAGS) -Wall -Wextra -Wconversion -pedantic

LDFLAGS := -s
LDLIBS  :=

# --- RULES -------------------------------------------------------------- {{{1

$(BINDIR)/%: $(OBJDIR)/%.c
	@mkdir -p $(BINDIR)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

# --- TARGET ------------------------------------------------------------- {{{1

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
TARGETS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

.PHONY: build
build: $(BINDIR)/lzw

$(BINDIR)/lzw: $(TARGETS)
	@mkdir -p $(BINDIR)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# --- CLEANUP ------------------------------------------------------------ {{{1

.PHONY: clean
clean:
	$(RM) -r build/

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

TMPL_IMPLS := $(patsubst %, $(BUILD)/%.del.cpp, $(wildcard $(SRCDIR)/*.ipp))

.PHONY: $(TMPL_IMPLS) _compile_commands_targets compile_commands.json

_compile_commands_targets: $(TARGETS) $(TMPL_IMPLS)

# $(TMPL_IMPLS):
# 	$(CXX) -include $(@:%.ipp.del.cpp=%.hpp) -x c++-header $@

compile_commands.json:
	@ # > $@
	@ # touch $(TMPL_IMPLS)
	@ compiledb -n $(MAKE) _compile_commands_targets
	@ # $(RM) $(TMPL_IMPLS)
	@ # sed -i 's/.ipp.del.cpp/.ipp/' $@
