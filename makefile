TILES = ./tiles/*.cpp
FILES = main.cpp World.cpp Helper.cpp

make:
	g++ $(FILES) $(TILES) -o out -fsanitize=address
