#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <utility>

class Board
{
    public:
        //constructor class, width and height are the size of the window
        Board();

        void Draw(sf::RenderWindow& window);

        void Draw(sf::RenderWindow& window, sf::RectangleShape* yellow_box,std::vector<sf::CircleShape>* circle);


        //highlights the piece that the user clicks
        void Select_Piece(sf::RenderWindow& window, int x_pos, int y_pos, sf::RectangleShape* yellow_box, std::vector<sf::CircleShape>* circle);

        //gives all valid moves of the players turns
        std::vector<std::pair<int,int>> Valid_Moves();

        //gives valid move of a certain piece
        std::vector<std::pair<int,int>> Valid_Moves(std::pair<int,int> piece);

        void Make_Move(int x_pos, int y_pos,std::pair<int,int> previous_selection);


    private:
        static const int rows = 8;
        static const int cols = 8;
        int height;
        int width;
        int board_matrix[8][8] = 
            {
                {0,1,0,1,0,1,0,1},
                {1,0,1,0,1,0,1,0},
                {0,1,0,1,0,1,0,1},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {-1,0,-1,0,-1,0,-1,0},
                {0,-1,0,-1,0,-1,0,-1},
                {-1,0,-1,0,-1,0,-1,0}
            };

        sf::Texture t1,t2,t3,t4,t5;
        sf::Sprite board;
        sf::Sprite white_sprite[12];
        sf::Sprite black_sprite[12];

        //turn = true == white
        //turn = false == black
        bool turn = true;

};


#endif