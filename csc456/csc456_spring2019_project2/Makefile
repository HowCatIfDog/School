# Use the GNU C/C++ compiler:
CC = gcc
CPP = g++

# COMPILER OPTIONS:
CFLAGS = -c #-g -Wall

#OBJECT FILES
OBJS = bankers.o

#TARGET FILES
TARGET = bankers

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -lm -pthread -o $(TARGET) $(OBJS)

bankers.o: bankers.c bank.h customer.h
	$(CC) $(CFLAGS) bankers.c


clean:
	$(RM) *.o *~ $(TARGET)
