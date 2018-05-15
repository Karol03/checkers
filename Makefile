.PHONY: clean

CC=g++
CPPFLAGS=-pedantic -Wall
objects=obj/main.o obj/GameEngine.o obj/Player.o

checkers: $(objects)
	$(CC) -o checkers $(objects)

obj/%.o: src/%.cpp
	$(CC) -c $< $(CPPFLAGS) -o $@

clean:
	rm -f obj/*.o checkers
