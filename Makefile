CXX       = clang++
CXXFLAGS  = -Wall -Wextra -Werror -std=c++17
CXXFLAGS += -Wno-error=unused-parameter
CXXFLAGS += -Wno-error=unused-variable
CXXFLAGS += -Wno-error=unused-but-set-variable
CXXFLAGS += -I$(shell realpath include)

LDFLAGS = -lGL -lGLU -lgtest -lgtest_main -pthread

OPENGGL_SRC = \
      src/openGGL/2D/geometric-figures.cpp \
      src/openGGL/2D/geometric-figures-unit.cpp \
      src/openGGL/3D/geometric-figures.cpp \
      src/openGGL/3D/geometric-figures-unit.cpp \
      src/openGGL/3D/Vector/core.cpp
OPENGGL_OBJ = $(OPENGGL_SRC:.cpp=.o)

OPENGGLAPP_SRC = \
		 src/openGGL/App/core.cpp
OPENGGLAPP_OBJ = $(OPENGGLAPP_SRC:.cpp=.o)


TEST = bin/test
TEST_SRC = \
	   src/openGGL/3D/Vector/core.cpp \
	   tests/openGGL/3D/Vector/core.cpp
TEST_OBJ := $(TEST_SRC:.cpp=.o)

all: libOpenGGL.a libOpenGGLApp.a

libOpenGGL.a: $(OPENGGL_OBJ)
	ar rcs $@ $^

libOpenGGLApp.a: $(OPENGGLAPP_OBJ)
	ar rcs $@ $^

$(TEST): $(TEST_OBJ)
	mkdir --parents $(shell dirname "$@")
	$(CXX) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	find . -type f -iname "*.o" -exec rm "{}" \;

.PHONY: test
test: $(TEST)
	./$^

.PHONY: cov
cov: CXX       = g++
cov: CXXFLAGS += -fprofile-arcs -ftest-coverage
cov: LDFLAGS  += -lgcov --coverage
cov: clean test
	mkdir --parents cov
	gcovr --timestamp "$(shell date +"%Y-%m-%d %H:%M:%S")"

.PHONY: cov-web
cov-web: cov
	python -m http.server --bind 127.0.0.1 --directory ./cov 8080

.PHONY: .clangd
.clangd:
	rm --force $@

	@echo Diagnostics: | tee --append $@
	@echo '  UnusedIncludes: Strict' | tee --append $@
	@echo '  MissingIncludes: Strict' | tee --append $@
	@echo CompileFlags: | tee --append $@
	@echo '  Add:' | tee --append $@

	@for flag in $(CXXFLAGS) ; do echo "    - $$flag" | tee --append $@ ; done
