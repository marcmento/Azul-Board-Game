# Azul Board Game
Azul Board Game built in C++ that can be played on command line. This project follows many of the same rules and concepts as the original board game version including the use of factories, mosaics's, tiles and factories. You can also save games in their current state and then use the save file later to load the game back into the same state. This version also comes with the following advanced modes:
* Grey-board mode
* 6-tile mode

I created these modes to give the user an alternative game exepriance rather then always playing the original game mode. These game mode can also be saved and loaded back in.
## Implementation
To create this game the following programming tools were used:
* Linked Lists
* Vectors
* 1D and 2D Array's
* Binary Search Tree
* ADT

Gameplay tests were also created to ensure all parts of the game work as intended.
## Running the game
To run this game, open the game folder in your IDE and run the makefile. After all files have be created run the following command
```
./azul
```
This will take you to the main menu where you can start the game. Once you have started the game turns can be made with the following command
```
Turn <factory> <tile> <row>
```
To clean up the files run the following command
```
make clean
```
