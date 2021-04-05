CPP = g++
CPPFLAGS = -c -g
LDFLAGS = -g
SRC = $(wildcard src/*.cpp)
HDR = $(wildcard include/*.hpp)
OBJ = $(SRC:.cpp=.o)
EXEC = edulo

all: $(SRC) $(OBJ) $(EXEC)

$(EXEC): $(OBJ)
	$(CPP) $(LDFLAGS) $^ -o $@

%.o: %.cpp $(HDR)
	$(CPP) $(CPPFLAGS) $< -o $@

clean:
	rm src/*.o $(EXEC)

clean-obj:
	rm src/*.o

clean-exec:
	rm $(EXEC)