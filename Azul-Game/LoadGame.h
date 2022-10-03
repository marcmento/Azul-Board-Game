#ifndef COSC_ASSIGN_LG
#define COSC_ASSIGN_LG

#include "NewGame.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

class LoadGame {
public:
    LoadGame();
    ~LoadGame();

    /**
    * Read in a file
    */
    void readfile(std::string filename);

    /**
    * Return the size of the vector
    */
    int size();

    /**
    * Setup the loaded game
    */
    void setup();

    /**
    * Used for each round
    */
    void round(bool test);

    /**
    * Used to print players factory and mosaic
    */
    void printplayer(Player* player);

    /**
    * Used to make a players move
    */
    void move(Player* player, std::string move);

    /**
    * Used to check if the round is over
    */
    bool roundover();

    /**
    * End of round scoring and moving of tiles
    */
    void roundend();

    /**
    * Used to set up factories
    */
    void factorySetUp();

private:
    // Vector used for the moves loaded in from file
    std::vector<std::string> loadedmoves;
    // Setting up all objects required for game
    Player* lg_player1;
    Player* lg_player2;
    CentralFactory* lg_centralfactory;
    BST* lg_factory1;
    BST* lg_factory2;
    BST* lg_factory3;
    BST* lg_factory4;
    BST* lg_factory5;
    LinkedList* lg_tilebag;
    SaveGame* lg_savegame;
    BoxLid* lg_boxlid;
    // Enhancement features
    bool lg_random;
    std::string lg_seed;
    // Round counter
    int lg_roundCount;
} ;

#endif //COSC_ASSIGN_LG