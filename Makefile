CXX = g++

DEBUG ?= 0

DEBUG_FLAGS = -g -O0 -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

RELEASE_FLAGS = -O2 -DNDEBUG

ifeq ($(DEBUG),1)
    CXXFLAGS = $(DEBUG_FLAGS)
else
    CXXFLAGS = $(RELEASE_FLAGS)
endif

COMMONIC = -I./include

BUILD_DIR = build

EXECUTABLE = do

SOURCES = src/main.cpp src/tree_func.cpp src/stack_functions.cpp src/akinator_functions.cpp src/graph_dump.cpp

OBJECTS = $(addprefix $(BUILD_DIR)/, $(SOURCES:%.cpp=%.o))
DEPENDS = $(OBJECTS:.o=.d)

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@$(CXX) $(CXXFLAGS) $(COMMONIC) $^ -o $@
	@echo -e "\033[33m Build complete: $@ \033[0m"

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) $(COMMONIC) -MP -MMD -c $< -o $@

clean:
	@rm -rf $(BUILD_DIR) $(EXECUTABLE)

-include $(DEPENDS)
