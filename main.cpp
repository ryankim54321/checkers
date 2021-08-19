#include "Board.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Checkers by Ryan Kim");

    Board board;

    board.Draw(window);

    sf::RectangleShape yellow_box;
    yellow_box.setSize(sf::Vector2f(0,0));
    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if(event.type == sf::Event::MouseButtonPressed)
            {
                
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    
                    board.Select_Piece(window,pos.x,pos.y, &yellow_box);
                    
                }
            }
            
        }


        if(yellow_box.getSize().x != 0 || yellow_box.getSize().y != 0)
        {
            board.Draw(window,&yellow_box);
        }
        else
        {
            board.Draw(window);
        }
        
    }

    return 0;
}