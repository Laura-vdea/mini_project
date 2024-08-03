# Makefile for Banking System project

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++14

# Executable name
TARGET = BankingSystem

# Source files
SRCS = main.cpp Account.cpp BakingSystem.cpp NormalAccount.cpp User.cpp

# Header files
HEADERS = Account.h BankingSystem.h NormalAccount.h User.h BankingException.h

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile source files into object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
