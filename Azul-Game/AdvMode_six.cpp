#include "AdvMode_six.h"

ADVSIX::ADVSIX(std::string p1, std::string p2, bool random_choice, std::string seed)
{
    // Creating all objects
    this->player1 = new Player(p1, 0);
    this->player2 = new Player(p2, 0);
    this->factory1 = new BST();
    this->factory2 = new BST();
    this->factory3 = new BST();
    this->factory4 = new BST();
    this->factory5 = new BST();
    this->centralfactory = new CentralFactory();
    this->tilebag = new LinkedList();
    this->savegame = new SaveGame();
    this->boxlid = new BoxLid();
    this->roundCount = ROUND_START;
    this->turn = ROUND_START;
    this->random_choice = random_choice;
    this->seed = seed;
}
// This is used to load in game
ADVSIX::ADVSIX(Player* p1, Player* p2, BST* factory1, BST* factory2, BST* factory3,
        BST* factory4, BST* factory5, LinkedList* tilebag, CentralFactory* centralfactory, BoxLid* boxlid, int round, int turn,
        SaveGame* savegame, bool random_choice, std::string seed){
            this->player1 = p1;
            this->player2 = p2;
            this->factory1 = factory1;
            this->factory2 = factory2;
            this->factory3 = factory3;
            this->factory4 = factory4;
            this->factory5 = factory5;
            this->centralfactory = centralfactory;
            this->tilebag = tilebag;
            this->savegame = savegame;
            this->boxlid = boxlid;
            this->roundCount = round;
            this->turn = turn;
            this->random_choice = random_choice;
            this->seed = seed;
        }

ADVSIX::~ADVSIX()
{
    delete player1;
    delete player2;
    delete factory1;
    delete factory2;
    delete factory3;
    delete factory4;
    delete factory5;
    delete centralfactory;
    delete tilebag;
    delete savegame;
    delete boxlid;
}

void ADVSIX::start()
{
    // If random then number of tiles is reduced so that boxlid can be utilised
    int j = 17;
    // Setting up the tile bag
    if(random_choice == true){
        j = 12;
    }
    // Setting up the tile bag
    for (int i = 0; i < j; i++){
        Tile *tile_red = new Tile(Red);
        tilebag->addBack(tile_red);
        Tile *tile_db = new Tile(Dark_Blue);
        tilebag->addBack(tile_db);
        Tile *tile_yellow = new Tile(Yellow);
        tilebag->addBack(tile_yellow);
        Tile *tile_lb = new Tile(Light_Blue);
        tilebag->addBack(tile_lb);
        Tile *tile_black = new Tile(Black);
        tilebag->addBack(tile_black);
        Tile *tile_orange = new Tile(Orange);
        tilebag->addBack(tile_orange);
    }
    if(random_choice == true){
        tilebag->shuffle(stoi(seed));
        std::string random_tb;
        for(int i = 0; i < tilebag->size(); i ++){
            random_tb = random_tb + tilebag->get(i)->getletter();
        }
        savegame->changeInital(random_tb);
    } else {
        // Saving the inital tile bag
        savegame->changeInital("RBYLUORBYLUORBYLUORBYLUORBYLUORBYLUORBYLUORBYLUORBYLUORBYLUORBYLUORBYLUORBYLUORBYLUORBYLUORBYLUORBYLUO");
    }
    // Player 1 set first
    player1->setFirst(true);
}
// One round of game
void ADVSIX::round()
{
    if(tilebag->size() < 20){
        while(boxlid->size() >0){
            tilebag->addBack(boxlid->getTile(0));
            boxlid->remove(0);
        }
        tilebag->shuffle(stoi(seed));
    }
    Tile *Ftile = new Tile(First_Player);
    // Adding F tile to central factory
    centralfactory->add(Ftile);
    // Filling factories getting first item from tile bag
    for (int i = 0; i < TILES_IN_FACTORY; i++)
    {
        factory1->add(tilebag->get(0)->getColour());
        tilebag->removeFront();
    }
    for (int i = 0; i < TILES_IN_FACTORY; i++)
    {
        factory2->add(tilebag->get(0)->getColour());
        tilebag->removeFront();
    }
    for (int i = 0; i < TILES_IN_FACTORY; i++)
    {
        factory3->add(tilebag->get(0)->getColour());
        tilebag->removeFront();
    }
    for (int i = 0; i < TILES_IN_FACTORY; i++)
    {
        factory4->add(tilebag->get(0)->getColour());
        tilebag->removeFront();
    }
    for (int i = 0; i < TILES_IN_FACTORY; i++)
    {
        factory5->add(tilebag->get(0)->getColour());
        tilebag->removeFront();
    }
    // This is for if player two is first
    if(player2->getFirst() == true){
        p2Input();
    }
    // Rounds will keep going to round over
    while (roundover() == false)
    {
        p1Input();
        if (roundover() == false)
        {
            p2Input();
        }
    }
}
// Used for loaded in game when round is not finished
void ADVSIX::partialRound(){
    std::cout << std::endl << "The current score is...." << std::endl << player1->getName() << ": " << player1->getPoints() << 
        std::endl << player2->getName() << ": " << player2->getPoints() << std::endl;
    while(roundover() == false){
        if (turn == 1){
            p1Input();
            turn = 2;
        } else if (turn == 2){
            p2Input();
            turn = 1;
        }
    }
    roundend();
}

void ADVSIX::p1Input(){
    // Getting player input
    std::cout << std::endl;
    printplayer(player1);
    std::string playermove;
    std::cout << std::endl
                << "> ";
    std::getline(std::cin, playermove);
    // Checking the players move is valid
    while (playermove.substr(START_INPUT, START_LENGTH) == "Save " || playermove.substr(START_INPUT, START_LENGTH) == "save " ||
            !validText(playermove) || !validMove(player1, playermove) ||
            player1->getAdvMosaic()->alreadyThere(stoi(playermove.substr(ROW_INPUT, ROW_LENGTH)), playermove.substr(TILE_INPUT, ROW_LENGTH)) 
            ||player1->getAdvMosaic()->returnIfStorageIsFull(stoi(playermove.substr(ROW_INPUT, ROW_LENGTH)))){   
        // If control D given then game is closed
        if(std::cin.eof()){
            exitgame();
        }
        // If player saves game
        if(playermove.substr(START_INPUT, START_LENGTH) == "Save " || playermove.substr(START_INPUT, START_LENGTH) == "save "){
            std::stringstream ss{playermove};
            std::string file;
            ss >> file;
            ss >> file;
            // Save is called
            save(file);
            std::cout << "Game succesfully saved to '" << file << "'" << std::endl;
            std::cout << std::endl
                    << "> ";
            std::getline(std::cin, playermove);
        } else {
            std::cout << "Invalid Input (Format is: Turn <factory> <tile> <row>)";
            std::cout << std::endl
                    << "> ";
            std::getline(std::cin, playermove);
        }       
    }
    std::cout << std::endl;
    // If players move is valid then game is started
    if (playermove.substr(START_INPUT, START_LENGTH) == "Turn " || playermove.substr(START_INPUT, START_LENGTH) == "turn ")
    {
        // Player makes move
        move(player1, playermove);
        // Moved is saved
        savegame->add(playermove);
    }
}
// Same as P1 except for P2
void ADVSIX::p2Input(){
    printplayer(player2);
    std::string playermove2;
    std::cout << std::endl
            << "> ";
    std::getline(std::cin, playermove2);
    while (playermove2.substr(START_INPUT, START_LENGTH) == "Save " || playermove2.substr(START_INPUT, START_LENGTH) == "save " ||
        !validText(playermove2) || !validMove(player2, playermove2)||
        player2->getAdvMosaic()->alreadyThere(stoi(playermove2.substr(ROW_INPUT, ROW_LENGTH)), playermove2.substr(TILE_INPUT, ROW_LENGTH)) 
        || player2->getAdvMosaic()->returnIfStorageIsFull(stoi(playermove2.substr(ROW_INPUT, ROW_LENGTH))))
    {
        if(std::cin.eof()){
            exitgame();
        }
        if(playermove2.substr(START_INPUT, START_LENGTH) == "Save " || playermove2.substr(START_INPUT, START_LENGTH) == "save "){
            std::stringstream ss{playermove2};
            std::string file;
            ss >> file;
            ss >> file;
            save(file);
            std::cout << "Game succesfully saved to '" << file << "'" << std::endl;
            std::cout << std::endl
                    << "> ";
            std::getline(std::cin, playermove2);
        } else{
            std::cout << "Invalid Input (Format is: Turn <factory> <tile> <row>";
            std::cout << std::endl
                    << "> ";
            std::getline(std::cin, playermove2);
        }
    }
    std::cout << std::endl;
    if (playermove2.substr(START_INPUT, START_LENGTH) == "Turn " || playermove2.substr(START_INPUT, START_LENGTH) == "turn ")
    {
        move(player2, playermove2);
        savegame->add(playermove2);
    }
}

// When save game is called
void ADVSIX::save(std::string file)
{
    std::ofstream savefile;
    savefile.open(file);
    // If random on use new format
    savefile << "#NewFormat_ADVSIX\n";
    savefile << seed << "\n";
    // Inital tilebag saved
    savefile << savegame->returnInital() << "\n";
    // Names saved
    savefile << player1->getName() << "\n";
    savefile << player2->getName() << "\n";
    // Goes through all moves and saves them
    for (int i = 0; i < savegame->size(); ++i)
    {
        savefile << savegame->getMove(i) << "\n";
    }
    savefile.close();
}
// Prints player info
void ADVSIX::printplayer(Player *player)
{
    std::cout << std::endl
              << "TURN FOR PLAYER: " << player->getName() << std::endl;
    std::cout << "Factories: " << std::endl;
    std::cout << "0: ";
    centralfactory->printletters();
    std::cout << std::endl
              << "1: ";
    factory1->dfs();
    std::cout << std::endl
              << "2: ";
    factory2->dfs();
    std::cout << std::endl
              << "3: ";
    factory3->dfs();
    std::cout << std::endl
              << "4: ";
    factory4->dfs();
    std::cout << std::endl
              << "5: ";
    factory5->dfs();

    std::cout << std::endl
              << std::endl
              << "Mosaic for " << player->getName() << ": " << std::endl;
    player->getAdvMosaic()->print();
}

void ADVSIX::move(Player *player, std::string move)
{
    // Splitting the move apart to get each individual part
    std::string fac = move.substr(FACT_INPUT, 1);
    std::string chosentile = move.substr(TILE_INPUT, 1);
    std::string row = move.substr(ROW_INPUT, ROW_LENGTH);

    //Creating a temporary factory to determine which factory was chosen based off user input
    BST *chosenfac = nullptr;
    bool central = false;
    int tile_col;
    // Selecting the factory
    if (fac == "1")
    {
        chosenfac = factory1;
    }
    else if (fac == "2")
    {
        chosenfac = factory2;
    }
    else if (fac == "3")
    {
        chosenfac = factory3;
    }
    else if (fac == "4")
    {
        chosenfac = factory4;
    }
    else if (fac == "5")
    {
        chosenfac = factory5;
    }
    else if (fac == "0")
    {
        central = true;
    }
    // If not central factory then tile is converted to colour for BST
    if(central == false){
        if(chosentile == "R"){
            tile_col = 0;
        } else if(chosentile == "Y"){
            tile_col = 1;
        } else if(chosentile == "B"){
            tile_col = 2;
        } else if(chosentile == "L"){
            tile_col = 3;
        } else if(chosentile == "U"){
            tile_col = 4;
        } else if(chosentile == "O"){
            tile_col = 8;
        }
    }
    int lastIndex = -1;
    int firstIndex = -1;
    int freeSpots = 0;
    // Unless row is 7 which means tiles go to broken
    if(row != "7"){
        for (int i = 5; i>= 0; i--)
        {
             // Getting the last index of that storage row, if a tiles already there
            if (player->getAdvMosaic()->getStorageTile(stoi(row) - 1, i)->getColour() == No_Tile)
            {
                lastIndex = i;
            }
        }
        for (int i = 0; i < 6; i++)
        {
             // Getting the first index of that storage row
            if (player->getAdvMosaic()->getStorageTile(stoi(row) - 1, i)->getColour() == No_Tile)
            {
                firstIndex = i;
            }
        }
        for (int i = 0; i < 6; i++)
        {
             // Getting the free spots
            if (player->getAdvMosaic()->getStorageTile(stoi(row) - 1, i)->getColour() == No_Tile)
            {
                freeSpots++;
            }
        }
    }
    // If not the central factory   
    if (central == false)
    {
        Tile *tileToBeMoved = nullptr;
        int count = 0;
        for(int i = 0; i <chosenfac->multiple(tile_col); i++){
            tileToBeMoved = new Tile(tile_col);
            ++count;
        }
        for(int i = 0; i<=TILES_IN_FACTORY; i++){
            if(i != tile_col){
                if(chosenfac->multiple(i) > 0){
                    for(int j = 0; j<chosenfac->multiple(i); j++){
                        Tile *cent_tile = new Tile(i);
                        centralfactory->add(cent_tile);
                    }
                }
            }
        }
        if(8 != tile_col){
                if(chosenfac->multiple(8) > 0){
                    for(int j = 0; j<chosenfac->multiple(8); j++){
                        Tile *cent_tile = new Tile(8);
                        centralfactory->add(cent_tile);
                    }
                }
            }
        // moves tile from factory to storage
        if(row != "7"){
            // If there are more tiles then spots
            if (count > freeSpots){
                // Whatever can fit goes at the end
                player->getAdvMosaic()->setStorageRow(tileToBeMoved, stoi(row), freeSpots, lastIndex);
                 // The rest go to broken
                for(int i = 0; i < count-freeSpots; i++){
                    player->getAdvMosaic()->addBroken(tileToBeMoved, tilebag, boxlid, random_choice);
                }
            // If all can fit then they go into the row
            } else {
                player->getAdvMosaic()->setStorageRow_first(tileToBeMoved, stoi(row), count, firstIndex);
            }
        // Row 6 means broken, so all tiles are added to broken 
        } else {
            for(int i = 0; i<count; i++){
                player->getAdvMosaic()->addBroken(tileToBeMoved, tilebag, boxlid, random_choice);
            }
        }
        chosenfac->clear();
    }
    // This is the same for the central factory
    // Difference is that extra tiles stay in factory
    else
    {
        if (centralfactory->getTile(0)->getColour() == First_Player)
        {
            player->getAdvMosaic()->addBroken(centralfactory->getTile(0), tilebag, boxlid, random_choice);
            centralfactory->remove(0);
        }
        Tile *tileToBeMoved = nullptr;
        int count = 0;
        // Have to set central factory size now because it will change throughout loop
        int size = centralfactory->size();
        // This for loop goes through each tile in the factory
        for (int i = size - 1; i >= 0; i--)
        {
            // Getting the letter of the tile in index i of facotory
            // Checking if that matches the users selected tile
            if (centralfactory->getTile(i)->getletter() == chosentile)
            {
                // sets the temporary tile to the tile that will be moved
                // then increments a count of the number of tiles to be moved
                tileToBeMoved = new Tile(*centralfactory->getTile(i));
                ++count;

                centralfactory->remove(i);
            }
        }
        if(row != "7"){
            // If there are more tiles then spots
            if (count > freeSpots){
                // Whatever can fit goes at the end
                player->getAdvMosaic()->setStorageRow(tileToBeMoved, stoi(row), freeSpots, lastIndex);
                 // The rest go to broken
                for(int i = 0; i < count-freeSpots; i++){
                    player->getAdvMosaic()->addBroken(tileToBeMoved, tilebag, boxlid, random_choice);
                }
            // If all can fit then they go into the row
            } else {
                player->getAdvMosaic()->setStorageRow_first(tileToBeMoved, stoi(row), count, firstIndex);
            }
        } else {
            for(int i = 0; i<count; i++){
                player->getAdvMosaic()->addBroken(tileToBeMoved, tilebag, boxlid, random_choice);
            }
        }
    }
}
// Returns true or false if round is over
bool ADVSIX::roundover()
{
    // Sees if all factories are empty
    bool returnval = false;
    if (factory1->isEmpty() == true && factory2->isEmpty() == true && factory3->isEmpty() == true &&
        factory4->isEmpty() == true && factory5->isEmpty() == true && centralfactory->size() == 0)
    {
        returnval = true;
    }
    return returnval;
}
// Method for end of round
void ADVSIX::roundend()
{
    // Round is increased
    ++roundCount;
    // Checks if the storage is full, this is used later in mosaic class
    player1->getAdvMosaic()->checkIfStorageIsFull();
    for(int i = 0; i< ROW_COL_SIZE_ADV; i++){
        // End of round is called to automatically move mosaics, tile bag is updated
        this->tilebag = player1->getAdvMosaic()->endOfRound(tilebag, boxlid, random_choice, i);
        // Scoring for this tile moved
        player1->setPoints(player1->getAdvMosaic()->scoring_tile(player1->getPoints(), i));
    }
    // Scoring for broken line
    player1->setPoints(player1->getAdvMosaic()->scoring_broken(player1->getPoints()));
    // Sets whose first
    player1->setFirst(player1->getAdvMosaic()->checkfirst());
    // Tile bag is updated wth broken
    this->tilebag = player1->getAdvMosaic()->clearBroken(tilebag, boxlid, random_choice);

    // Same as above
    player2->getAdvMosaic()->checkIfStorageIsFull();
    for(int i = 0; i< ROW_COL_SIZE_ADV; i++){
        // End of round is called to automatically move mosaics, tile bag is updated
        this->tilebag = player2->getAdvMosaic()->endOfRound(tilebag, boxlid, random_choice, i);
        // Scoring for this tile moved
        player2->setPoints(player2->getAdvMosaic()->scoring_tile(player2->getPoints(), i));
    }
    // Scoring for broken line
    player2->setPoints(player2->getAdvMosaic()->scoring_broken(player2->getPoints()));
    // Sets whose first
    player2->setFirst(player2->getAdvMosaic()->checkfirst());
    // Tile bag is updated wth broken
    this->tilebag = player2->getAdvMosaic()->clearBroken(tilebag, boxlid, random_choice);
    // Printing Score
    if(roundCount <= ROUNDS){
        std::cout << "Scores:" << std::endl;
        std::cout << "Player " << player1->getName() << ": " << player1->getPoints() << std::endl;
        std::cout << "Player " << player2->getName() << ": " << player2->getPoints() << std::endl;
        std::cout << "=== END OF ROUND ===" << std::endl << std::endl;
    }
}
// This validates users input
bool ADVSIX::validText(std::string playermove)
{
    // First part must be turn
    bool returnval = false;
    if ((playermove.substr(START_INPUT, START_LENGTH) == "turn " || playermove.substr(START_INPUT, START_LENGTH) == "Turn ") && 
            playermove.size() != 10)
    {
        returnval = false;
    }
    else if (playermove.substr(START_INPUT, START_LENGTH) == "turn " || playermove.substr(START_INPUT, START_LENGTH) == "Turn ")
    {
        // Next must be a valid factory
        if (playermove.substr(FACT_INPUT, FACT_AND_TILE_LENGTH) == "0 " || playermove.substr(FACT_INPUT, FACT_AND_TILE_LENGTH) == "1 "
                || playermove.substr(FACT_INPUT, FACT_AND_TILE_LENGTH) == "2 " || 
                playermove.substr(FACT_INPUT, FACT_AND_TILE_LENGTH) == "3 " || 
                playermove.substr(FACT_INPUT, FACT_AND_TILE_LENGTH) == "4 " || 
                playermove.substr(FACT_INPUT, FACT_AND_TILE_LENGTH) == "5 ")
        {
            // Tile must be valid
            if (playermove.substr(TILE_INPUT, FACT_AND_TILE_LENGTH) == "R " || 
                    playermove.substr(TILE_INPUT, FACT_AND_TILE_LENGTH) == "Y " ||
                    playermove.substr(TILE_INPUT, FACT_AND_TILE_LENGTH) == "B " || 
                    playermove.substr(TILE_INPUT, FACT_AND_TILE_LENGTH) == "L " || 
                    playermove.substr(TILE_INPUT, FACT_AND_TILE_LENGTH) == "U "|| 
                    playermove.substr(TILE_INPUT, FACT_AND_TILE_LENGTH) == "O ")
            {
                // Row must be valid
                if (playermove.substr(ROW_INPUT, ROW_LENGTH) == "1" || playermove.substr(ROW_INPUT, ROW_LENGTH) == "2" || 
                        playermove.substr(ROW_INPUT, ROW_LENGTH) == "3" || playermove.substr(ROW_INPUT, ROW_LENGTH) == "4" || 
                        playermove.substr(ROW_INPUT, ROW_LENGTH) == "5" || playermove.substr(ROW_INPUT, ROW_LENGTH) == "6"|| 
                        playermove.substr(ROW_INPUT, ROW_LENGTH) == "7")
                {
                    returnval = true;
                }
                else
                {
                    returnval = false;
                }
            }
            else
            {
                returnval = false;
            }
        }
        else
        {
            returnval = false;
        }
    }
    // If save then its valid
    else if (playermove.substr(START_INPUT, START_LENGTH) == "save " || playermove.substr(START_INPUT, START_LENGTH) == "Save ")
    {
        returnval = true;
    }
    else
    {
        returnval = false;
    }
    return returnval;
}
// Checks if the move is valid
bool ADVSIX::validMove(Player *player, std::string playermove)
{
    // Input is broken apart
    std::string fac = playermove.substr(FACT_INPUT, FACT_AND_TILE_ONE);
    std::string chosentile = playermove.substr(TILE_INPUT, FACT_AND_TILE_ONE);
    std::string row = playermove.substr(ROW_INPUT, ROW_LENGTH);
    int colour_num;
    if(fac != "0"){
        if(chosentile == "R"){
        colour_num = Red;
        } else if(chosentile == "Y"){
            colour_num = Yellow;
        } else if(chosentile == "B"){
            colour_num = Dark_Blue;
        } else if(chosentile == "L"){
            colour_num = Light_Blue;
        } else if(chosentile == "U"){
            colour_num = Black;
        } else if(chosentile == "O"){
            colour_num = Orange;
        }
    }
    bool check1 = false;
    bool check2 = false;
    bool check3 = false;
    bool returnval = false;
    // Tile must be same as row colour or row must be empty
    if (player->getAdvMosaic()->checkrowcolour(std::stoi(row)) == chosentile ||
        player->getAdvMosaic()->checkrowcolour(std::stoi(row)) == "." || row == "7")
    {
        check1 = true;
    }
    // Goes though to make sure tile is in factory
    if (fac == "1")
    {
        if (factory1->isEmpty() == false)
        {
            check2 = true;
        }
        for (int i = 0; i < TILES_IN_FACTORY; i++)
        {
            if (factory1->contains(colour_num) == true)
            {
                check3 = true;
            }
        }
    }
    else if (fac == "2")
    {
        if (factory2->isEmpty() == false)
        {
            check2 = true;
        }
        for (int i = 0; i < TILES_IN_FACTORY; i++)
        {
            if (factory2->contains(colour_num) == true)
            {
                check3 = true;
            }
        }
    }
    else if (fac == "3")
    {
        if (factory3->isEmpty() == false)
        {
            check2 = true;
        }
        for (int i = 0; i < TILES_IN_FACTORY; i++)
        {
            if (factory3->contains(colour_num) == true)
            {
                check3 = true;
            }
        }
    }
    else if (fac == "4")
    {
        if (factory4->isEmpty() == false)
        {
            check2 = true;
        }
        for (int i = 0; i < TILES_IN_FACTORY; i++)
        {
            if (factory4->contains(colour_num) == true)
            {
                check3 = true;
            }
        }
    }
    else if (fac == "5")
    {
        if (factory5->isEmpty() == false)
        {
            check2 = true;
        }
        for (int i = 0; i < TILES_IN_FACTORY; i++)
        {
            if (factory5->contains(colour_num) == true)
            {
                check3 = true;
            }
        }
    }
    else if (fac == "0")
    {
        if (centralfactory->size() > 0)
        {
            check2 = true;
        }
        for (int i = 0; i < centralfactory->size(); i++)
        {
            if (centralfactory->getTile(i)->getletter() == chosentile)
            {
                check3 = true;
            }
        }
    }
    // If all is true then move is valid
    if (check1 == true && check2 == true && check3 == true)
    {
        returnval = true;
    }
    return returnval;
}
// Ends the game and prints final score and winner
void ADVSIX::gameend() {
    std::cout << "=== GAME OVER ===" << std::endl;
    std::cout << "Player " << player1->getName() << "'s Mosaic: "<< std::endl;
    player1->getAdvMosaic()->print();
    std::cout << std::endl << "Player " << player2->getName() << "'s Mosaic: "<< std::endl;
    player2->getAdvMosaic()->print();
    std::cout << std::endl << "Final Scores:" << std::endl;
    std::cout << "Player " << player1->getName() << ": " << player1->getPoints() << std::endl;
    std::cout << "Player " << player2->getName() << ": " << player2->getPoints() << std::endl;

    if (player1->getPoints() > player2->getPoints()) {
        std::cout << "Player " << player1->getName() << " wins!" << std::endl;
    } else if (player1->getPoints() == player2->getPoints()){
        std::cout << "It's a Draw!" << std::endl;
    } else {
        std::cout << "Player " << player2->getName() << " wins!" << std::endl;
    }
}
// Used when eof is given
void ADVSIX::exitgame(){
    std::cout << std::endl;
    exit(EXIT_SUCCESS);
}