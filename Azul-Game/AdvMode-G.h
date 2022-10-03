#ifndef COSC_ASSIGN_ADV_G
#define COSC_ASSIGN_ADV_G

#include <iostream>
#include <fstream>
#include <sstream>

#include "CentralFactory.h"
#include "Factory.h"
#include "LinkedList.h"
#include "Mosaic.h"
#include "Player.h"
#include "Tile.h"
#include "SaveGame.h"
#include "BoxLid.h"

#define START_INPUT 0
#define TILE_ARRAY 4
#define START_LENGTH 5
#define FACT_INPUT 5
#define TILE_INPUT 7
#define FACT_AND_TILE_LENGTH 2
#define FACT_AND_TILE_ONE 1
#define ROW_INPUT 9
#define ROW_LENGTH 1
#define ROUNDS 5
#define ROUND_START 1

class ADVG {
public:
    ADVG(std::string p1, std::string p2, bool random_choice, std::string seed);
    ADVG(Player* p1, Player* p2, BST* factory1, BST* factory2, BST* factory3,
        BST* factory4, BST* factory5, LinkedList* tilebag, CentralFactory* centralfactory, BoxLid* boxlid, int round, 
        int turn, SaveGame* savegame, bool random, std::string seed);
    ~ADVG();

    /**
    * Used to start a new game
    */
    void start();

    /**
    * Used for each round
    */
    void round();

    /**
    * Used when loading in a game and the round is half done
    */
    void partialRound();

    /**
    * Used to get player 1 input
    */
    void p1Input();

    /**
    * Used to get player 2 input
    */
    void p2Input();

    /**
    * Used to save the game at the current state
    */
    void save(std::string file);

    /**
    * Used to print players factory and mosaci
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
    * Checks validity of players text
    */
    bool validText(std::string playermove);

    /**
    * Checks validity of playermove
    */
    bool validMove(Player* player, std::string playermove);

    /**
    * End of game method 
    */
    void gameend();

    /**
    * Manual Move at end of round
    */
    void manual(Player* player);

    /**
    * Used if eof is called
    */
    void exitgame();
    
private:

    Player* player1;
    Player* player2;
    CentralFactory* centralfactory;
    BST* factory1;
    BST* factory2;
    BST* factory3;
    BST* factory4;
    BST* factory5;
    LinkedList* tilebag;
    SaveGame* savegame;
    BoxLid* boxlid;

    int roundCount;
    std::string seed;
    bool random_choice;
    // Only used when loading in game
    int turn;
} ;

#endif //COSC_ASSIGN_ADV_G