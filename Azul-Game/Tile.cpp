#include "Tile.h"

Tile::Tile() {

}

Tile::Tile(int colour_num){
   if(colour_num == 0){
      this->colour = Red;
   } else if(colour_num == 1){
      this->colour = Yellow;
   } else if(colour_num == 2){
      this->colour = Dark_Blue;
   } else if(colour_num == 3){
      this->colour = Light_Blue;
   } else if(colour_num == 4){
      this->colour = Black;
   } else if(colour_num == 5){
      this->colour = First_Player;
   } else if(colour_num == 6){
      this->colour = No_Tile;
   } else if(colour_num == 7){
      this->colour = Blank;
   } else if(colour_num == 8){
      this->colour = Orange;
   }
}

Tile::Tile(Colour colour)
{
   this->colour = colour;
}

Tile::Tile(Tile& other) {
   this->colour = other.colour;
}

Tile::~Tile() {
}

void Tile::setColour(Colour colour){
   this->colour = colour;
}

Colour Tile::getColour() {
   return colour;
}

std::string Tile::getletter(){
   Colour colour = getColour();
   std::string returnval;
   if(colour == 0){
      returnval =  "R";
   } else if (colour == 1){
      returnval = "Y";
   } else if (colour == 2){
      returnval = "B";
   } else if (colour == 3){
      returnval = "L";
   } else if (colour == 4){
      returnval = "U";
   } else if (colour == 5){
      returnval = "F";
   } else if (colour == 6){
      returnval = ".";
   } else if (colour == 7){
      returnval = " ";
   } else if (colour == 8){
      returnval = "O";
   }
   return returnval;
}

void Tile::printLetter() {
   if(colour == 0){
      std::cout << "R ";
   } else if (colour == 1){
      std::cout << "Y ";
   } else if (colour == 2){
      std::cout << "B ";
   } else if (colour == 3){
      std::cout << "L ";
   } else if (colour == 4){
      std::cout << "U ";
   } else if (colour == 5){
      std::cout << "F ";
   } else if (colour == 6){
      std::cout << ". ";
   } else if (colour == 7){
      std::cout << "  ";
   } else if (colour == 8){
      std::cout << "O ";
   } else{
      std::cout << "  ";
   }
}

bool Tile::isColoured() {
   return colour != Blank && colour != No_Tile;
}