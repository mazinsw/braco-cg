CPP  = g++
OBJ = main.o \
	  braco.o \
	  util.o \
	  suporte.o \
	  classes/display.o \
	  classes/glwindow.o
LIBS=-lSDLmain -lSDL -lGL -lGLU
FLAGS=

all: braco

clean:
	rm -rf $(OBJ) braco

braco: $(OBJ)
	$(CPP) -o braco $(OBJ) $(LIBS)

main.o: main.cpp
	$(CPP) -c main.cpp -o main.o $(FLAGS)

braco.o: braco.cpp
	$(CPP) -c braco.cpp -o braco.o $(FLAGS)

util.o: util.cpp
	$(CPP) -c util.cpp -o util.o $(FLAGS)

suporte.o: suporte.cpp
	$(CPP) -c suporte.cpp -o suporte.o $(FLAGS)

classes/glwindow.o: classes/glwindow.cpp
	$(CPP) -c classes/glwindow.cpp -o classes/glwindow.o $(FLAGS)

classes/display.o: classes/display.cpp
	$(CPP) -c classes/display.cpp -o classes/display.o $(FLAGS)
