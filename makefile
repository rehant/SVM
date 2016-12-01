#please use 'make clean' to clean the directory of intermediate build files and the executable
#simply typing 'make' will compile all source code files to object files .o, and then link all
#object files into an executable
#we are using a lot of makefile macros

#changing platform dependant stuff, do not change this
# Linux (default)
LDFLAGS = -lGL -lGLU -lglut -lm
CFLAGS=-g -Wall -std=c++11
CC=g++
EXEEXT=
RM=rm

# Windows (cygwin)
ifeq "$(OS)" "Windows_NT"
	EXEEXT=.exe #on windows applications must have .exe extension
	RM=del #rm command for windows powershell
    LDFLAGS = -lfreeglut -lglu32 -lopengl32
else
# OS X
	OS := $(shell uname)
	ifeq ($(OS), Darwin)
	        LDFLAGS = -framework Carbon -framework OpenGL -framework GLUT
	endif
endif

#change the 't1' name to the name you want to call your application
PROGRAM_NAME=mt

all: $(PROGRAM_NAME)

#run target to compile and build, and then launch the executable
run: $(PROGRAM_NAME)
	./$(PROGRAM_NAME)$(EXEEXT)

#when adding additional source files, such as boilerplateClass.cpp
#or yourFile.cpp, add the filename with an object extension below
#ie. boilerplateClass.o and yourFile.o
#make will automatically know that the objectfile needs to be compiled
#form a cpp source file and find it itself :)

Mesh.o: Mesh.cpp
	rm -rf out
	$(CC) -o Mesh.o -c $^ -std=c++11 2>&1 | tee -a out

# Note: we don't need to add header-only classes (like Vector3D and Face3D) here. They don't have any code that needs to be compiled.
$(PROGRAM_NAME): meshtest.o Vertex3D.o Mesh.o Face3D.o
	$(CC) -o $(PROGRAM_NAME)$(EXEEXT) $^ $(CFLAGS) $(LDFLAGS) 2>&1 | tee -a out
	./$(PROGRAM_NAME)$(EXEEXT) 2>&1 | tee -a out

clean:
	$(RM) *.o *.x
