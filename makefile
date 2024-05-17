# Compiler
CC = g++ -std=c++17
# Compiler flags
CFLAGS = -MMD -MP -I ./lib
# Executable name
EXECUTABLE = main
# Dependencies
DEPENDENCIES = ./bin/statements.o ./bin/expressions.o ./bin/test.o
MAIN_DEP = ./bin/main.d

all: $(EXECUTABLE)

# Compilation rule for the C++ program
$(EXECUTABLE): $(DEPENDENCIES) ./bin/main.o
	$(CC) $(CFLAGS) -o $(EXECUTABLE) ./bin/main.o $(DEPENDENCIES)

# Compilation rule for the main file
./bin/main.o: main.cpp
	$(CC) -c $(CFLAGS) main.cpp -o ./bin/main.o

# Compilation rules for statements and expressions
./bin/statements.o: ./src/statements.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

./bin/expressions.o: ./src/expressions.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

./bin/test.o: ./src/test.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

# Include dependency files
-include $(wildcard ./bin/*.d)
-include $(wildcard $(MAIN_DEP))

# Clean rule to remove object files and executable
clean:
	rm -f $(EXECUTABLE) $(DEPENDENCIES) $(MAIN_DEP)
	rm -f ./bin/*.o ./bin/*.d
# Run the program with custom arguments
run: $(EXECUTABLE)
	./$(EXECUTABLE) ${ARGS}

# Phony target to avoid conflicts with file names
.PHONY: all clean run
