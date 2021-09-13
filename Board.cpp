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

    

    for(int i = 0 ; i < rows; ++i)
    {
        for(int j = 0; j < cols; ++j)
        {

            
            if(board_matrix[i][j] == 1) //black piece
            {

                
                sf::Sprite sprite;
                sprite.setTexture(t3);
                sprite.setPosition( (width/cols) * j + 10, (height/rows) * i);
                black_sprite.insert({{i,j},sprite});
            }
            else if(board_matrix[i][j] == -1) //white pieces
            {

                sf::Sprite sprite;
                sprite.setTexture(t5);
                sprite.setPosition( (width/cols) * j + 10, (height/rows) * i);
                white_sprite.insert({{i,j},sprite});
            }
        }
    }
    
};

void Board::Draw(sf::RenderWindow& window)
{
    
    window.clear();
    window.draw(board);

    for (std::map<std::pair<int,int>,sf::Sprite>::iterator it=white_sprite.begin(); it!=white_sprite.end(); ++it)
    {
        window.draw(it->second);
    }

    for (std::map<std::pair<int,int>,sf::Sprite>::iterator it=black_sprite.begin(); it!=black_sprite.end(); ++it)
    {
        window.draw(it->second);
    }

    //window.draw(b_pawn);
    window.display();
  
        
}

void Board::Draw(sf::RenderWindow& window, sf::RectangleShape* yellow_box,std::vector<sf::CircleShape>* circle)
{
   
    
    window.clear();
    window.draw(board);
    window.draw(*yellow_box);
    for (std::map<std::pair<int,int>,sf::Sprite>::iterator it=white_sprite.begin(); it!=white_sprite.end(); ++it)
    {
        window.draw(it->second);
    }

    for (std::map<std::pair<int,int>,sf::Sprite>::iterator it=black_sprite.begin(); it!=black_sprite.end(); ++it)
    {
        window.draw(it->second);
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
    

    if(board_matrix[board_matrix_x][board_matrix_y] != 0)
    {

        //highlight 
        
        yellow_box->setSize(sf::Vector2f(width/rows,height/cols));
        yellow_box->setPosition(board_matrix_y * (width/rows), board_matrix_x * (height/cols));
        yellow_box->setFillColor(sf::Color::Yellow);

        

        std::vector<std::pair<int,int>> temp = Valid_Moves(std::pair<int,int>(board_matrix_x,board_matrix_y));



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
            std::vector<std::pair<int,int>> capture_moves = Check_Capture(piece);

            if(can_capture == true)
            {
                
                return capture_moves;
            }


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
            
            
            
        }


    }

    //for black
    else
    {
        //if board_matrix[][] = -1 it is a normal piece
        if(board_matrix[piece.first][piece.second] == 1)
        {
            std::vector<std::pair<int,int>> capture_moves = Check_Capture(piece);

            if(can_capture == true)
            {   
                
                return capture_moves;
            }

            

            //pushing back the moves if they are free squares and they are not kings or corner pieces
            if(piece.second > 0 && board_matrix[piece.first + 1][piece.second - 1] == 0)
            {
                moves.push_back(std::pair<int,int>(piece.first + 1, piece.second - 1));
            }
            if( piece.second < 7 && board_matrix[piece.first + 1][piece.second + 1] == 0)
            {
                moves.push_back(std::pair<int,int>(piece.first + 1, piece.second + 1));
            }
            

            
        }
    }

    return moves;
}


void Board::Make_Move(int x_pos, int y_pos,std::pair<int,int> previous_selection)
{

    int previous_x = previous_selection.second / (width/rows);
    int previous_y = previous_selection.first/ (height/cols);

    int board_matrix_x = y_pos / (width/rows);
    int board_matrix_y = x_pos / (height/cols);

    std::vector<std::pair<int,int>> moves = Valid_Moves(std::pair<int,int>(previous_x,previous_y));

    for(int i = 0; i < moves.size(); ++i)
    {

        //the clicked position is a valid move
        if(moves.at(i).first == board_matrix_x && moves.at(i).second == board_matrix_y)
        {
            //it is valid and now i am making the move
            //first updating the game matrix
            board_matrix[previous_x][previous_y] = 0;
            Print_Sprite_Locations();
            //if white make the number -1
            if(turn == true)
            {
                board_matrix[board_matrix_x][board_matrix_y] = -1;
                
                std::map<std::pair<int,int>,sf::Sprite>::iterator it = white_sprite.find({previous_x,previous_y});

                if(it != white_sprite.end()) //if it is found continue
                {
                        int dx = board_matrix_x * (width/rows);
                        int dy = board_matrix_y * (height/cols);
                        
                        it -> second.setPosition(sf::Vector2f(dy + 10,dx));

                        //going to erase and insert new map node to have updated coords
                        sf::Sprite temp = it -> second;
                        white_sprite.erase(it);
                        white_sprite.insert({{board_matrix_x,board_matrix_y},temp});
                }
                else
                {
                    std::cout << "white_piece not found in map: " << board_matrix_x << " " << board_matrix_y << std::endl;
                }


                turn = false;
                break;
                
            }
            else
            {
                board_matrix[board_matrix_x][board_matrix_y] = 1;
                
                std::map<std::pair<int,int>,sf::Sprite>::iterator it = black_sprite.find({previous_x,previous_y});

                if(it != black_sprite.end()) //if it is found continue
                {
                    int dx = board_matrix_x * (width/rows);
                    int dy = board_matrix_y * (height/cols);
                    
                    it -> second.setPosition(sf::Vector2f(dy + 10,dx));
                    //have to update key so that it corresponds to the new position
                    sf::Sprite temp = it -> second;
                    black_sprite.erase(it);
                    black_sprite.insert({{board_matrix_x,board_matrix_y},temp});
                    

                }
                else
                {
                    std::cout << "black_piece not found in map: " << board_matrix_x << " " << board_matrix_y << std::endl;
                }


                turn = true;
                break;
            }

            
            
        }
    }

    Print_Matrix();

}



std::vector<std::pair<int,int>> Board::Check_Capture(std::pair<int,int> piece)
{
    //iterating through board matrix and checking to see if there is a chance that a piece capture can take place
    std::vector<std::pair<int,int>> capture_pieces;
    can_capture = false;
    if(turn == true)
    {
        for(int i = 0; i < rows; ++i)
        {
            for(int j = 0; j < cols; ++j)
            {
                if(board_matrix[i][j] == -1)
                {

                    if( (i - 1) > 0 && (j - 1) > 0 && board_matrix[i - 1][j - 1] == 1)
                    {   
                    
                        int x = i - 2;
                        int y = j - 2;
                        

                        if(x >= 0 && y >= 0 && board_matrix[x][y] == 0)
                        {

                            can_capture = true;
                            if(piece.first == i && piece.second == j)
                            {
                                capture_pieces.push_back(std::pair<int,int>(x,y));
                            }
                            
                        }

                    }

                    if( (i - 1) > 0 && (j + 1)< 7 && board_matrix[i-1][j + 1] == 1)
                    {
                        int x = i - 2;
                        int y = j + 2;
                        

                        if(x >= 0 && y <= 7 && board_matrix[x][y] == 0)
                        {
                            can_capture = true;
                            if(piece.first == i && piece.second == j)
                            {
                                capture_pieces.push_back(std::pair<int,int>(x,y));
                            }
                        }

                    }
                }  
            }
        }
    }
    //if it is black's turn
    else
    {
        for(int i = 0; i < rows; ++i)
        {
            for(int j = 0; j < cols; ++j)
            {
                if(board_matrix[i][j] == 1)
                {

                    if( (i + 1) < 7 && (j - 1) > 0 && board_matrix[i + 1][j - 1] == -1)
                    {   
                    
                        int x = i + 2;
                        int y = j - 2;
                        

                        if(x >= 0 && y >= 0 && board_matrix[x][y] == 0)
                        {
                            can_capture = true;
                            if(piece.first == i && piece.second == j)
                            {
                                capture_pieces.push_back(std::pair<int,int>(x,y));
                            }
                        }

                    }

                    if((i + 1) < 7 && (j + 1) < 7 && board_matrix[i + 1][j + 1] == -1)
                    {
                        int x = i + 2;
                        int y = j + 2;
                        

                        if(x >= 0 && y <= 7 && board_matrix[x][y] == 0)
                        {
                            can_capture = true;
                            if(piece.first == i && piece.second == j)
                            {
                                capture_pieces.push_back(std::pair<int,int>(x,y));
                            }
                        }

                    }
                }  
            }
        }
    }


    return capture_pieces;

}


void Board::Print_Matrix()
{
    for(int i = 0; i < 8; ++i)
    {
        for(int j = 0 ; j < 8; ++j)
        {
            std::cout << board_matrix[i][j] << "  ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl << std::endl;
}


void Board::Print_Sprite_Locations()
{
    for (std::map<std::pair<int,int>,sf::Sprite>::iterator it=white_sprite.begin(); it!=white_sprite.end(); ++it)
    {
        std::cout << "white position: " << it->first.first << " " << it -> first.second << std::endl;
    }

    for (std::map<std::pair<int,int>,sf::Sprite>::iterator it=black_sprite.begin(); it!=black_sprite.end(); ++it)
    {
        std::cout << "black position: " << it->first.first << " " << it -> first.second << std::endl;
    }

}