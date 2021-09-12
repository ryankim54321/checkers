#include "Piece.hpp"

Piece::Piece(int y, int x,bool color, int identifier, int board_size, sf::Texture* piece_texture)
{

    //initializing the given arguments
    this->x = x;
    this->y = y;
    this->color = color;
    this -> identifier = identifier;
    this -> board_size = board_size;

    piece.setTexture(*piece_texture);

    is_king = false;

    //setting position board position

    
    board_y = y * (board_size / 8);
    board_x = x * (board_size / 8);

    piece.setOrigin(-10,0);
    piece.setPosition(board_x, board_y);


    captures = false;

}

int Piece::Get_Identifier()
{
    return identifier;
}

void Piece::Make_King(sf::Texture king_texture)
{
    piece.setTexture(king_texture);
    is_king = true;

}

//returns the calculated position on the board_size;
std::pair<int,int> Piece::Change_Position(int x, int y)
{
    this-> x = y;
    this -> y = x;

    board_x = this->x * (board_size / 8);
    board_y = this ->y * (board_size / 8);

    
    piece.setPosition(board_x, board_y);    

    return std::pair<int,int>(board_x,board_y);
}

//get Location on the board
std::pair<int,int> Piece::Get_Location()
{
    return std::pair<int,int>(board_x,board_y);
}

//get x/y
std::pair<int,int> Piece::Get_Coordinates()
{
    return std::pair<int,int>(x,y);
}

bool Piece::Get_Color()
{
    return color;
}

sf::Sprite Piece::Get_Sprite()
{
    return piece;
}

bool Piece::Is_King()
{
    return is_king;
}

bool Piece::Capture()
{
    return captures;
}