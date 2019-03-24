SOURCE = main.cpp \ functions.cpp

OBJS = $(SOURCE:.cpp=.o )

#GNU C/C++ Compiler
GCC = g++

# GNU C/C++ Linker
LINK = g++

all : main

-include $(SOURCE:.cpp=.d)

main: main.o functions.o
	g++ -std=c++11 -g -o main main.o functions.o
   
main.o: main.cpp
	g++ -std=c++11 -g -c -Wall main.cpp
	
functions.o: functions.cpp functions.h node.h
	g++ -std=c++11 -g -c -Wall functions.cpp
