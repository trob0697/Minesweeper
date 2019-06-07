#include "Board.h"
#include "Tile.h"

Board::Board(){
    imageMap();
    initialBoard();
    setMines();
    checkAdjacent();
}

void Board::imageMap(){
    map <string, sf::Texture> map;
    
    map["debug"].loadFromFile("images/debug.png");
    map["digits"].loadFromFile("images/digits.png");
    map["happy"].loadFromFile("images/face_happy.png");
    map["lose"].loadFromFile("images/face_lose.png");
    map["win"].loadFromFile("images/face_win.png");
    map["flag"].loadFromFile("images/flag.png");
    map["mine"].loadFromFile("images/mine.png");
    map["1"].loadFromFile("images/number_1.png");
    map["2"].loadFromFile("images/number_2.png");
    map["3"].loadFromFile("images/number_3.png");
    map["4"].loadFromFile("images/number_4.png");
    map["5"].loadFromFile("images/number_5.png");
    map["6"].loadFromFile("images/number_6.png");
    map["7"].loadFromFile("images/number_7.png");
    map["8"].loadFromFile("images/number_8.png");
    map["test1"].loadFromFile("images/test_1.png");
    map["test2"].loadFromFile("images/test_2.png");
    map["test3"].loadFromFile("images/test_3.png");
    map["hidden"].loadFromFile("images/tile_hidden.png");
    map["revealed"].loadFromFile("images/tile_revealed.png");
    
   images = map;
}

void Board::initialBoard(){
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 25; j++){
            tiles[i][j].hidden.setTexture(images["hidden"]);
            tiles[i][j].hidden.setPosition(j * 32, i * 32);
            tiles[i][j].revealed.setTexture(images["revealed"]);
            tiles[i][j].revealed.setPosition(j * 32, i * 32);
            tiles[i][j].flag.setTexture(images["flag"]);
            tiles[i][j].flag.setPosition(j * 32, i * 32);
            tiles[i][j].mine.setTexture(images["mine"]);
            tiles[i][j].mine.setPosition(j * 32, i * 32);
            tiles[i][j].mineCount.setPosition(j * 32, i * 32);
            tiles[i][j].isMine = false;
            tiles[i][j].isFlag = false;
            tiles[i][j].isRevealed = false;
        }
    }
    
    revealedTile.setTexture(images["revealed"]);
    
    thirdDigit.setTexture(images["digits"]);
    thirdDigit.setTextureRect(sf::IntRect(0, 0, 21, 32));
    thirdDigit.setPosition(0, 512);
    
    secondDigit.setTexture(images["digits"]);
    secondDigit.setTextureRect(sf::IntRect(102, 0, 21, 32));
    secondDigit.setPosition(20, 512);
    
    firstDigit.setTexture(images["digits"]);
    firstDigit.setTextureRect(sf::IntRect(0, 0, 21, 32));
    firstDigit.setPosition(40, 512);
    
    face.setTexture(images["happy"]);
    face.setPosition(368, 512);
    debug.setTexture(images["debug"]);
    debug.setPosition(496, 512);
    test1.setTexture(images["test1"]);
    test1.setPosition(560, 512);
    test2.setTexture(images["test2"]);
    test2.setPosition(624, 512);
    test3.setTexture(images["test3"]);
    test3.setPosition(688, 512);
}

void Board::counter(){
    count = mineCount - flagCount;
    if(count >= 0){
        thirdDigit.setTextureRect(sf::IntRect(21 * (count / 100), 0, 21, 32));
        secondDigit.setTextureRect(sf::IntRect(21 * (count / 10), 0, 21, 32));
        firstDigit.setTextureRect(sf::IntRect(21 * (count % 10), 0, 21, 32));
    }
    else{
        int absCount = abs(int(count));
        thirdDigit.setTextureRect(sf::IntRect(208, 0, 21, 32));
        secondDigit.setTextureRect(sf::IntRect(21 * (absCount / 10), 0, 21, 32));
        firstDigit.setTextureRect(sf::IntRect(21 * (absCount % 10), 0, 21, 32));
    }
}

void Board::setMines(){
    for(int i = 0; i < 50; i++){
        std::random_device mt;
        std::mt19937 gen(mt());
        std::uniform_int_distribution<> numberY(0, 15);
        short y =  (short)numberY(gen);
        
        std::uniform_int_distribution<> numberX(0, 24);
        short x =   (short)numberX(gen);

        if(!tiles[y][x].isMine){
            tiles[y][x].isMine = true;
            mineCount++;
        }
        else{
            i--;
        }
    }
}

void Board::checkAdjacent(){
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 25; j++){
            if(i - 1 >= 0 && j - 1 >= 0){
                tiles[i][j].neighbors[0] = &tiles[i - 1][j - 1];
            }
            else{
                tiles[i][j].neighbors[0] = nullptr;
            }
            
            if(i - 1 >= 0){
                tiles[i][j].neighbors[1] = &tiles[i - 1][j];
            }
            else{
                tiles[i][j].neighbors[1] = nullptr;
            }
            
            if(i - 1 >= 0 && j + 1 < 25){
                tiles[i][j].neighbors[3] = &tiles[i - 1][j + 1];
            }
            else{
                tiles[i][j].neighbors[3] = nullptr;
            }
            
            if(j - 1 >= 0){
                tiles[i][j].neighbors[2] = &tiles[i][j - 1];
            }
            else{
                tiles[i][j].neighbors[2] = nullptr;
            }
            
            if(j + 1 < 25){
                tiles[i][j].neighbors[4] = &tiles[i][j + 1];
            }
            else{
                tiles[i][j].neighbors[4] = nullptr;
            }
            
            if(i + 1 < 16 && j - 1 >= 0){
                tiles[i][j].neighbors[5] = &tiles[i + 1][j - 1];
            }
            else{
                tiles[i][j].neighbors[5] = nullptr;
            }
            
            if(i + 1 < 16){
                tiles[i][j].neighbors[6] = &tiles[i + 1][j];
            }
            else{
                tiles[i][j].neighbors[6] = nullptr;
            }
            
            if(i + 1 < 16 && j + 1 < 25){
                tiles[i][j].neighbors[7] = &tiles[i + 1][j + 1];
            }
            else{
                tiles[i][j].neighbors[7] = nullptr;
            }
        }
    }
    
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 25; j++){
            for(int k = 0; k < 8; k++){
                if(tiles[i][j].neighbors[k]->isMine && !(tiles[i][j].neighbors[k] == nullptr)){
                    tiles[i][j].neighbMines++;
                }
            }
        }
    }
    
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 25; j++){
            if(!tiles[i][j].isMine){
                if(tiles[i][j].neighbMines == 0){
                    tiles[i][j].mineCount.setTexture(images["revealed"]);
                }
                if(tiles[i][j].neighbMines == 1){
                    tiles[i][j].mineCount.setTexture(images["1"]);
                }
                if(tiles[i][j].neighbMines == 2){
                    tiles[i][j].mineCount.setTexture(images["2"]);
                }
                if(tiles[i][j].neighbMines == 3){
                    tiles[i][j].mineCount.setTexture(images["3"]);
                }
                if(tiles[i][j].neighbMines == 4){
                    tiles[i][j].mineCount.setTexture(images["4"]);
                }
                if(tiles[i][j].neighbMines == 5){
                    tiles[i][j].mineCount.setTexture(images["5"]);
                }
                if(tiles[i][j].neighbMines == 6){
                    tiles[i][j].mineCount.setTexture(images["6"]);
                }
                if(tiles[i][j].neighbMines == 7){
                    tiles[i][j].mineCount.setTexture(images["7"]);
                }
                if(tiles[i][j].neighbMines == 8){
                    tiles[i][j].mineCount.setTexture(images["8"]);
                }
            }
        }
    }
}

void Board::revealAdjacent(){
    for(int run = 0; run < 400; run++){
        for(int i = 0; i < 16; i++){
            for(int j = 0; j < 25; j++){
                if(tiles[i][j].isRevealed && !tiles[i][j].isMine && (tiles[i][j].neighbMines == 0)){
                    for(int k = 0; k < 8; k++){
                        if((tiles[i][j].neighbors[k]->neighbMines == 0) && !(tiles[i][j].neighbors[k] == nullptr)){
                            tiles[i][j].neighbors[k]->isRevealed = true;
                        }
                    }
                }
            }
        }
    }
    
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 25; j++){
            if(tiles[i][j].isRevealed && !tiles[i][j].isMine && (tiles[i][j].neighbMines == 0)){
                for(int k = 0; k < 8; k++){
                    if(!(tiles[i][j].neighbors[k]->isMine) && !(tiles[i][j].neighbors[k] == nullptr)){
                        tiles[i][j].neighbors[k]->isRevealed = true;
                    }
                }
            }
        }
    }
    
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 25; j++){
            if(tiles[i][j].isFlag){
                tiles[i][j].isRevealed = false;
            }
        }
    }
}

void Board::readBoard(string file){
    fstream f(file);
    string line;
    if(f.is_open()){
        for(int i = 0; i < 16; i++){
            getline(f, line);
            for(int j = 0; j < 25; j++) {
                if(line[j] == '1'){
                    tiles[i][j].isMine = true;
                    mineCount++;
                }
            }
        }
    }
}

void Board::victory(){
    int winCondition1 = 0;
    int winCondition2 = 0;
    
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 25; j++){
            if(!tiles[i][j].isMine && tiles[i][j].isRevealed){
                winCondition1++;
            }
            if(tiles[i][j].isMine && tiles[i][j].isFlag){
                winCondition2++;
            }
        }
    }
    
    if(winCondition1 == (400 - mineCount) || (winCondition2 == mineCount && count == 0)){
        victorious = true;
        face.setTexture(images["win"]);
    }
}

void Board::defeat(int y, int x){
    defeated = true;
    debugMode = true;
    setDebug();
    face.setTexture(images["lose"]);
    tiles[y][x].revealed.setColor(sf::Color::Red);
}

void Board::newGame(string option){
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 25; j++){
            tiles[i][j].revealed.setColor(revealedTile.getColor());
            tiles[i][j].isMine = false;
            tiles[i][j].isFlag = false;
            tiles[i][j].isRevealed = false;
            tiles[i][j].neighbMines = 0;
            tiles[i][j].mineCount.setTexture(images["revealed"]);
        }
    }
    
    flagCount = 0;
    mineCount = 0;
    victorious = false;
    defeated = false;
    debugMode = false;
    
    if(option == "New Game"){
        setMines();
    }
    if(option == "Test1"){
        readBoard("boards/testboard1.brd");
    }
    if(option == "Test2"){
        readBoard("boards/testboard2.brd");
    }
    if(option == "Test3"){
        readBoard("boards/testboard3.brd");
    }
    
    checkAdjacent();
    face.setTexture(images["happy"]);
}

void Board::setDebug(){
    if(debugMode){
        for(int i = 0; i < 16; i++){
            for(int j = 0; j < 25; j++){
                if(tiles[i][j].isMine){
                    tiles[i][j].isRevealed = true;
                }
            }
        }
    }
    else{
        for(int i = 0; i < 16; i++){
            for(int j = 0; j < 25; j++){
                if(tiles[i][j].isMine){
                    tiles[i][j].isRevealed = false;
                }
            }
        }
    }
}

void Board::buildBoard(sf::RenderWindow &window){
    counter();
    victory();
    setDebug();
    
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 25; j++){
            if(!tiles[i][j].isRevealed){
                window.draw(tiles[i][j].hidden);
            }
            if(tiles[i][j].isRevealed && !tiles[i][j].isFlag){
                window.draw(tiles[i][j].revealed);
                window.draw(tiles[i][j].mineCount);
            }
            if(tiles[i][j].isFlag){
                window.draw(tiles[i][j].hidden);
                window.draw(tiles[i][j].flag);
            }
            if(tiles[i][j].isMine && tiles[i][j].isRevealed && !tiles[i][j].isFlag){
                window.draw(tiles[i][j].revealed);
                window.draw(tiles[i][j].mine);
            }
        }
    }
    window.draw(thirdDigit);
    window.draw(secondDigit);
    window.draw(firstDigit);
    window.draw(face);
    window.draw(debug);
    window.draw(test1);
    window.draw(test2);
    window.draw(test3);
}

void Board::leftClick(sf::RenderWindow &window){
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    double x = mousePosition.x / 32.0;
    double y = mousePosition.y / 32.0;
    
    if(!defeated && !victorious){
        //Game Board Click
        if(y < 16 && x < 25){
            if(!tiles[int(y)][int(x)].isRevealed && !tiles[int(y)][int(x)].isFlag){
                tiles[int(y)][int(x)].isRevealed = true;
                revealAdjacent();
            }
        }
        
        //Game Board Click Mine
        if(y < 16 && x < 25){
            if(tiles[int(y)][int(x)].isMine && !tiles[int(y)][int(x)].isFlag){
                defeat(y,x);
            }
        }
        
        //NewG Game
        if(x >= 11.5 && x < 13.5 && y >= 16 && y < 18){
            newGame("New Game");
        }
        
        //Debug Mode Click
        if(x >= 15.5 && x < 17.5 && y >= 16 && y < 18){
            if(!debugMode)
                debugMode = true;
            else
                debugMode = false;
        }
        
        //Test1
        if(x >= 17.5 && x < 19.5 && y >= 16 && y < 18){
            newGame("Test1");
        }
        
        //Test2
        if(x >= 19.5 && x < 21.5 && y >= 16 && y < 18){
            newGame("Test2");
        }
        
        //Test3
        if(x >= 21.5 && x < 23.5 && y >= 16 && y < 18){
            newGame("Test3");
        }
    }
    
    if(defeated || victorious){
        if(x >= 11.5 && x < 13.5 && y >= 16 && y < 18){
            newGame("New Game");
        }
    }
}

void Board::rightClick(sf::RenderWindow &window){
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    int x = mousePosition.x / 32.0;
    int y = mousePosition.y / 32.0;
    if(!defeated && !victorious){
        if(y < 16 && x < 25){
            if(/*!tiles[y][x].isRevealed &&*/ !tiles[y][x].isFlag){
                tiles[y][x].isFlag = true;
                flagCount++;
            }
            else{
                tiles[y][x].isFlag = false;
                flagCount--;
            }
        }
    }
}
