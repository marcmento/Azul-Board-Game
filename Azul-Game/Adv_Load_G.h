#ifndef COSC_ASSIGN_AVDLG
#define COSC_ASSIGN_AVDLG

#include "AdvMode-G.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

class ADVLG {
public:
    ADVLG();
    ~ADVLG();

    /**
    * Read in a file
    */
    void readfile(std::string filename);

    /**
    * Return the size of the vector
    */
    int size();

    /**
    * Sets up the loaded game
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
    int roundend(int j);

    /**
    * Simulation of manually moved tiles
    */
    void manual(Player* player, std::string move, int i);

    /**
    * Used to set up factories
    */
    void factorySetUp();

private:
    // Vector used for the moves loaded in from file
    std::vector<std::string> loadedmoves;
    // Setting up all objects required for game
    Player* advlg_player1;
    Player* advlg_player2;
    CentralFactory* advlg_centralfactory;
    BST* advlg_factory1;
    BST* advlg_factory2;
    BST* advlg_factory3;
    BST* advlg_factory4;
    BST* advlg_factory5;
    LinkedList* advlg_tilebag;
    SaveGame* advlg_savegame;
    BoxLid* advlg_boxlid;
    // Enhancement features
    bool advlg_random;
    std::string advlg_seed;
    // Round counter
    int advlg_roundCount;
} ;

#endif //COSC_ASSIGN_AVDLG