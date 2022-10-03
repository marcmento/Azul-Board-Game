#include "Adv_Load_G.h"

// Creating new objects at start of game
ADVLG::ADVLG() {
    this->advlg_player1 = new Player("no name", 0);
    this->advlg_player2 = new Player("no name1", 0);
    this->advlg_factory1 = new BST();
    this->advlg_factory2 = new BST();
    this->advlg_factory3 = new BST();
    this->advlg_factory4 = new BST();
    this->advlg_factory5 = new BST();
    this->advlg_centralfactory = new CentralFactory();
    this->advlg_tilebag = new LinkedList();
    this->advlg_savegame = new SaveGame();
    this->advlg_boxlid = new BoxLid();
    this->advlg_roundCount = ROUND_START;
    this->advlg_random = false;
    this->advlg_seed = "no";
}
// Deconstructor removes all moves from vector and all other objects
ADVLG::~ADVLG(){
    while(loadedmoves.size() != 0){
        loadedmoves.pop_back();
    }
    delete advlg_player1;
    delete advlg_player2;
    delete advlg_factory1;
    delete advlg_factory2;
    delete advlg_factory3;
    delete advlg_factory4;
    delete advlg_factory5;
    delete advlg_centralfactory;
    delete advlg_tilebag;
    delete advlg_savegame;
    delete advlg_boxlid;
}

void ADVLG::readfile(std::string filename){
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

int ADVLG::size(){
    // Returns the size of the moves vector
    return loadedmoves.size();
}

void ADVLG::setup(){
    // Goes through the inital tile bag in saved game and adds them to tile bag
    for(int i = 0; i<loadedmoves[2].length(); i++){
        // If letter corresponds to colour then new tile is created and added to the back of the tilebag
        if(loadedmoves[2].substr(i,1) == "R"){
            Tile* tile_red = new Tile(Red);
            advlg_tilebag->addBack(tile_red);
        } else if(loadedmoves[2].substr(i,1) == "L"){
            Tile* tile_LB = new Tile(Light_Blue);
            advlg_tilebag->addBack(tile_LB);
        } else if(loadedmoves[2].substr(i,1) == "U"){
            Tile* tile_Black = new Tile(Black);
            advlg_tilebag->addBack(tile_Black);
        } else if(loadedmoves[2].substr(i,1) == "B"){
            Tile* tile_DB = new Tile(Dark_Blue);
            advlg_tilebag->addBack(tile_DB);
        } else if (loadedmoves[2].substr(i,1) == "Y"){
            Tile* tile_Yellow = new Tile(Yellow);
            advlg_tilebag->addBack(tile_Yellow);
        } else if (loadedmoves[2].substr(i,1) == "O"){
            Tile* tile_Orange = new Tile(Orange);
            advlg_tilebag->addBack(tile_Orange);
        }
    } 
    // If there is a seed then random is turned on
    if(loadedmoves[1] != "no"){
        advlg_seed = loadedmoves[1];
        advlg_random = true;
    }
    // Inital tile bag is set
    advlg_savegame->changeInital(loadedmoves[2]);
    // Players names are set from file
    advlg_player1->changeName(loadedmoves[3]);
    advlg_player2->changeName(loadedmoves[4]);
    // Player 1 goes first
    advlg_player1->setFirst(true);
}
// This method goes through all turns made and simulates them
void ADVLG::round(bool test)
{   
    // Factories are set up
    factorySetUp();
    // Signifies the start of a round
    bool round_start = true;
    // Determines whose turn it is
    int turn = 0;
    // First player marker determines who gets the first turn of the round
    if(advlg_player1->getFirst() == true){
        turn = 1;
    } else {
        turn = 2;
    }
    // This for loop goes through all moves and makes them
    for(int i = 5; i < loadedmoves.size(); i++){
        // If there is a blank line then it is ignored
        if(loadedmoves[i].substr(START_INPUT, 5) != ""){
            // If rounds not over a move is made
            if(roundover() == false){
                // If player ones first and the rounds just started
                if(advlg_player1->getFirst() == true && round_start == true){
                    move(advlg_player1, loadedmoves[i]);
                    advlg_savegame->add(loadedmoves[i]);
                    round_start = false;
                    turn = 2;
                // If players two first and the rounds just started
                } else if(advlg_player2->getFirst() == true && round_start == true){
                    move(advlg_player2, loadedmoves[i]);
                    advlg_savegame->add(loadedmoves[i]);
                    round_start = false;
                    turn = 1;
                // If its not start of round then whoevers turn it is goes
                } else if (turn == 1){
                    // Move is called
                    move(advlg_player1, loadedmoves[i]);
                    // Move is saved so if the game is saved again after its loaded the original moves are still saved
                    advlg_savegame->add(loadedmoves[i]);
                    // Turn is then player two's
                    turn = 2;
                } else if (turn == 2){
                    move(advlg_player2, loadedmoves[i]);
                    advlg_savegame->add(loadedmoves[i]);
                    // Turn is now player ones
                    turn = 1;
                }
            // If the rounds ended
            } else {
                //Round end function is called
                i = roundend(i);
                // Start of round is set to true
                round_start = true;
                // Whoever has first tile goes first next round
                if(advlg_player1->getFirst() == true){
                    turn = 1;
                } else {
                    turn = 2;
                }
                // Making sure this doesn't count as a turn
            }
        } 
    }
    // If its not a test then game is started up
    if(test == false){
        // Game is then created with current factories, players, mosaics and tilebag used as parameters
        ADVG* ng_advlg = new ADVG(advlg_player1, advlg_player2, advlg_factory1, advlg_factory2, advlg_factory3, advlg_factory4,
            advlg_factory5, advlg_tilebag, advlg_centralfactory, advlg_boxlid, advlg_roundCount, turn, advlg_savegame, advlg_random, advlg_seed);
        int rounds = advlg_roundCount;
        // Partial round is called
        ng_advlg->partialRound();
        rounds = rounds +1;
        // If game is over after partial round
        if(rounds > 5){
            ng_advlg->gameend();
        } else {
            // After that the normal game starts 
            while(rounds<=ROUNDS){
                std::cout << "=== ROUND " << rounds << " ===" << std::endl;
                ng_advlg->round();
                // If round 5 then game is ended
                if (rounds == ROUNDS) {
                    ng_advlg->roundend();
                    ng_advlg->gameend();
                // else next round continues
                } else {
                    ng_advlg->roundend();
                }
                rounds = rounds + 1;
            }
        }
    // If it is a test then the current factories, players and scores are printed
    } else {
        std::cout << std::endl << "=== TEST RESULTS ==="<< std::endl << std::endl;
        std::cout << "Player 1 Name: " << advlg_player1->getName() << std::endl;
        std::cout << "Player 2 Name: " << advlg_player2->getName() << std::endl << std::endl;
        std::cout << "Seed: " << advlg_seed << std::endl << std::endl;
        std::cout << "Tilebag: " << std::endl;
        advlg_tilebag->print();
        std::cout << std::endl << "BoxLid: " << std::endl;
        advlg_boxlid->print();
        std::cout << std::endl << std::endl << "Factories: " << std::endl;
        std::cout << "0: ";
        advlg_centralfactory->printletters();
        std::cout << std::endl << "1: ";
        advlg_factory1->dfs();
        std::cout << std::endl << "2: ";
        advlg_factory2->dfs();
        std::cout << std::endl << "3: ";
        advlg_factory3->dfs();
        std::cout << std::endl << "4: ";
        advlg_factory4->dfs();
        std::cout << std::endl << "5: ";
        advlg_factory5->dfs();
        std::cout << std::endl << std::endl << "Score for " << advlg_player1->getName() << ": " << advlg_player1->getPoints() << std::endl;
        advlg_player1->getMosaic()->print();
        std::cout << std::endl << "Score for " << advlg_player2->getName() << ": " << advlg_player2->getPoints() << std::endl;
        advlg_player2->getMosaic()->print();
        std::cout << std::endl;
        std::cout << "=== END TEST ==="<< std::endl << std::endl;
        }
}
// This method just prints out all the players info
void ADVLG::printplayer(Player *player)
{
    std::cout << std::endl
              << "TURN FOR PLAYER: " << player->getName() << std::endl;
    std::cout << "Factories: " << std::endl;
    std::cout << "0: ";
    advlg_centralfactory->printletters();
    std::cout << std::endl
              << "1: ";
    advlg_factory1->dfs();
    std::cout << std::endl
              << "2: ";
    advlg_factory2->dfs();
    std::cout << std::endl
              << "3: ";
    advlg_factory3->dfs();
    std::cout << std::endl
              << "4: ";
    advlg_factory4->dfs();
    std::cout << std::endl
              << "5: ";
    advlg_factory5->dfs();
    std::cout << std::endl << std::endl 
            << "Mosaic for " << player->getName() << ": " << std::endl;
    player->getMosaic()->print();
}
// This method is used to make the players move
void ADVLG::move(Player *player, std::string move)
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
        chosenfac = advlg_factory1;
    }
    else if (fac == "2")
    {
        chosenfac = advlg_factory2;
    }
    else if (fac == "3")
    {
        chosenfac = advlg_factory3;
    }
    else if (fac == "4")
    {
        chosenfac = advlg_factory4;
    }
    else if (fac == "5")
    {
        chosenfac = advlg_factory5;
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
        }
    }
    int lastIndex = -1;
    int firstIndex = -1;
    int freeSpots = 0;
    // Unless row is 6 which means tiles go to broken
    if(row != "6"){
        for (int i = TILES_IN_FACTORY; i>= 0; i--)
        {
            //Getting the last index of that storage row, if a tiles already there
            if (player->getMosaic()->getStorageTile(stoi(row) - 1, i)->getColour() == No_Tile)
            {
                lastIndex = i;
            }
        }
        for (int i = 0; i < ROW_COL_SIZE; i++)
        {
            //Getting the first index of that storage row
            if (player->getMosaic()->getStorageTile(stoi(row) - 1, i)->getColour() == No_Tile)
            {
                firstIndex = i;
            }
        }
        for (int i = 0; i < ROW_COL_SIZE; i++)
        {
            // Getting the free spots in the row
            if (player->getMosaic()->getStorageTile(stoi(row) - 1, i)->getColour() == No_Tile)
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
                        advlg_centralfactory->add(cent_tile);
                    }
                }
            }
        }
        // moves tile from factory to storage
        if(row != "6"){
            // If there are more tiles then spots
            if (count > freeSpots){
                // Whatever can fit goes at the end
                player->getMosaic()->setStorageRow(tileToBeMoved, stoi(row), freeSpots, lastIndex);
                 // The rest go to broken
                for(int i = 0; i < count-freeSpots; i++){
                    player->getMosaic()->addBroken(tileToBeMoved, advlg_tilebag, advlg_boxlid, advlg_random);
                }
            // If all can fit then they go into the row
            } else {
                player->getMosaic()->setStorageRow_first(tileToBeMoved, stoi(row), count, firstIndex);
            }
        // Row 6 means broken, so all tiles are added to broken 
        } else {
            for(int i = 0; i<count; i++){
                player->getMosaic()->addBroken(tileToBeMoved, advlg_tilebag, advlg_boxlid, advlg_random);
            }
        }
        chosenfac->clear();
    }
    // This is the same for the central factory
    // Difference is that extra tiles stay in factory
    else
    {
        if (advlg_centralfactory->getTile(0)->getColour() == First_Player)
        {
            player->getMosaic()->addBroken(advlg_centralfactory->getTile(0), advlg_tilebag, advlg_boxlid, advlg_random);
            advlg_centralfactory->remove(0);
        }
        Tile *tileToBeMoved = nullptr;
        int count = 0;
        // Have to set central factory size now because it will change throughout loop
        int size = advlg_centralfactory->size();
        // This for loop goes through each tile in the factory
        for (int i = size - 1; i >= 0; i--)
        {
            // Getting the letter of the tile in index i of facotory
            // Checking if that matches the users selected tile
            if (advlg_centralfactory->getTile(i)->getletter() == chosentile)
            {
                // sets the temporary tile to the tile that will be moved
                // then increments a count of the number of tiles to be moved
                tileToBeMoved = new Tile(*advlg_centralfactory->getTile(i));
                ++count;

                advlg_centralfactory->remove(i);
            }
        }
        if(row != "6"){
            // If there are more tiles then spots
            if (count > freeSpots){
                // Whatever can fit goes at the end
                player->getMosaic()->setStorageRow(tileToBeMoved, stoi(row), freeSpots, lastIndex);
                 // The rest go to broken
                for(int i = 0; i < count-freeSpots; i++){
                    player->getMosaic()->addBroken(tileToBeMoved, advlg_tilebag, advlg_boxlid, advlg_random);
                }
            // If all can fit then they go into the row
            } else {
                player->getMosaic()->setStorageRow_first(tileToBeMoved, stoi(row), count, firstIndex);
            }
        } else {
            for(int i = 0; i<count; i++){
                player->getMosaic()->addBroken(tileToBeMoved, advlg_tilebag, advlg_boxlid, advlg_random);
            }
        }
    }
}
// Returns true or false if round is over
bool ADVLG::roundover()
{
    // Sees if all factories are empty
    bool returnval = false;
    if (advlg_factory1->isEmpty() == true && advlg_factory2->isEmpty() == true && advlg_factory3->isEmpty() == true &&
        advlg_factory4->isEmpty() == true && advlg_factory5->isEmpty() == true && advlg_centralfactory->size() == 0)
    {
        returnval = true;
    }
    return returnval;
}

// Method for end of round
int ADVLG::roundend(int j){ 
    // J is the number of moves the game is up to as this method is going to go through more moves
    int returnval = j;  
    // Round is increased
    ++advlg_roundCount;
    //Manual moves are made
    for(int i = 0; i<ROW_COL_SIZE; i++){
        if(advlg_player1->getMosaic()->returnIfStorageIsFull(i+1) == true){
            manual(advlg_player1, loadedmoves[returnval], i);
            returnval++;
        }
    }
    // Scoring for broken line
    advlg_player1->setPoints(advlg_player1->getMosaic()->scoring_broken(advlg_player1->getPoints()));
    // Sets whose first
    advlg_player1->setFirst(advlg_player1->getMosaic()->checkfirst());
    // Tile bag is updated wth broken
    this->advlg_tilebag = advlg_player1->getMosaic()->clearBroken(advlg_tilebag, advlg_boxlid, advlg_random);

    // Same as above
    for(int i = 0; i<ROW_COL_SIZE; i++){
        if(advlg_player2->getMosaic()->returnIfStorageIsFull(i+1) == true){
            manual(advlg_player2, loadedmoves[returnval], i);
            returnval++;
        }
    }
    // Scoring for broken line
    advlg_player2->setPoints(advlg_player2->getMosaic()->scoring_broken(advlg_player2->getPoints()));
    // Sets whose first
    advlg_player2->setFirst(advlg_player2->getMosaic()->checkfirst());
    // Tile bag is updated wth broken
    this->advlg_tilebag = advlg_player2->getMosaic()->clearBroken(advlg_tilebag, advlg_boxlid, advlg_random);

    //If round does not equal 5 then scores are shown
    if(advlg_roundCount != 6){
        // Resetting factories
        factorySetUp();
    }
    // Returning the new index for the moves list
    returnval--;
    return returnval;
}
// Method for manual move
void ADVLG::manual(Player* player, std::string move, int i){
    int col = 0;
    if(move == "1" || move == "2" || move == "3" || move == "4" || move == "5"){
        col = stoi(move);
        //Tile is moved
        if(player->getMosaic()->mosaicSpotTaken(i, col-1) == false){
            advlg_savegame->add(move);
        }
    } else if(move == "6"){
        // Tile is for broken row
        col = stoi(move);
        advlg_savegame->add(move);  
    } 
    // If broken chosen all tiles moved to broken
    if(col == 6){
        int count = 0;
        for(int j = 0; j < ROW_COL_SIZE; j++){
            if(player->getMosaic()->getStorageTile(i,j)->isColoured() == true){
                player->getMosaic()->addBroken(player->getMosaic()->getStorageTile(i,j), advlg_tilebag, advlg_boxlid, advlg_random);
                count++;
            }
        }
        Tile* remove = new Tile(No_Tile);
        player->getMosaic()->setStorageRow_first(remove, i+1, count, 4);  
    // Else move is made
    } else {
        this->advlg_tilebag = player->getMosaic()->manualMove(i, col-1, advlg_tilebag, advlg_boxlid, advlg_random);
        player->setPoints(player->getMosaic()->manualScoring(i, col-1, player->getPoints()));
    }
}

void ADVLG::factorySetUp(){
    // Resetting factories at the end of the round //
    if(advlg_tilebag->size() < 20){
        while(advlg_boxlid->size() >0){
            advlg_tilebag->addBack(advlg_boxlid->getTile(0));
            advlg_boxlid->remove(0);
        }
        advlg_tilebag->shuffle(stoi(advlg_seed));
    }
    // Adding F tile to central factory
    Tile *Ftile = new Tile(First_Player);
    advlg_centralfactory->add(Ftile);
    // Filling factories getting first item from tile bag
    for (int i = 0; i < TILES_IN_FACTORY; i++)
    {
        advlg_factory1->add(advlg_tilebag->get(0)->getColour());
        advlg_tilebag->removeFront();
    }
    for (int i = 0; i < TILES_IN_FACTORY; i++)
    {
        advlg_factory2->add(advlg_tilebag->get(0)->getColour());
        advlg_tilebag->removeFront();
    }
    for (int i = 0; i < TILES_IN_FACTORY; i++)
    {
        advlg_factory3->add(advlg_tilebag->get(0)->getColour());
        advlg_tilebag->removeFront();
    }
    for (int i = 0; i < TILES_IN_FACTORY; i++)
    {
        advlg_factory4->add(advlg_tilebag->get(0)->getColour());
        advlg_tilebag->removeFront();
    }
    for (int i = 0; i < TILES_IN_FACTORY; i++)
    {
        advlg_factory5->add(advlg_tilebag->get(0)->getColour());
        advlg_tilebag->removeFront();
    }
}