CXX       = clang++
CXXFLAGS  = -Wall -Wextra -std=c++17
CXXFLAGS += -I$(shell realpath include)

SRC = src/openGGL/2D/geometric-figures-unit.cpp src/openGGL/2D/geometric-figures.cpp
OBJ = $(SRC:.cpp=.o)

all: libOpenGGL.a

libOpenGGL.a: $(OBJ)
	ar rcs $@ $^

.PHONY: clean
clean:
	rm -f *.o *.a libOpenGGL.a

.PHONY: .clangd
.clangd:
	rm --force $@

	@echo Diagnostics: | tee --append $@
	@echo '  UnusedIncludes: Strict' | tee --append $@
	@echo '  MissingIncludes: Strict' | tee --append $@
	@echo CompileFlags: | tee --append $@
	@echo '  Add:' | tee --append $@

	@for flag in $(CXXFLAGS) ; do echo "    - $$flag" | tee --append $@ ; done
