all: random sumCharsFiles

random: random.cpp
	g++ random.cpp -o random -lpthread

sumCharsFiles: sumCharsFiles.cpp
	g++ -g sumCharsFiles.cpp -o sumCharsFiles -lpthread

clean:
	rm random sumCharsFiles
