.default: all

all: azul

clean:
	rm -rf azul azul.dSYM *.o

azul: main.o CentralFactory.o Factory.o LinkedList.o Mosaic.o Player.o Tile.o NewGame.o SaveGame.o LoadGame.o BoxLid.o AdvMode-G.o AdvMode_six.o Adv_Mosaic.o Adv_Load_G.o Adv_Load_six.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^