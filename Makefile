# Makefile - Final Version
CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = finalgame

SRCS = ui.cpp \
       level1.cpp \
       level2.cpp \
       level3.cpp \
       level4.cpp \
       level5.cpp \
       level6.cpp \
       level7.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)