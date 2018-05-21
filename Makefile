.PHONY: clean

CC=g++
CPPFLAGS=-pedantic -Wall
objects=obj/main.o obj/GameEngine.o obj/GraphicModule.o obj/Board.o obj/AI.o
SFMLLIB=-lsfml-graphics -lsfml-window -lsfml-system

checkers: $(objects)
	$(CC) $(objects) -o checkers $(SFMLLIB)

obj/%.o: src/%.cpp
	$(CC) -c $< $(CPPFLAGS) -o $@

clean:
	rm -f obj/*.o checkers
