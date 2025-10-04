CXX = g++
CXXFLAGS = -std=c++17 -Wall -I./
SOURCES = $(wildcard *.cpp)
TARGETS = $(SOURCES:.cpp=)
BUILDDIR = build
BUILD_TARGETS = $(addprefix $(BUILDDIR)/, $(TARGETS))

all: $(BUILDDIR) $(BUILD_TARGETS)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/%: %.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -o $@ $<

# Alias para permitir make q1 compilar build/q1 corretamente
$(TARGETS): %: $(BUILDDIR)/%
	@true

clean:
	rm -rf $(BUILDDIR)