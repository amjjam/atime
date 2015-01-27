

FLAGS=-Wall -g -I ~/include/
CFLAGS=$(FLAGS)
CPPFLAGS=$(FLAGS)

CC=gcc
CPP=g++

TEST1_SRC=test1.C ../../src/aTime.C
TEST1_OBJ=$(TEST1_SRC:.C=.o)

test1: $(TEST1_OBJ)
	$(CPP) -o $@ $^ -lrt
