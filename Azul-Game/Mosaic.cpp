#include "Mosaic.h"

Mosaic::Mosaic()
{
    // initialising storage
    for (int i = 0; i < ROW_COL_SIZE; ++i)
    {
        for (int j = 0; j < ROW_COL_SIZE; ++j)
        {
            storage[i][j] = new Tile(Blank);
        }
        for (int j = STORAGE_ARRAY_INDEX; j > 3 - i; --j)
        {
            storage[i][j] = new Tile(No_Tile);
        }
    }

    // initialising grid
    for (int i = 0; i < ROW_COL_SIZE; ++i)
    {
        for (int j = 0; j < ROW_COL_SIZE; ++j)
        {
            grid[i][j] = new Tile(No_Tile);
        }
    }

    // initialising broken
    for (int i = 0; i < BROKEN_SIZE; ++i)
    {
        broken[i] = new Tile(Blank);
    }

    // initialising storageRowIsFull array
    for (int i = 0; i < ROW_COL_SIZE; ++i)
    {
        storageRowIsFull[i] = false;
    }

    // initialising storageRowColour array
    for (int i = 0; i < ROW_COL_SIZE; ++i)
    {
        storageRowColour[i] = No_Tile;
    }
}

Mosaic::~Mosaic()
{   
    // Goes through all arrays and deletes tiles
    for (int i = 0; i < BROKEN_SIZE; ++i)
    {   
        delete broken[i];
        broken[i] = nullptr;
    }
    
    for (int i = 0; i < ROW_COL_SIZE; ++i)
    {
        for (int j = 0; j < ROW_COL_SIZE; ++j)
        {
            delete grid[i][j];
            grid[i][j] = nullptr;
        }
    }

    for (int i = 0; i < ROW_COL_SIZE; ++i)
    {
        for (int j = 0; j < ROW_COL_SIZE; ++j)
        {
            delete storage[i][j];
            storage[i][j] = nullptr;
        }
    }
}

void Mosaic::print()
{
    // Goes through all arrays and prints
    for (int i = 0; i < ROW_COL_SIZE; ++i)
    {

        std::cout << i + 1 << ": ";

        for (int j = 0; j < ROW_COL_SIZE; ++j)
        {
            storage[i][j]->printLetter();
            std::cout << ' ';
        }

        std::cout << "|| ";

        for (int j = 0; j < ROW_COL_SIZE; ++j)
        {
            grid[i][j]->printLetter();
            std::cout << ' ';
        }

        std::cout << std::endl;
    }

    std::cout << "broken: ";

    for (int i = 0; (unsigned)i < BROKEN_SIZE; ++i)
    {
        broken[i]->printLetter();
        std::cout << ' ';
    }

    std::cout << std::endl;
}

void Mosaic::setStorageRow(Tile *tile, int rowIndex, int numTiles)
{
    // Chosen tile is set in the array 
    for (int i = 0; i < numTiles; ++i)
    {
        // New tile createdthis is to prevent issue in moving of tiles to broken array
        Tile *ntile = new Tile(*tile); 
        storage[rowIndex - 1][STORAGE_ARRAY_INDEX - i] = ntile;
    }
}
void Mosaic::setStorageRow_first(Tile *tile, int rowIndex, int numTiles, int firstIndex)
{
    // Chosen tile is set in the array 
    for (int i = firstIndex; i > firstIndex - numTiles; i--)
    {
        Tile *ntile = new Tile(*tile); //this is to prevent issue in moving of tiles to broken array
        storage[rowIndex - 1][i] = ntile;
    }
}
// Overloaded function
void Mosaic::setStorageRow(Tile *tile, int rowIndex, int numTiles, int startIndex)
{
    // This method sets a starting point, if tile is already in row
    for (int i = startIndex; i < startIndex + numTiles; i++)
    {
        Tile *ntile = new Tile(*tile); //this is to prevent issue in moving of tiles to broken array
        storage[rowIndex - 1][i] = ntile;
    }
}

Tile *Mosaic::getStorageTile(int row, int column){
    return storage[row][column];
}

void Mosaic::addBroken(Tile* temp, LinkedList* tilebag, BoxLid* BoxLid, bool random){
    // Adds tile to back of broken
    int count = 0;
    for(int i = 0; i < BROKEN_SIZE; i++){
        if(broken[i]->isColoured()){
            count++;
        }
    }
    // If broken full the tile is added to the back of the tilebag
    if(count == BROKEN_SIZE){
        if(random == true){
            BoxLid->add(new Tile(*temp));
        } else {
            tilebag->addBack(new Tile(*temp));
        }
    } else{
        broken[count] = new Tile(*temp);
    }
}

bool Mosaic::checkfirst(){
    // Checks if the first tile is in the broken array
    bool first = false;
    for (int h = 0; h < BROKEN_SIZE; h++){
        if(broken[h]->getColour() == First_Player){
            first = true;
        }
    }
    // If so true is returned
    return first;
}
// Clears broken
LinkedList* Mosaic::clearBroken(LinkedList *tilebag, BoxLid* BoxLid, bool random){
    // Clears the broken line
    for (int h = 0; h < BROKEN_SIZE; h++){
        if(broken[h]->getColour() != First_Player && broken[h]->getColour() != Blank){
            if(random == true){
                BoxLid->add(new Tile(*broken[h]));
            } else {
                tilebag->addBack(new Tile(*broken[h]));
            }
        }
    }
    for (int h = 0; h < BROKEN_SIZE; ++h){
        broken[h] = new Tile(Blank);
    }
    return tilebag;
}

std::string Mosaic::checkrowcolour(int rowIndex)
{
    return storage[rowIndex - 1][STORAGE_ARRAY_INDEX]->getletter();
}

LinkedList* Mosaic::endOfRound(LinkedList* tilebag, BoxLid* boxlid, bool random, int row)
{
    int lastTileSpace = 0;
    Colour currentColour = Blank;

    lastTileSpace = STORAGE_ARRAY_INDEX - row;

    currentColour = storage[row][lastTileSpace]->getColour();

    if (currentColour != Blank)
    {
        //for each index in row of grid template
        for (int j = 0; j < ROW_COL_SIZE; j++)
        {
            if (currentColour == gridTemplate[row][j])
            {
                Tile *tile = new Tile(currentColour);
                grid[row][j] = tile;
            }
        }
        //copying coloured tiles into tilebag, not including the right-most tile
        for (int k = 0; k < STORAGE_ARRAY_INDEX; ++k){
            if (storage[row][k]->getColour() == currentColour && storage[row][k]->isColoured())
            {
                if(random == true){
                    boxlid->add(new Tile(*storage[row][k]));
                } else {
                    tilebag->addBack(new Tile(*storage[row][k]));
                }
            }
        }

        //for each index of storage
        for (int k = 0; k < ROW_COL_SIZE; ++k){
            if (storage[row][k]->getColour() == currentColour)
            {
                Tile *tile = new Tile(No_Tile);
                storage[row][k] = tile;
            }
        }
    }
    return tilebag;
}

void Mosaic::checkIfStorageIsFull(){
    int rowNo = 0; // storage row number
    int count = 0; // count of coloured tiles in a row
    // looping for all 5 storage rows
    while (rowNo < ROW_COL_SIZE) {
        // looping for all 5 storage columns
        for (int i = STORAGE_ARRAY_INDEX; i >= 0; --i) {
            // increments count if the tile is not blank, no_tile or a first_player tile
            if (storage[rowNo][i]->isColoured()) {
                ++count;
            }
        }
        // sets storageRowIsFull index to true if all tiles are coloured in storage row, where index corresponds to row number
        if (count == rowNo + 1) {
            storageRowIsFull[rowNo] = true;
        }
        // sets storageRowColour index to colour of the right-most tile of the storage row, where index corresponds to row number
        // resets count to 0 for the next row
        // increments rowNo to move to the next row
        storageRowColour[rowNo] = storage[rowNo][STORAGE_ARRAY_INDEX]->getColour();
        count = 0;
        ++rowNo;
    }
}

bool Mosaic::returnIfStorageIsFull(int row){
    bool returnval = false;
    int count = 0; // count of coloured tiles in a row
    // looping for all 5 storage rows
    if(row != 6){
        for (int i = 0; i < ROW_COL_SIZE; ++i) {
            // increments count if the tile is not blank, no_tile or a first_player tile
            if (storage[row-1][i]->isColoured()) {
                ++count;
            }
        }
        // sets storageRowIsFull index to true if all tiles are coloured in storage row, where index corresponds to row number
        if (count == row) {
            returnval = true;
        }
    } else {
        returnval = false;
    }
    return returnval;
}

int Mosaic::scoring_tile(int score, int row) {
    // player score to be returned
    int newScore = score;

    // int to check if score has been incremented for horizontally linked tiles
    int jScore = 0;
    // int to check if score has been incremented for vertically linked tiles
    int iScore = 0;
    
    // offset for checking for horizontally linked tiles
    int jOffset = 1; 
    // offset for checking for vertically linked tiles
    int iOffset = 1; 
    // bool value used as while loop condition when checking horizontal and vertically
    bool canContinue = true;  
    
    // if the respective storage row was full
    if (storageRowIsFull[row] == true) {
        // find the new tile, set x and y to respective values, increment score
        for (int j = 0; j < ROW_COL_SIZE; j++) {
            if (grid[row][j]->getColour() == storageRowColour[row] && grid[row][j]->isColoured()) {
                ++newScore;
                // loop to find horizontal linked tiles on left side, increment for each linked to tile
                while (canContinue) {
                    if (j - jOffset >= 0 && grid[row][j - jOffset]->isColoured()) {
                        ++newScore;
                        ++jScore;
                        ++jOffset;
                    } else {
                        canContinue = false;
                    }
                }
                // resetting jOffset value to 1
                jOffset = 1; 
                // resetting bool value for next while loop
                canContinue = true; 
                // loop to find horizontal linked tiles on right side, increment for each linked to tile
                while (canContinue) {
                    if (j + jOffset <= STORAGE_ARRAY_INDEX && grid[row][j + jOffset]->isColoured()) {
                        ++newScore;
                        ++jScore;
                        ++jOffset;
                    } else {
                        canContinue = false;
                    }
                }
                // resetting jOffset value to 1
                jOffset = 1; 
                canContinue = true; // resetting bool value for next while loop
                // loop to find vertical linked tiles on top side, increment for each linked to tile
                while (canContinue) {
                    if (row - iOffset >= 0 && grid[row - iOffset][j]->isColoured()) {
                        ++newScore;
                        ++iScore;
                        ++iOffset;
                    } else {
                        canContinue = false;
                    }
                }
                // resetting iOffset value to 1
                iOffset = 1; 
                // resetting bool value for next while loop
                canContinue = true;
                // loop to find vertical linked tiles on bottom side, increment for each linked to tile
                while (canContinue) {
                    if (row + iOffset <= STORAGE_ARRAY_INDEX && grid[row + iOffset][j]->isColoured()) {
                        ++newScore;
                        ++iScore;
                        ++iOffset;
                    } else {
                        canContinue = false;
                    }
                }
                // if score has been incremented for horizontally and vertically linked tiles, increment score
                if (jScore > 0 && iScore > 0) {
                    ++newScore;
                }
                jScore = 0;
                iScore = 0;
                // resetting iOffset value to 1
                iOffset = 1; 
                // resetting bool value for next while loop
                canContinue = true;
            }                
        }
    }
    return newScore;
}

int Mosaic::scoring_broken(int score) {
    int newScore = score;
    // looping for the broken tiles
    for (int i = 0; i < BROKEN_SIZE; ++i) {
        if ((i == 0 || i == 1) && broken[i]->isColoured()) {
            --newScore;
        } else if ((i == 2 || i == 3 || i == 4) && broken[i]->isColoured()) {
            newScore -=2;
        } else if ((i == 5 || i == 6) && broken[i]->isColoured()) {
            newScore -=3;
        }
    }
    return newScore;
}

bool Mosaic::alreadyThere(int rowindex, std::string tilecol){
    // Checks if a tile is already in the grid
    bool returnval = false;
    if(rowindex != 6){
        for(int i = 0; i<ROW_COL_SIZE; i++){
            if(grid[rowindex-1][i]->getletter() == tilecol){
                returnval = true;
            }
        }
    } else {
        returnval = false;
    }
    return returnval;
}

bool Mosaic::mosaicSpotTaken(int row, int col){
    bool returnval = false;
    if(grid[row][col]->isColoured() == true){
        returnval = true;
    }
    for(int i = 0; i < ROW_COL_SIZE; i ++){
            if(i != row ){
                if(grid[i][col]->getColour() == storage[row][4]->getColour()){
                    returnval = true;
                }
            }
        }
    return returnval;
}

LinkedList* Mosaic::manualMove(int row, int col, LinkedList* tilebag, BoxLid* boxlid, bool random){
    Tile* mTile = new Tile(storage[row][4]->getColour());
    grid[row][col] = mTile;
    //copying coloured tiles into tilebag, not including the right-most tile
    for (int k = 0; k < STORAGE_ARRAY_INDEX; ++k){
        if (storage[row][k]->getColour() != Blank){
            if(random == true){
                boxlid->add(new Tile(*storage[row][k]));
            } else {
                tilebag->addBack(new Tile(*storage[row][k]));
            }
        }
    }
    Colour temp = storage[row][4]->getColour();
    //for each index of storage
    for (int k = 0; k < ROW_COL_SIZE; ++k){
        if (storage[row][k]->getColour() == temp)
        {
            Tile *tile = new Tile(No_Tile);
            storage[row][k] = tile;
        }
    }
    return tilebag;
}

int Mosaic::manualScoring(int row, int col, int score){
    // player score to be returned
    int newScore = score;

    // int to check if score has been incremented for horizontally linked tiles
    int jScore = 0;
    // int to check if score has been incremented for vertically linked tiles
    int iScore = 0;
    
    // offset for checking for horizontally linked tiles
    int jOffset = 1; 
    // offset for checking for vertically linked tiles
    int iOffset = 1; 
    // bool value used as while loop condition when checking horizontal and vertically
    bool canContinue = true;  
        
    ++newScore;
    // loop to find horizontal linked tiles on left side, increment for each linked to tile
    while (canContinue) {
        if (col - jOffset >= 0 && grid[row][col - jOffset]->isColoured()) {
            ++newScore;
            ++jScore;
            ++jOffset;
        } else {
            canContinue = false;
        }
    }
    // resetting jOffset value to 1
    jOffset = 1; 
    // resetting bool value for next while loop
    canContinue = true; 
    // loop to find horizontal linked tiles on right side, increment for each linked to tile
    while (canContinue) {
        if (col + jOffset <= STORAGE_ARRAY_INDEX && grid[row][col + jOffset]->isColoured()) {
            ++newScore;
            ++jScore;
            ++jOffset;
        } else {
            canContinue = false;
        }
    }
            // resetting jOffset value to 1
    jOffset = 1; 
    canContinue = true; // resetting bool value for next while loop
    // loop to find vertical linked tiles on top side, increment for each linked to tile
    while (canContinue) {
        if (row - iOffset >= 0 && grid[row - iOffset][col]->isColoured()) {
            ++newScore;
            ++iScore;
            ++iOffset;
        } else {
            canContinue = false;
        }
    }
    // resetting iOffset value to 1
    iOffset = 1; 
    // resetting bool value for next while loop
    canContinue = true;
    // loop to find vertical linked tiles on bottom side, increment for each linked to tile
    while (canContinue) {
        if (row + iOffset <= STORAGE_ARRAY_INDEX && grid[row + iOffset][col]->isColoured()) {
            ++newScore;
            ++iScore;
            ++iOffset;
        } else {
            canContinue = false;
        }
    }
    // if score has been incremented for horizontally and vertically linked tiles, increment score
    if (jScore > 0 && iScore > 0) {
        ++newScore;
    }
    jScore = 0;
    iScore = 0;
    // resetting iOffset value to 1
    iOffset = 1; 
    // resetting bool value for next while loop
    canContinue = true;
    return newScore;
}
