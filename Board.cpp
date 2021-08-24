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

void Board::Draw(sf::RenderWindow& window, sf::RectangleShape* yellow_box,std::vector<sf::CircleShape>* circle)
{
   
    
    window.clear();
    window.draw(board);
    window.draw(*yellow_box);
    for(int i = 0; i < 12; ++i)
    {
        window.draw(black_sprite[i]);
        window.draw(white_sprite[i]);
    }

    for(int i = 0; i < circle->size(); ++i)
    {
        window.draw(circle->at(i));
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
void Board::Select_Piece(sf::RenderWindow& window, int x_pos, int y_pos, sf::RectangleShape* yellow_box,std::vector<sf::CircleShape>* circle)
{
    int board_matrix_x = y_pos / (width/rows);
    int board_matrix_y = x_pos / (height/cols);


    circle->clear();
    
    std::cout << "Board_Matrix: " << board_matrix_x << " " << board_matrix_y << std::endl;
    //the given square contains a piece
    std::cout << "ARR: " << board_matrix[board_matrix_x][board_matrix_y] << std::endl;
    if(board_matrix[board_matrix_x][board_matrix_y] != 0)
    {

        //highlight 
        
        yellow_box->setSize(sf::Vector2f(width/rows,height/cols));
        yellow_box->setPosition(board_matrix_y * (width/rows), board_matrix_x * (height/cols));
        yellow_box->setFillColor(sf::Color::Yellow);

        

        std::vector<std::pair<int,int>> temp = Valid_Moves(std::pair<int,int>(board_matrix_x,board_matrix_y));
        for(int i = 0; i < temp.size(); ++i)
        {
            std::cout << "temp: " << temp.at(i).first << " " << temp.at(i).second << std::endl;
        }


        for(int i = 0; i < temp.size(); ++i)
        {
            sf::CircleShape temp_circle(20);
            temp_circle.setPosition(temp.at(i).second * (width/rows) + (width/rows/3), temp.at(i).first * (height/cols) + (height/cols/3) );
            sf::Color color(192,192,192);
            temp_circle.setFillColor(color);
            circle->push_back(temp_circle);
        }
        
    }

    //selected square does not contain a piece
    else
    {
        yellow_box -> setSize(sf::Vector2f(0,0));
    }

    
}


//returns all valid moves for the given turn
std::vector<std::pair<int,int>> Board::Valid_Moves()
{
    std::vector<std::pair<int,int>> moves;
    for(int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < cols; ++j)
        {
            std::vector<std::pair<int,int>> temp = Valid_Moves(std::pair<int,int>(i,j));
            moves.insert(moves.end(),temp.begin(),temp.end());
        }
    }
    return moves;
}


//returns valid moves of one piece for the given turn
std::vector<std::pair<int,int>> Board::Valid_Moves(std::pair<int,int> piece)
{
    std::vector<std::pair<int,int>> moves;
    //if it's white turn
    if(turn == true)
    {
        //if board_matrix[][] = -1 it is a normal piece
        if(board_matrix[piece.first][piece.second] == -1)
        {
        
            int capture_counter = 0;

            //pushing back the moves if they are free squares and they are not kings or corner pieces
            if(piece.second > 0 && board_matrix[piece.first - 1][piece.second - 1] == 0)
            {
                moves.push_back(std::pair<int,int>(piece.first - 1, piece.second - 1));
            }

            if( piece.second < 7 && board_matrix[piece.first - 1][piece.second + 1] == 0)
            {
                moves.push_back(std::pair<int,int>(piece.first - 1, piece.second + 1));
            }
            

            //have not implemented double jumps
            if( piece.second > 0 && board_matrix[piece.first - 1][piece.second - 1] == 1)
            {
                int i = piece.first - 2;
                int j = piece.second - 2;
                int line_counter = 1;

                if(board_matrix[i][j] == 0 && capture_counter == 0)
                {
                    moves.clear();
                    moves.push_back(std::pair<int,int>(i,j));
                    capture_counter++;
                }
                else if(board_matrix[i][j] == 0 && capture_counter > 0)
                {
                    moves.push_back(std::pair<int,int>(i,j));
                    capture_counter++;
                }
                


            }
            if( piece.second < 7 && board_matrix[piece.first-1][piece.second + 1] == 1)
            {
                int i = piece.first - 2;
                int j = piece.second + 2;
                int line_counter = 1;

                if(board_matrix[i][j] == 0 && capture_counter == 0)
                {
                    moves.clear();
                    moves.push_back(std::pair<int,int>(i,j));
                    capture_counter++;
                }
                else if(board_matrix[i][j] == 0 && capture_counter > 0)
                {
                    moves.push_back(std::pair<int,int>(i,j));
                    capture_counter++;
                }
            }
            
            
        }


    }

    //for black
    else
    {
        //if board_matrix[][] = -1 it is a normal piece
        if(board_matrix[piece.first][piece.second] == 1)
        {
        
            int capture_counter = 0;

            //pushing back the moves if they are free squares and they are not kings or corner pieces
            if(piece.second > 0 && board_matrix[piece.first + 1][piece.second - 1] == 0)
            {
                moves.push_back(std::pair<int,int>(piece.first + 1, piece.second - 1));
            }
            if( piece.second < 7 && board_matrix[piece.first + 1][piece.second + 1] == 0)
            {
                moves.push_back(std::pair<int,int>(piece.first + 1, piece.second + 1));
            }
            

            //have not implemented double jumps
            if( piece.second > 0 && board_matrix[piece.first + 1][piece.second - 1] == -1)
            {
                int i = piece.first + 2;
                int j = piece.second - 2;
                int line_counter = 1;

                if(board_matrix[i][j] == 0 && capture_counter == 0)
                {
                    moves.clear();
                    moves.push_back(std::pair<int,int>(i,j));
                    capture_counter++;
                }
                else if(board_matrix[i][j] == 0 && capture_counter > 0)
                {
                    moves.push_back(std::pair<int,int>(i,j));
                    capture_counter++;
                }
                


            }
            else if( piece.second < 7 && board_matrix[piece.first+1][piece.second + 1] == -1)
            {
                int i = piece.first + 2;
                int j = piece.second + 2;
                int line_counter = 1;

                if(board_matrix[i][j] == 0 && capture_counter == 0)
                {
                    moves.clear();
                    moves.push_back(std::pair<int,int>(i,j));
                    capture_counter++;
                }
                else if(board_matrix[i][j] == 0 && capture_counter > 0)
                {
                    moves.push_back(std::pair<int,int>(i,j));
                    capture_counter++;
                }
            }
            
            
        }
    }

    return moves;
}