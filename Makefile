CC=g++
OBJ=main.o strlib.o word.o parse.o arg.o random.o definition.o dictionary.o
DEPS=src/strlib.hpp src/word.hpp src/parse.hpp src/arg.hpp src/random.hpp src/definition.hpp src/dictionary.hpp

main: $(OBJ) $(DEPS)
	$(CC) -g -o lang-test $(OBJ)

main.o: $(DEPS)
	$(CC) -c src/main.cpp

strlib.o: $(DEPS)
	$(CC) -c src/strlib.cpp

word.o: $(DEPS)
	$(CC) -c src/word.cpp

parse.o: $(DEPS)
	$(CC) -c src/parse.cpp

arg.o: $(DEPS)
	$(CC) -c src/arg.cpp

random.o: $(DEPS)
	$(CC) -c src/random.cpp

definition.o: $(DEPS)
	$(CC) -c src/definition.cpp

dictionary.o: $(DEPS)
	$(CC) -c src/dictionary.cpp

clean:
	rm -f lang-test $(OBJ)
