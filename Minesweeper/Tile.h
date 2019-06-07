#pragma once

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

class Tile{
    public:
        sf::Sprite hidden;
        sf::Sprite revealed;
        sf::Sprite flag;
        sf::Sprite mine;
        sf::Sprite mineCount;
        Tile* neighbors[8];
        int neighbMines = 0;
        bool isMine = false;
        bool isFlag = false;
        bool isRevealed = false;
    private:
};
