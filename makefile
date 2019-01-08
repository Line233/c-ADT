CC=gcc -g 
Iarg= -I ./ADT -I ./ADT/BasicTypes 

ADT_PATH=./ADT
ADT_SOURCE:=${wildcard $(ADT_PATH)/*.c}
ADT_HEAD:=${patsubst %.c,%.h,$(ADT_SOURCE) }
ADT_OBJ=${patsubst %.c,%.o,$(ADT_SOURCE)}

BASICTYPE_PATH=./ADT/BasicTypes
BASICTYPE_SOURCE:=${wildcard $(BASICTYPE_PATH)/*.c}
BASICTYPE_HEAD:=${patsubst %.c,%.h,$(BASICTYPE_SOURCE) }
BASICTYPE_OBJ=${patsubst %.c,%.o,$(BASICTYPE_SOURCE)}



all:BinaryTreeTest.exe ElementTypeTest.exe StackSTest.exe

BinaryTreeTest.exe:  $(ADT_OBJ) $(BASICTYPE_OBJ)  BinaryTreeTest.o
	$(CC) $(Iarg)  -o $@ $^

StackSTest.exe:  $(ADT_OBJ) $(BASICTYPE_OBJ) StackSTest.o
	$(CC) $(Iarg) -o $@ $^

ElementTypeTest.exe: $(ADT_OBJ) $(BASICTYPE_OBJ) ElementTypeTest.o
	$(CC) $(Iarg) -o $@ $^ 

$(ADT_OBJ):$(ADT_SOURCE) $(ADT_HEAD) $(BASICTYPE_SOURCE)
	$(CC) $(Iarg) -c $*.c -o $*.o

$(BASICTYPE_OBJ):$(BASICTYPE_SOURCE) $(BASICTYPE_HEAD)
	$(CC) $(Iarg) -c $*.c -o $*.o

%.o:%.c
	$(CC) $(Iarg) -c $<

clean:
	rm $(ADT_OBJ) $(BASICTYPE_OBJ)
	rm BinaryTreeTest.o ElementTypeTest.o StackSTest.o


# $@: the target filename.
# $*: the target filename without the file extension.
# $<: the first prerequisite filename.
# $^: the filenames of all the prerequisites, separated by spaces, discard duplicates.
# $+: similar to $^, but includes duplicates.
# $?: the names of all prerequisites that are newer than the target, separated by spaces.

