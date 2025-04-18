CXX = g++
COMMONOTIC = -I./include

Target = akinator

.Phony: clean

clean:
	rm -f $(CPPOBJ) $(TARGET)
# релизная сборка по деффолту
DEBUG ?= 0

# для откладки make DEBUG=1
DEBUG_FLAGS = -g -O0 -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SID
# для релиза make DEBUG=0
RELEASE_FLAGS = -O2 -DNDEBUG

ifeq ($(DEBUG),1)
    CXXFLAGS = $(DEBUG_FLAGS)
else
    CXXFLAGS = $(RELEASE_FLAGS)
endif


CPPSRC = ./main.cpp ./tree_func.cpp ./graph_dump.cpp ./akinator_functions.cpp ./stack_functions.cpp

CPPOBJ = main.o tree_func.o graph_dump.o akinator_functions.o stack_functions.o

$(CPPOBJ): %.o: ./%.cpp
	$(CXX) $(CXXFLAGS) -MP -MMD -c $< -o $@

$(Target): $(CPPOBJ)
	$(CXX) $^ -o $@ $(LDFLAGS)
