#include "BoxLid.h"

BoxLid::BoxLid() {
}

// Deconstructor loops through the vector removing the last item
BoxLid::~BoxLid(){
    while(Lid.size() != 0){
        Lid.pop_back();
    }
}

Tile* BoxLid::getTile(int index){
    return Lid[index];
}
// New tile added to back of vector
void BoxLid::add(Tile* tile){
    Tile* newTile = new Tile(*tile);
    Lid.push_back(newTile);
}
// Goes to front of vector then reaches the index and deletes it
void BoxLid::remove(int index){
    Lid.erase(Lid.begin() + index);
}
// Returns size
int BoxLid::size(){
    return Lid.size();
}
// Removes back
void BoxLid::removeBack(){
    Lid.pop_back();
}
// Prints boxlid
void BoxLid::print(){
    for(int i = 0; i < size(); i++){
        std::cout << getTile(i)->getletter();
    }
}