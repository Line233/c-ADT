CC=gcc -I ./ADT -I ./ADT/BasicTypes
OBJBasicElement=${./ADT/BasicTypes/*.o}
OBJADT=${./ADT/*.o}


all:BinaryTreeTest.exe ElementTypeTest.exe

BinaryTreeTest.exe: ./ADT/*.o ./ADT/BasicTypes/*.o BinaryTreeTest.o
	$(CC) -o $@ $^

ElementTypeTest.exe:./ADT/*.o ./ADT/BasicTypes/*.o ElementTypeTest.o
	$(CC) -o $@ $^ 

./ADT/*.o:
	cd ./ADT && MAKE
./ADT/BasicTypes/*.o:

%.o:%.c
	$(CC) -c $*.c

clean:
	rm BinaryTreeTest.o ElementTypeTest.o 
	cd ./ADT && MAKE clean
	

# ElementTypeTest.exe:$(Types)
#      $(CC) -o ElementTypeTest.exe $(Types)


# $@: the target filename.
# $*: the target filename without the file extension.
# $<: the first prerequisite filename.
# $^: the filenames of all the prerequisites, separated by spaces, discard duplicates.
# $+: similar to $^, but includes duplicates.
# $?: the names of all prerequisites that are newer than the target, separated by spaces.

