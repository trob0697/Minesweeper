#pragma once

#include "Tile.h"

#include <cmath>
#include <random>
#include <vector>
#include <map>
#include <fstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

class Board{
    public:
        Board();
        void imageMap();
        void initialBoard();
        void counter();
        void setMines();
        void checkAdjacent();
        void revealAdjacent();
        void readBoard(string file);
        void victory();
        void defeat(int y, int x);
        void newGame(string option);
        void setDebug();
        void buildBoard(sf::RenderWindow &window);
        void leftClick(sf::RenderWindow &window);
        void rightClick(sf::RenderWindow &window);
    private:
        int flagCount;
        int mineCount;
        int count;
        bool victorious = false;
        bool defeated = false;
        bool debugMode = false;
        Tile tiles[16][26];
        sf::Sprite revealedTile;
        sf::Sprite thirdDigit;
        sf::Sprite secondDigit;
        sf::Sprite firstDigit;
        sf::Sprite face;
        sf::Sprite debug;
        sf::Sprite test1;
        sf::Sprite test2;
        sf::Sprite test3;
        map<string, sf::Texture> images;
};
