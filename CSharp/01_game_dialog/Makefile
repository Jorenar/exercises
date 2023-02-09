EXE = Game.exe

CSC = mcs
FLAGS = -out:$(EXE)

SRC = $(wildcard *.cs **/*.cs)

all: $(EXE)

$(EXE): $(SRC)
	$(CSC) $^ $(FLAGS)

run: $(EXE)
	mono $(EXE)

clean:
	$(RM) $(EXE)
