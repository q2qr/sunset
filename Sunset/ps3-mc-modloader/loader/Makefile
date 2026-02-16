TARGET := ps3-mc-modloader-loader.prx
CXX := ppu-lv2-g++
CXXFLAGS := -O2 -std=gnu++11 -Wall -Wextra \
    -I./include -I../framework/include
LDFLAGS := -shared -L../framework -lps3mcframework -lpsutil

SRC := \
    src/main.cpp \
    src/EBOOTHook.cpp \
    src/TickHook.cpp

OBJ := $(SRC:.cpp=.o)

all: framework $(TARGET)

framework:
	$(MAKE) -C ../framework

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(MAKE) -C ../framework clean
	rm -f $(OBJ) $(TARGET)
