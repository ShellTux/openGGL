CXX       = clang++
CXXFLAGS  = -Wall -Wextra
CXXFLAGS += -I$(shell realpath include)
CXXFLAGS += -I$(shell realpath ../../include)
CXXFLAGS += -L$(shell realpath ../..)

SOURCES = src/main.cpp

LD_FLAGS = -lGL -lGLU -lglfw -lOpenGGL -lOpenGGLApp

TARGET = bin/app

$(TARGET): $(SOURCES)
	mkdir --parents $(shell dirname $(TARGET))
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LD_FLAGS)

.clangd:
	rm --force $@

	@echo Diagnostics: | tee --append $@
	@echo '  UnusedIncludes: Strict' | tee --append $@
	@echo '  MissingIncludes: Strict' | tee --append $@
	@echo CompileFlags: | tee --append $@
	@echo '  Add:' | tee --append $@

	@for flag in $(CXXFLAGS) ; do echo "    - $$flag" | tee --append $@ ; done

.PHONY: run
run: $(TARGET)
	./$<
