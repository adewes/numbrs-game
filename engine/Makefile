CPP= g++
FLAGS= -lSDL -lGL -lGLU

OBJECTS= sound.o graphics.o input.o game.o object.o $(wildcard ./objects/*.o) $(wildcard ./utils/*.o)

app: $(OBJECTS)	app.cpp
	$(CPP) -o $@ $(OBJECTS) app.cpp $(FLAGS);

objects:	objects/Makefile
	(cd objects;make)
 
%.o:	%.cpp
	$(CPP) -c $< $(FLAGS);



all: objects app
