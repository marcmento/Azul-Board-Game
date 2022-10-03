#ifndef COSC_ASSIGN_LSIX
#define COSC_ASSIGN_LSIX

#include "AdvMode_six.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

class ADVLGSIX {
public:
    ADVLGSIX();
    ~ADVLGSIX();

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
    Player* lgsix_player1;
    Player* lgsix_player2;
    CentralFactory* lgsix_centralfactory;
    BST* lgsix_factory1;
    BST* lgsix_factory2;
    BST* lgsix_factory3;
    BST* lgsix_factory4;
    BST* lgsix_factory5;
    LinkedList* lgsix_tilebag;
    SaveGame* lgsix_savegame;
    BoxLid* lgsix_boxlid;
    // Enhancement features
    bool lgsix_random;
    std::string lgsix_seed;
    // Round counter
    int lgsix_roundCount;
} ;

#endif //COSC_ASSIGN_LSIX