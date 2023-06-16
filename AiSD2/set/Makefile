SRCDIR   := src
BUILD    := build
OBJDIR   := $(BUILD)/obj
BINDIR   := $(BUILD)/bin
DEPSDIR  := $(BUILD)/deps

CXXFLAGS := -std=c++17 -O2 -march=native

ASAN_FLAGS := -fsanitize=address,undefined,leak,signed-integer-overflow
ASAN_FLAGS += -fno-omit-frame-pointer

LDFLAGS := -s
LDLIBS  :=

SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

.PHONY: build clean debug compile_commands.json

build: $(BINDIR)/test

clean:
	$(RM) -r build/

debug: CXXFLAGS += -g3 -Og
debug: CXXFLAGS += -Wall -Wextra -pedantic
debug: CXXFLAGS += -DDEBUG=1
debug: CXXFLAGS += $(ASAN_FLAGS)
debug: CXXFLAGS += -fno-omit-frame-pointer
debug: LDFLAGS :=
debug: LDFLAGS += $(ASAN_FLAGS)
debug: LDFLAGS += -fno-omit-frame-pointer
debug: compile_commands.json build


-include $(patsubst $(OBJDIR)/%.o, $(DEPSDIR)/%.d, $(OBJS))

$(BINDIR)/%: $(OBJS)
	@mkdir -p $(BINDIR)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<

$(DEPSDIR)/%.d: $(SRCDIR)/%.cpp
	@mkdir -p $(DEPSDIR)
	$(CXX) $(CPPFLAGS) -M $< -MT $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $<) > $@


$(wildcard $(SRCDIR)/*.ipp):
	$(CXX) -include $(@:%.ipp=%.hpp) -x c++-header $@

compile_commands.json:
	@ $(MAKE) --always-make --dry-run build $(SRCDIR)/*.ipp \
		| grep -wE -e '$(CC)' -e '$(CXX)' \
		| grep -w -e '\-c' -e '\-x' \
		| jq -nR '[inputs|{directory:"'$$PWD'", command:., file: match(" [^ ]+$$").string[1:]}]' \
		> compile_commands.json
