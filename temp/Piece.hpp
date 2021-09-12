#ifndef PIECE_HPP
#define PIECE_HPP

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <utility>

class Piece
{
    public: 
        Piece(int y, int x,bool color, int identifier, int board_size, sf::Texture* piece_texture);

        int Get_Identifier();

        void Make_King(sf::Texture king_texture);

        //returns the calculated position on the board_size;
        std::pair<int,int> Change_Position(int x, int y);

        //get Location on the board
        std::pair<int,int> Get_Location();

        //get x/y
        std::pair<int,int> Get_Coordinates();
        
        bool Get_Color();

        sf::Sprite Get_Sprite();

        bool Is_King();

        bool Capture();


    private:

        //decides whether or not this piece is a king
        bool is_king;

        //if true is white
        //false is black
        bool color;
        
        //x/y are the x and y on the board matrix array
        int x;
        int y;

        //Board_x board_y are the position according to the actual board
        int board_y;
        int board_x;
        int board_size;

        //number to find this piece better 
        int identifier;

        //the sfml object to represent the piece
        //sf::CircleShape circle_piece;
        sf::Sprite piece;

        bool captures;
};


#endif