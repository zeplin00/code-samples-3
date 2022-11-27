
# A simple makefile

TARGET=app

SRC := main.cpp

################################################################


CXX=g++

CC=gcc

# Used by the C/C++ Pre-Processor
#
CPPFLAGS=

# Used by the C Compiler
#
CFLAGS= 

# Used by the C+ Compiler
#
CXXFLAGS= -std=c++11

# Linker Flags
#
LDFLAGS=

################################################################

OBJ := $(SRC:.cpp=.o)

%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

%.o : %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(TARGET): $(OBJ)
	$(CXX) -o $(TARGET) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(TARGET) $(OBJ) $(TARGET).exe
