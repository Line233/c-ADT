CC=gcc -I ./BasicTypes -g
OBJADT=BinaryTree.o StackS.o
#test


all:$(OBJADT) subsystem

subsystem:
	cd ./BasicTypes && MAKE

%.o:%.c
	$(CC) -c $*.c 
clean:
	rm $(OBJADT)
	cd ./BasicTypes && MAKE clean
# ElementTypeTest.exe:$(Types)
#      $(CC) -o ElementTypeTest.exe $(Types)


# $@: the target filename.
# $*: the target filename without the file extension.
# $<: the first prerequisite filename.
# $^: the filenames of all the prerequisites, separated by spaces, discard duplicates.
# $+: similar to $^, but includes duplicates.
# $?: the names of all prerequisites that are newer than the target, separated by spaces.

