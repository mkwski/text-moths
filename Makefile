.PHONY: all clean

CXX := clang++
CXX_FLAGS := -std=c++23 -O2 \
	-Wall -Wextra \
	-Wno-experimental-header-units \
	-Wno-pragma-system-header-outside-header \

PCH_HEADERS := iostream regex string
PCH_FILES := $(addsuffix .pch,$(PCH_HEADERS))
PCH_FLAGS := $(addprefix -fmodule-file=,$(PCH_FILES))

MODULES := parser
PCM_FILES := $(addsuffix .pcm,$(MODULES))
MOD_OBJ_FILES := $(addsuffix .o,$(MODULES))

all: text_moths

text_moths: $(MOD_OBJ_FILES) main.o
	$(CXX) $(CXX_FLAGS) $(MOD_OBJ_FILES) main.o -o $@

%.pch:
	$(CXX) $(CXX_FLAGS) \
		-xc++-system-header \
		--precompile $* \
		-o $@

parser.pcm: parser.cppm $(PCH_FILES)
	$(CXX) $(CXX_FLAGS) \
		-fprebuilt-module-path=. \
		--precompile $(PCH_FLAGS) \
		$< -o $@

%.o: %.pcm
	$(CXX) $(CXX_FLAGS) \
		-fprebuilt-module-path=. \
		-c $< -o $@

main.o: main.cpp parser.pcm $(PCH_FILES)
	$(CXX) $(CXX_FLAGS) \
		-fprebuilt-module-path=. \
		$(PCH_FLAGS) \
		-c $< -o $@

clean:
	rm -f text_moths *.o *.pcm *.pch

