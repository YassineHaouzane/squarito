#OBJS specifies which files to compile as part of the project
OBJS = squarito.o game.o

#CC specifies which compiler we're using
CC = gcc

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_ttf
OBJECTS_FLAGS= -g -O -c

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = squarito 

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

game.o : game.c
	$(CC) $(OBJECTS_FLAGS) game.c -o game.o $(LINKER_FLAGS)

squarito.o : squarito.c
	$(CC) $(OBJECTS_FLAGS) squarito.c -o squarito.o $(LINKER_FLAGS)


clean :
	rm *.o $(OBJ_NAME)

