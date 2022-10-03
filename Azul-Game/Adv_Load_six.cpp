#include "Adv_Load_six.h"
// Creating new objects at start of game
ADVLGSIX::ADVLGSIX() {
    this->lgsix_player1 = new Player("no name", 0);
    this->lgsix_player2 = new Player("no name1", 0);
    this->lgsix_factory1 = new BST();
    this->lgsix_factory2 = new BST();
    this->lgsix_factory3 = new BST();
    this->lgsix_factory4 = new BST();
    this->lgsix_factory5 = new BST();
    this->lgsix_centralfactory = new CentralFactory();
    this->lgsix_tilebag = new LinkedList();
    this->lgsix_savegame = new SaveGame();
    this->lgsix_boxlid = new BoxLid();
    this->lgsix_roundCount = ROUND_START;
    this->lgsix_random = false;
    this->lgsix_seed = "no";
}
// Deconstructor removes all moves from vector and all other objects
ADVLGSIX::~ADVLGSIX(){
    while(loadedmoves.size() != 0){
        loadedmoves.pop_back();
    }
    delete lgsix_player1;
    delete lgsix_player2;
    delete lgsix_factory1;
    delete lgsix_factory2;
    delete lgsix_factory3;
    delete lgsix_factory4;
    delete lgsix_factory5;
    delete lgsix_centralfactory;
    delete lgsix_tilebag;
    delete lgsix_savegame;
    delete lgsix_boxlid;
}

void ADVLGSIX::readfile(std::string filename){
    std::string line;
    std::ifstream loadfile;
    loadfile.open(filename);
    // Files is opened and looped through untill end of file is reached
    while(!loadfile.eof()){
	        std::getline(loadfile,line);
            // Line is added to the back of the moves vector 
	        loadedmoves.push_back(line);
        }
	loadfile.close();
}

int ADVLGSIX::size(){
    // Returns the size of the moves vector
    return loadedmoves.size();
}

void ADVLGSIX::setup(){
    // Goes through the inital tile bag and adds to tile bag
    for(int i = 0; i<loadedmoves[2].length(); i++){
        // If letter corresponds to colour then new tile is created and added to the back of the tilebag
        if(loadedmoves[2].substr(i,1) == "R"){
            Tile* tile_red = new Tile(Red);
            lgsix_tilebag->addBack(tile_red);
        } else if(loadedmoves[2].substr(i,1) == "L"){
            Tile* tile_LB = new Tile(Light_Blue);
            lgsix_tilebag->addBack(tile_LB);
        } else if(loadedmoves[2].substr(i,1) == "U"){
            Tile* tile_Black = new Tile(Black);
            lgsix_tilebag->addBack(tile_Black);
        } else if(loadedmoves[2].substr(i,1) == "B"){
            Tile* tile_DB = new Tile(Dark_Blue);
            lgsix_tilebag->addBack(tile_DB);
        } else if (loadedmoves[2].substr(i,1) == "Y"){
            Tile* tile_Yellow = new Tile(Yellow);
            lgsix_tilebag->addBack(tile_Yellow);
        } else if (loadedmoves[2].substr(i,1) == "O"){
            Tile* tile_Orange = new Tile(Orange);
            lgsix_tilebag->addBack(tile_Orange);
        }
    } 
    // If theres a seed random is turned on
    if(loadedmoves[1] != "no"){
        // Random is turned on
        lgsix_random = true;
        // Seed is recieved
        lgsix_seed = loadedmoves[1];
    }
    // Inital tile bag is set
    lgsix_savegame->changeInital(loadedmoves[2]);
    // Players names are set from file
    lgsix_player1->changeName(loadedmoves[3]);
    lgsix_player2->changeName(loadedmoves[4]);
    // Player 1 goes first
    lgsix_player1->setFirst(true);
}
// This method goes through all turns made and makes them
void ADVLGSIX::round(bool test)
{   
    // Factories are set up
    factorySetUp();
    bool round_start = true;
    int turn = 0;
    // First player gets the first turn
    if(lgsix_player1->getFirst() == true){
        turn = 1;
    } else {
        turn = 2;
    }
    // This for loop goes through all moves and makes them
    for(int i = 5; (unsigned) i < loadedmoves.size(); i++){
        // If there is a blank line then it is ignored
        if(loadedmoves[i].substr(START_INPUT, 5) != ""){
            // If rounds not over a move is made
            if(roundover() == false){
                // If player ones first and the rounds just started
                if(lgsix_player1->getFirst() == true && round_start == true){
                    move(lgsix_player1, loadedmoves[i]);
                    lgsix_savegame->add(loadedmoves[i]);
                    round_start = false;
                    turn = 2;
                // If players two first and the rounds just started
                } else if(lgsix_player2->getFirst() == true && round_start == true){
                    move(lgsix_player2, loadedmoves[i]);
                    lgsix_savegame->add(loadedmoves[i]);
                    round_start = false;
                    turn = 1;
                // If its not start of round then whoevers turn it is goes
                } else if (turn == 1){
                    // Move is called
                    move(lgsix_player1, loadedmoves[i]);
                    // Move is saved so if the game is saved again after its loaded the original moves are still saved
                    lgsix_savegame->add(loadedmoves[i]);
                    // Turn is then player two's
                    turn = 2;
                } else if (turn == 2){
                    move(lgsix_player2, loadedmoves[i]);
                    lgsix_savegame->add(loadedmoves[i]);
                    // Turn is now player ones
                    turn = 1;
                }
            // If the rounds ended
            } else {
                //Round end function is called
                roundend();
                // Start of round is set to true
                round_start = true;
                // Whoever has first tile goes first next round
                if(lgsix_player1->getFirst() == true){
                    turn = 1;
                } else {
                    turn = 2;
                }
                // Making sure this doesn't count as a turn
                i = i -1;
            }
        } 
    }
    // This is for when the last move of the save file ends the round
    if(roundover() == true){
        roundend();
        round_start = true;
        if(lgsix_player1->getFirst() == true){
            turn = 1;
        } else {
            turn = 2;
        }
    }
    // If its not a test then this is used
    if(test == false){
        // Game is then created with current factories, players, mosaics and tilebag used as parameters
        ADVSIX* SixLg = new ADVSIX(lgsix_player1, lgsix_player2, lgsix_factory1, lgsix_factory2, lgsix_factory3, lgsix_factory4,
            lgsix_factory5, lgsix_tilebag, lgsix_centralfactory, lgsix_boxlid, lgsix_roundCount, turn, lgsix_savegame, lgsix_random, lgsix_seed);
        int rounds = lgsix_roundCount;
        // Partial round is called
        SixLg->partialRound();
        rounds = rounds +1;
        // If partial round ends game
        if(rounds > 5){
            SixLg->gameend();
        } else {
            // After that the normal game starts 
            while(rounds<=ROUNDS){
                std::cout << "=== ROUND " << rounds << " ===" << std::endl;
                SixLg->round();
                // If round 5 then game is ended
                if (rounds == ROUNDS) {
                    SixLg->roundend();
                    SixLg->gameend();
                // else next round continues
                } else {
                    SixLg->roundend();
                }
                rounds = rounds + 1;
            }
        }
    // If it is a test then the current factories, players and scores are printed
    } else {
        std::cout << std::endl << "=== TEST RESULTS ==="<< std::endl << std::endl;
        std::cout << "Player 1 Name: " << lgsix_player1->getName() << std::endl;
        std::cout << "Player 2 Name: " << lgsix_player2->getName() << std::endl << std::endl;
        std::cout << "Seed: " << lgsix_seed << std::endl << std::endl;
        std::cout << "Tilebag: " << std::endl;
        lgsix_tilebag->print();
        std::cout << std::endl << "BoxLid: " << std::endl;
        lgsix_boxlid->print();
        std::cout << std::endl << std::endl << "Factories: " << std::endl;
        std::cout << "0: ";
        lgsix_centralfactory->printletters();
        std::cout << std::endl << "1: ";
        lgsix_factory1->dfs();
        std::cout << std::endl << "2: ";
        lgsix_factory2->dfs();
        std::cout << std::endl << "3: ";
        lgsix_factory3->dfs();
        std::cout << std::endl << "4: ";
        lgsix_factory4->dfs();
        std::cout << std::endl << "5: ";
        lgsix_factory5->dfs();
        std::cout << std::endl << std::endl << "Score for " << lgsix_player1->getName() << ": " << lgsix_player1->getPoints() << std::endl;
        lgsix_player1->getAdvMosaic()->print();
        std::cout << std::endl << "Score for " << lgsix_player2->getName() << ": " << lgsix_player2->getPoints() << std::endl;
        lgsix_player2->getAdvMosaic()->print();
        std::cout << std::endl;
        std::cout << "=== END TEST ==="<< std::endl << std::endl;
        }
}
// This method just prints out all the players info
void ADVLGSIX::printplayer(Player *player)
{
    std::cout << std::endl
              << "TURN FOR PLAYER: " << player->getName() << std::endl;
    std::cout << "Factories: " << std::endl;
    std::cout << "0: ";
    lgsix_centralfactory->printletters();
    std::cout << std::endl
              << "1: ";
    lgsix_factory1->dfs();
    std::cout << std::endl
              << "2: ";
    lgsix_factory2->dfs();
    std::cout << std::endl
              << "3: ";
    lgsix_factory3->dfs();
    std::cout << std::endl
              << "4: ";
    lgsix_factory4->dfs();
    std::cout << std::endl
              << "5: ";
    lgsix_factory5->dfs();

    std::cout << std::endl
              << std::endl
              << "Mosaic for " << player->getName() << ": " << std::endl;
    player->getAdvMosaic()->print();
}
// This method is used to make the players move
void ADVLGSIX::move(Player *player, std::string move)
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
        chosenfac = lgsix_factory1;
    }
    else if (fac == "2")
    {
        chosenfac = lgsix_factory2;
    }
    else if (fac == "3")
    {
        chosenfac = lgsix_factory3;
    }
    else if (fac == "4")
    {
        chosenfac = lgsix_factory4;
    }
    else if (fac == "5")
    {
        chosenfac = lgsix_factory5;
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
             // Getting the firs index of that storage row
            if (player->getAdvMosaic()->getStorageTile(stoi(row) - 1, i)->getColour() == No_Tile)
            {
                firstIndex = i;
            }
        }
        for (int i = 0; i < 6; i++)
        {
             // Getting the free sports in row
            if (player->getAdvMosaic()->getStorageTile(stoi(row) - 1, i)->getColour() == No_Tile)
            {
                freeSpots++;
            }
        }
    }
    // If not the central factory   
    if (central == false)
    {
        //Checking how many tiles of that colour in factory
        Tile *tileToBeMoved = nullptr;
        int count = 0;
        for(int i = 0; i <chosenfac->multiple(tile_col); i++){
            tileToBeMoved = new Tile(tile_col);
            ++count;
        }
        // Adding other tiles to central factory
        for(int i = 0; i<=TILES_IN_FACTORY; i++){
            if(i != tile_col){
                if(chosenfac->multiple(i) > 0){
                    for(int j = 0; j<chosenfac->multiple(i); j++){
                        Tile *cent_tile = new Tile(i);
                        lgsix_centralfactory->add(cent_tile);
                    }
                }
            }
        }
        //Individual check for orange tile
        if(8 != tile_col){
                if(chosenfac->multiple(8) > 0){
                    for(int j = 0; j<chosenfac->multiple(8); j++){
                        Tile *cent_tile = new Tile(8);
                        lgsix_centralfactory->add(cent_tile);
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
                    player->getAdvMosaic()->addBroken(tileToBeMoved, lgsix_tilebag, lgsix_boxlid, lgsix_random);
                }
            // If all can fit then they go into the row
            } else {
                player->getAdvMosaic()->setStorageRow_first(tileToBeMoved, stoi(row), count, firstIndex);
            }
        // Row 6 means broken, so all tiles are added to broken 
        } else {
            for(int i = 0; i<count; i++){
                player->getAdvMosaic()->addBroken(tileToBeMoved, lgsix_tilebag, lgsix_boxlid, lgsix_random);
            }
        }
        chosenfac->clear();
    }
    // This is the same for the central factory
    // Difference is that extra tiles stay in factory
    else
    {
        if (lgsix_centralfactory->getTile(0)->getColour() == First_Player)
        {
            player->getAdvMosaic()->addBroken(lgsix_centralfactory->getTile(0), lgsix_tilebag, lgsix_boxlid, lgsix_random);
            lgsix_centralfactory->remove(0);
        }
        Tile *tileToBeMoved = nullptr;
        int count = 0;
        // Have to set central factory size now because it will change throughout loop
        int size = lgsix_centralfactory->size();
        // This for loop goes through each tile in the factory
        for (int i = size - 1; i >= 0; i--)
        {
            // Getting the letter of the tile in index i of facotory
            // Checking if that matches the users selected tile
            if (lgsix_centralfactory->getTile(i)->getletter() == chosentile)
            {
                // sets the temporary tile to the tile that will be moved
                // then increments a count of the number of tiles to be moved
                tileToBeMoved = new Tile(*lgsix_centralfactory->getTile(i));
                ++count;

                lgsix_centralfactory->remove(i);
            }
        }
        if(row != "7"){
            // If there are more tiles then spots
            if (count > freeSpots){
                // Whatever can fit goes at the end
                player->getAdvMosaic()->setStorageRow(tileToBeMoved, stoi(row), freeSpots, lastIndex);
                 // The rest go to broken
                for(int i = 0; i < count-freeSpots; i++){
                    player->getAdvMosaic()->addBroken(tileToBeMoved, lgsix_tilebag, lgsix_boxlid, lgsix_random);
                }
            // If all can fit then they go into the row
            } else {
                player->getAdvMosaic()->setStorageRow_first(tileToBeMoved, stoi(row), count, firstIndex);
            }
        } else {
            for(int i = 0; i<count; i++){
                player->getAdvMosaic()->addBroken(tileToBeMoved, lgsix_tilebag, lgsix_boxlid, lgsix_random);
            }
        }
    }
}
// Returns true or false if round is over
bool ADVLGSIX::roundover()
{
    // Sees if all factories are empty
    bool returnval = false;
    if (lgsix_factory1->isEmpty() == true && lgsix_factory2->isEmpty() == true && lgsix_factory3->isEmpty() == true &&
        lgsix_factory4->isEmpty() == true && lgsix_factory5->isEmpty() == true && lgsix_centralfactory->size() == 0)
    {
        returnval = true;
    }
    return returnval;
}

// Method for end of round
void ADVLGSIX::roundend()
{   
    // Round is increased
    ++lgsix_roundCount;
    // Checks if the storage is full, this is used later in mosaic class
    lgsix_player1->getAdvMosaic()->checkIfStorageIsFull();
    for(int i = 0; i< ROW_COL_SIZE_ADV; i++){
        // End of round is called to automatically move mosaics, tile bag is updated
        this->lgsix_tilebag = lgsix_player1->getAdvMosaic()->endOfRound(lgsix_tilebag, lgsix_boxlid, lgsix_random, i);
        // Scoring for this tile moved
        lgsix_player1->setPoints(lgsix_player1->getAdvMosaic()->scoring_tile(lgsix_player1->getPoints(), i));
    }
    // Scoring for broken line
    lgsix_player1->setPoints(lgsix_player1->getAdvMosaic()->scoring_broken(lgsix_player1->getPoints()));
    // Sets whose first
    lgsix_player1->setFirst(lgsix_player1->getAdvMosaic()->checkfirst());
    // Tile bag is updated wth broken
    this->lgsix_tilebag = lgsix_player1->getAdvMosaic()->clearBroken(lgsix_tilebag, lgsix_boxlid, lgsix_random);

    // Same as above
    lgsix_player2->getAdvMosaic()->checkIfStorageIsFull();
    for(int i = 0; i< ROW_COL_SIZE_ADV; i++){
        // End of round is called to automatically move mosaics, tile bag is updated
        this->lgsix_tilebag = lgsix_player2->getAdvMosaic()->endOfRound(lgsix_tilebag, lgsix_boxlid, lgsix_random, i);
        // Scoring for this tile moved
        lgsix_player2->setPoints(lgsix_player2->getAdvMosaic()->scoring_tile(lgsix_player2->getPoints(), i));
    }
    // Scoring for broken line
    lgsix_player2->setPoints(lgsix_player2->getAdvMosaic()->scoring_broken(lgsix_player2->getPoints()));
    // Sets whose first
    lgsix_player2->setFirst(lgsix_player2->getAdvMosaic()->checkfirst());
    // Tile bag is updated wth broken
    this->lgsix_tilebag = lgsix_player2->getAdvMosaic()->clearBroken(lgsix_tilebag, lgsix_boxlid, lgsix_random);

    //If round does not equal 5 then scores are shown
    if(lgsix_roundCount != 6){
        // Resetting factories
        factorySetUp();
    }
    
}

void ADVLGSIX::factorySetUp(){
    // Resetting factories at the end of the round
    if(lgsix_random == true){
        if(lgsix_tilebag->size() < 20){
            while(lgsix_boxlid->size() >0){
                lgsix_tilebag->addBack(lgsix_boxlid->getTile(0));
                lgsix_boxlid->remove(0);
            }
            lgsix_tilebag->shuffle(stoi(lgsix_seed));
        }
    }
    // Adding F tile to central factory
    Tile *Ftile = new Tile(First_Player);
    lgsix_centralfactory->add(Ftile);
    // Filling factories getting first item from tile bag
    for (int i = 0; i < TILES_IN_FACTORY; i++)
    {
        lgsix_factory1->add(lgsix_tilebag->get(0)->getColour());
        lgsix_tilebag->removeFront();
    }
    for (int i = 0; i < TILES_IN_FACTORY; i++)
    {
        lgsix_factory2->add(lgsix_tilebag->get(0)->getColour());
        lgsix_tilebag->removeFront();
    }
    for (int i = 0; i < TILES_IN_FACTORY; i++)
    {
        lgsix_factory3->add(lgsix_tilebag->get(0)->getColour());
        lgsix_tilebag->removeFront();
    }
    for (int i = 0; i < TILES_IN_FACTORY; i++)
    {
        lgsix_factory4->add(lgsix_tilebag->get(0)->getColour());
        lgsix_tilebag->removeFront();
    }
    for (int i = 0; i < TILES_IN_FACTORY; i++)
    {
        lgsix_factory5->add(lgsix_tilebag->get(0)->getColour());
        lgsix_tilebag->removeFront();
    }
}