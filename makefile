CC=gcc
OBJstatus=Status.o
OBJtype=Int.o Triple.o 
OBJelement= ElementType.o 
OBJbinarytree=BinaryTree.o
#test
OBJbinarytreetest=BinaryTreeTest.o
OBJelementest=ElementTypeTest.o

all:BinaryTreeTest.exe ElementTypeTest.exe

BinaryTreeTest.exe:$(OBJelement) $(OBJtype) $(OBJstatus) $(OBJbinarytree) $(OBJbinarytreetest)
	$(CC) -o $@ $^

ElementTypeTest.exe:$(OBJelement) $(OBJelement) $(OBJtype) $(OBJstatus) $(obj) $(OBJelementest)
	$(CC) -o $@ $^

$(OBJelementest):$(OBJelement)

$(OBJbinarytreetest):$(OBJbinarytree)

$(OBJbinarytree):$(OBJelement)

$(OBJelement):$(OBJtype) $(OBJstatus)

%.o:%.c
	$(CC) -c $*.c

clean:
	rm $(OBJstatus) 
	rm $(OBJtype) 
	rm $(OBJelement) 
	rm $(OBJbinarytree) 
	rm $(OBJbinarytreetest) 
	rm $(OBJelementest) 


# ElementTypeTest.exe:$(Types)
#      $(CC) -o ElementTypeTest.exe $(Types)


# $@: the target filename.
# $*: the target filename without the file extension.
# $<: the first prerequisite filename.
# $^: the filenames of all the prerequisites, separated by spaces, discard duplicates.
# $+: similar to $^, but includes duplicates.
# $?: the names of all prerequisites that are newer than the target, separated by spaces.

