CC=gcc
# CFLAGS=-I
OBJ=Int.o Triple.o ElementType.o ElementTypeTest.o Status.o
# src=Int.c Triple.c ElementType.c ElementTypeTest.c

all:BinaryTreeTest.exe

ElementTypeTest.exe:$(OBJ)
	$(CC) -o ElementTypeTest.exe $(OBJ)

%.o:%.c
	$(CC) -c $*.c

clean:
	rm $(OBJ) 
# all:ElementTypeTest.exe

# ElementTypeTest.exe:$(Types)
#      $(CC) -o ElementTypeTest.exe $(Types)


# $@: the target filename.
# $*: the target filename without the file extension.
# $<: the first prerequisite filename.
# $^: the filenames of all the prerequisites, separated by spaces, discard duplicates.
# $+: similar to $^, but includes duplicates.
# $?: the names of all prerequisites that are newer than the target, separated by spaces.

