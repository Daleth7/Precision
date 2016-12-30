CC = g++

STD = c++11

OPTIMIZE = -O0

INCLUDE = -I../

FLAGS = $(OPTIMIZE) -Wall -std=$(STD) $(INCLUDE) -DNDEBUG

TEST_SRC = ./*.cpp
LIB_SRC = ../src/*.cpp

SRC = $(TEST_SRC) $(LIB_SRC)

OBJDIR = obj
BINDIR = bin

OBJ := $(OBJDIR)/$(SRC:%.cpp=%.o)

test_precision.exe: $(SRC)
	if not exist $(BINDIR)/NUL mkdir $(BINDIR)
	$(CC) -o $(BINDIR)/$@ $(FLAGS) $^

#test_precision.exe: $(OBJ)
#	$(CC) -o $@ $^
#
#$(OBJ): $(SRC)
#	$(CC) -c -o $@ $(FLAGS) $^

.PHONY: clean

clean:
	rm -f -r $(BINDIR)/*.exe $(OBJDIR)/*.o