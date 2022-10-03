#ifndef COSC_ASSIGN_TWO_MOSAIC
#define COSC_ASSIGN_TWO_MOSAIC

#include "Tile.h"
#include "LinkedList.h"
#include "BoxLid.h"

#include <iostream>

#define ROW_COL_SIZE 5
#define ROUNDS 5
#define BROKEN_SIZE 7
#define STORAGE_ARRAY_INDEX 4

class Mosaic {
public:
    Mosaic();
    ~Mosaic();

    /**
    * Prints mosaic 
    */
    void print();
    /**
    * Sets storage row 
    */
    void setStorageRow(Tile* tile, int rowIndex, int numTiles);

    void setStorageRow_first(Tile *tile, int rowIndex, int numTiles, int firstIndex);

    /**
    * Sets storage row (Overload)
    */
    void setStorageRow(Tile *tile, int rowIndex, int numTiles, int startIndex);
    /**
    * Get storage row tile in specific spot
    */
    Tile* getStorageTile(int row, int column);
    /**
    * Adds tile to back of the broken line, if full goes to tilebag
    */
    void addBroken(Tile* temp, LinkedList* tilebag, BoxLid* BoxLid, bool random);
    /**
    * Checks if first tile is in broken
    */
    bool checkfirst();
    /**
    * Clears broken row
    */
    LinkedList* clearBroken(LinkedList *tilebag, BoxLid* BoxLid, bool random);
    /**
    * Returns row colour
    */
    std::string checkrowcolour(int rowIndex);
    /**
    * Moves tiles according to end of round rules
    */
    LinkedList* endOfRound(LinkedList* tilebag, BoxLid* boxlid, bool random, int row);
    /**
    * Will check if storage is full
    */
    void checkIfStorageIsFull();
    /**
    * Will return a boolean value if storage is full
    */
    bool returnIfStorageIsFull(int row);
    /**
    * Gets score after each tile is moved
    */
    int scoring_tile(int score, int row);
    /**
    * Reduces score due to broken tiles broken 
    */
    int scoring_broken(int score);
    /**
    * Returns true if tile is already in grid
    */
    bool alreadyThere(int rowindex, std::string tilecol);
    /**
    * Returns if mosaic spot has a tile already
    */
    bool mosaicSpotTaken(int row, int col);
    /**
    * Manual move of tile
    */
    LinkedList* manualMove(int row, int col, LinkedList* tilebag, BoxLid* boxlid, bool random);
    /**
    * Manual scoring
    */
    int manualScoring(int row, int col, int score);

private:
    // Left side of mosaci
    Tile* storage[ROW_COL_SIZE][ROW_COL_SIZE];
    // Right side
    Tile* grid[ROW_COL_SIZE][ROW_COL_SIZE];
    // Broken line
    Tile* broken[BROKEN_SIZE];

    bool storageRowIsFull[ROW_COL_SIZE];
    Colour storageRowColour[ROW_COL_SIZE];

    // template mosaic grid for moving tiles from storage to grid
    Colour gridTemplate[ROW_COL_SIZE][ROW_COL_SIZE] = {
        {Dark_Blue, Yellow, Red, Black, Light_Blue},
        {Light_Blue, Dark_Blue, Yellow, Red, Black}, 
        {Black, Light_Blue, Dark_Blue, Yellow, Red}, 
        {Red, Black, Light_Blue, Dark_Blue, Yellow}, 
        {Yellow, Red, Black, Light_Blue, Dark_Blue}
    };
};

#endif // COSC_ASSIGN_TWO_MOSAIC