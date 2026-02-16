TARGET := libps3mcframework.a
CXX := ppu-lv2-g++
AR := ppu-lv2-ar
CXXFLAGS := -O2 -std=gnu++11 -Wall -Wextra -I./include

SRC := \
    src/ModLoader.cpp \
    src/MemoryAPI.cpp \
    src/Syscalls.cpp \
    src/Filesystem.cpp

OBJ := $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(AR) rcs $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
