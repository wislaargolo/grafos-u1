CXX = g++
CXXFLAGS = -std=c++17 -Wall -I./
ROOT_SOURCES := $(wildcard *.cpp)
TEST_SOURCES := $(wildcard tests/*.cpp)

SOURCES := $(ROOT_SOURCES) $(TEST_SOURCES)

# targets for root .cpp files (e.g. q1.cpp -> build/q1)
ROOT_TARGETS := $(ROOT_SOURCES:.cpp=)

# targets for tests .cpp files (e.g. tests/q1.cpp -> build/tests/q1)
TEST_TARGETS := $(patsubst tests/%.cpp,tests/%, $(TEST_SOURCES))

BUILDDIR = build
BUILD_ROOT_TARGETS := $(addprefix $(BUILDDIR)/, $(ROOT_TARGETS))
BUILD_TEST_TARGETS := $(addprefix $(BUILDDIR)/, $(TEST_TARGETS))
BUILD_TARGETS := $(BUILD_ROOT_TARGETS) $(BUILD_TEST_TARGETS)

all: $(BUILDDIR) $(BUILDDIR)/tests $(BUILD_TARGETS)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/%: %.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -o $@ $<

# Regra para compilar arquivos dentro de tests/ para build/tests/
$(BUILDDIR)/tests/%: tests/%.cpp | $(BUILDDIR) $(BUILDDIR)/tests
	$(CXX) $(CXXFLAGS) -o $@ $<

$(BUILDDIR)/tests:
	mkdir -p $(BUILDDIR)/tests

# Alias para permitir make q1 compilar build/q1 corretamente
$(ROOT_TARGETS): %: $(BUILDDIR)/%
	@true

# Alias para permitir make tests/q1 compilar build/tests/q1 corretamente
$(TEST_TARGETS): tests/%: $(BUILDDIR)/tests/%
	@true

clean:
	rm -rf $(BUILDDIR)