#ifndef COSC_ASSIGN_TWO_BOXLID
#define COSC_ASSIGN_TWO_BOXLID

#include "Tile.h"

#include <vector>

class BoxLid {
public:
    BoxLid();
    ~BoxLid();

    /**
    * Get a tile at the index of the lid
    */
    Tile* getTile(int index);

    /**
    * Add a tile to the end of the lid
    */
    void add(Tile* tile);

    /**
    * Remove a Tile from the index of the box lid
    */
    void remove(int index);

    /**
    * Return box lid size
    */
    int size();

    /**
    * Remove back of box lid
    */
    void removeBack();

    /**
    * Prints the box lid
    */
    void print();

private:
    std::vector<Tile*> Lid;
} ;

#endif //COSC_ASSIGN_TWO_BOXLID