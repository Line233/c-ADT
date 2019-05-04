CC=gcc -g
OBJstatus=Status.o
OBJtype=Int.o Triple.o Pointer.o Char.o CII.o CI.o CodeNode.o
OBJelement= ElementType.o 


all:$(OBJstatus) $(OBJtype) $(OBJelement)



%.o:%.c %.h
	$(CC) -c $*.c

clean:
	rm $(OBJstatus) 
	rm $(OBJtype) 
	rm $(OBJelement) 

# ElementTypeTest.exe:$(Types)
#      $(CC) -o ElementTypeTest.exe $(Types)


# $@: the target filename.
# $*: the target filename without the file extension.
# $<: the first prerequisite filename.
# $^: the filenames of all the prerequisites, separated by spaces, discard duplicates.
# $+: similar to $^, but includes duplicates.
# $?: the names of all prerequisites that are newer than the target, separated by spaces.

