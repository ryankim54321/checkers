#include "Board.hpp"



//constructor class
Board::Board()
{

    height = 1000;
    width = 1000;

    //loading textures
    t1.loadFromFile("images/PNGs/board.png");
    t2.loadFromFile("images/PNGs/b_king.png");
    t3.loadFromFile("images/PNGs/b_pawn.png");
    t4.loadFromFile("images/PNGs/w_king.png");
    t5.loadFromFile("images/PNGs/w_pawn.png");

    //setting board sprite
    board.setTexture(t1);

    //setting textures for the pieces
    for(int i = 0; i < 12; ++i)
    {
        white_sprite[i].setTexture(t5);
        black_sprite[i].setTexture(t3);
    }
    

    //placing pieaces on board
    int black_counter = 0;
    int white_counter = 0;

    for(int i = 0 ; i < rows; ++i)
    {
        for(int j = 0; j < cols; ++j)
        {
            if(board_matrix[i][j] == 1) //black piece
            {
                black_sprite[black_counter].setPosition( (width/cols) * j + 10, (height/rows) * i);
                black_counter++;
            }
            else if(board_matrix[i][j] == -1) //white pieces
            {
                white_sprite[white_counter].setPosition( (width/cols) * j + 10, (height/rows) * i);
                white_counter++;
            }
        }
    }
    
};

void Board::Draw(sf::RenderWindow& window)
{
    
    window.clear();
    window.draw(board);

    for(int i = 0; i < 12; ++i)
    {
        window.draw(black_sprite[i]);
        window.draw(white_sprite[i]);
    }

    //window.draw(b_pawn);
    window.display();
  
        
}

void Board::Draw(sf::RenderWindow& window, sf::RectangleShape* yellow_box)
{
   
    
    window.clear();
    window.draw(board);
    window.draw(*yellow_box);
    for(int i = 0; i < 12; ++i)
    {
        window.draw(black_sprite[i]);
        window.draw(white_sprite[i]);
    }

    //window.draw(b_pawn);
    window.display();
  
        
}


//select piece
//does not move anything
//highlights the selected piece
//and gray dots on valid moves

//return 1: highlights and shows dots
//return 0: move the piece to designated place
//return 2: no action (empty space)
void Board::Select_Piece(sf::RenderWindow& window, int x_pos, int y_pos, sf::RectangleShape* yellow_box)
{
    int board_matrix_x = x_pos / (width/rows);
    int board_matrix_y = y_pos / (height/cols);



    

    //the given square contains a piece

    if(board_matrix[board_matrix_y][board_matrix_x] != 0)
    {

        
        yellow_box->setSize(sf::Vector2f(width/rows,height/cols));
        yellow_box->setPosition(board_matrix_x * (width/rows), board_matrix_y * (height/cols));
        yellow_box->setFillColor(sf::Color::Yellow);

        
        
    }
    else
    {
        yellow_box -> setSize(sf::Vector2f(0,0));
    }

    
}