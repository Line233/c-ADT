CC=gcc -I ./ADT -I ./ADT/BasicTypes -g
OBJBasicElement=${./ADT/BasicTypes/*.o}
OBJADT=${./ADT/*.o}


all:BinaryTreeTest.exe ElementTypeTest.exe StackSTest.exe

BinaryTreeTest.exe: ./ADT/*.o ./ADT/BasicTypes/*.o BinaryTreeTest.o
	$(CC) -o $@ $^

StackSTest.exe: ./ADT/*.o ./ADT/BasicTypes/*.o StackSTest.o
	$(CC) -o $@ $^

ElementTypeTest.exe:./ADT/BasicTypes/*.o ElementTypeTest.o
	$(CC) -o $@ $^ 

./ADT/*.o:./ADT/*.c ./ADT/*.h
	cd ./ADT && MAKE
./ADT/BasicTypes/*.o:./ADT/BasicTypes/*.c ./ADT/BasicTypes/*.h
	cd ./ADT/BasicTypes && MAKE

%.o:%.c %.h
	$(CC) -c $*.c

clean:
	rm BinaryTreeTest.o ElementTypeTest.o StackSTest.o
	cd ./ADT && MAKE clean
	

# ElementTypeTest.exe:$(Types)
#      $(CC) -o ElementTypeTest.exe $(Types)


# $@: the target filename.
# $*: the target filename without the file extension.
# $<: the first prerequisite filename.
# $^: the filenames of all the prerequisites, separated by spaces, discard duplicates.
# $+: similar to $^, but includes duplicates.
# $?: the names of all prerequisites that are newer than the target, separated by spaces.

