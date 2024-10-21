CXX       = clang++
CXXFLAGS  = -Wall -Wextra -std=c++17
CXXFLAGS += -I$(shell realpath include)

SOURCES = src/main.cpp src/events.cpp

LD_FLAGS = -lGL -lGLU -lglfw -lOpenGGL -lOpenGGLApp

TARGET = bin/template

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
