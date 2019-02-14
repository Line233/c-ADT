CC=gcc -g 
Iarg= -I ./ADT -I ./ADT/BasicTypes 

ADT_PATH=ADT
ADT_SOURCE:=${wildcard $(ADT_PATH)/*.c}
ADT_HEAD:=${patsubst %.c,%.h,$(ADT_SOURCE) }
ADT_OBJ=${patsubst $(ADT_PATH)/%.c,$(ADT_PATH)/obj/%.o,$(ADT_SOURCE)}

BASICTYPE_PATH=ADT/BasicTypes
BASICTYPE_SOURCE:=${wildcard $(BASICTYPE_PATH)/*.c}
BASICTYPE_HEAD:=${patsubst %.c,%.h,$(BASICTYPE_SOURCE) }
BASICTYPE_OBJ=${patsubst $(BASICTYPE_PATH)/%.c,$(BASICTYPE_PATH)/obj/%.o,$(BASICTYPE_SOURCE)}



all:BinaryTreeTest.exe ElementTypeTest.exe StackSTest.exe GraphTest.exe Addline.exe

BinaryTreeTest.exe:  $(ADT_OBJ) $(BASICTYPE_OBJ)  obj/BinaryTreeTest.o
	$(CC) $(Iarg)  -o $@ $^
Addline.exe:  $(ADT_OBJ) $(BASICTYPE_OBJ)  obj/Addline.o
	$(CC) $(Iarg)  -o $@ $^
StackSTest.exe:  $(ADT_OBJ) $(BASICTYPE_OBJ) obj/StackSTest.o
	$(CC) $(Iarg) -o $@ $^

ElementTypeTest.exe: $(ADT_OBJ) $(BASICTYPE_OBJ) obj/ElementTypeTest.o
	$(CC) $(Iarg) -o $@ $^ 

GraphTest.exe:$(ADT_OBJ) $(BASICTYPE_OBJ) obj/GraphTest.o
	$(CC) $(Iarg) -o $@ $^ 


$(ADT_OBJ):$(ADT_PATH)/obj/%.o:$(ADT_PATH)/%.c $(ADT_PATH)/%.h $(BASICTYPE_OBJ)
	$(CC) $(Iarg) -c ${patsubst $(ADT_PATH)/obj/%.o,$(ADT_PATH)/%.c,$@} -o $@
	
$(BASICTYPE_OBJ): $(BASICTYPE_PATH)/obj/%.o:$(BASICTYPE_PATH)/%.c $(BASICTYPE_PATH)/%.h 
	$(CC) $(Iarg) -c $< -o $@

ADT_OBJ_PATH:
	mkdir -p  $(ADT_PATH)/obj

BASICTYPE_OBJ_PATH:
	mkdir -p  $(BASICTYPE_PATH)/obj

obj/%.o:%.c
	$(CC) $(Iarg) -c $< -o $@

clean:
	rm $(ADT_OBJ) $(BASICTYPE_OBJ)
	rm obj/BinaryTreeTest.o obj/ElementTypeTest.o obj/StackSTest.o


# $@: the target filename.
# $*: the target filename without the file extension.
# $<: the first prerequisite filename.
# $^: the filenames of all the prerequisites, separated by spaces, discard duplicates.
# $+: similar to $^, but includes duplicates.
# $?: the names of all prerequisites that are newer than the target, separated by spaces.

