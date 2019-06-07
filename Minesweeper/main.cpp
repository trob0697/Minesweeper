#include "Board.h"

#include <SFML/Window.hpp>

int main(){
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window", sf::Style::Close);
    Board board;
    
    while(window.isOpen()){
        sf::Event event;
        
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
            if(event.type == sf::Event::MouseButtonReleased){
                if(event.mouseButton.button == sf::Mouse::Left){
                    board.leftClick(window);
                }
                if(event.mouseButton.button == sf::Mouse::Right){
                    board.rightClick(window);
                }
            }
        }
        
        window.clear();
        board.buildBoard(window);
        window.display();
    }
    
    return 0;
}
