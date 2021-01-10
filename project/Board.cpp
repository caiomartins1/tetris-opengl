#include "Tetromino.cpp"

class Board
{
    public:
        int score;
        int game_board[20][10];
        Board() {
            score = 0;
            for(int x = 0; x < 20; x++)
            {
                for(int y = 0; y < 10; y++)
                {
                    game_board[x][y] = 0;
                }
            }
        }

        Tetromino move_piece_left(Tetromino piece) 
        {

            // Clear old coordinates
            for(int i = 0; i < 4; i++)
            {
                game_board[piece.y[i]][piece.x[i]] = 0;
            }

            // Refresh new coordinates
            if(validation_move_left(piece,1))
            {
                for(int i = 0; i < 4; i++)
                {
                    piece.x[i]--;
                }
                piece.prevX = piece.prevX - 1;
            }

             // Add new coordinates to board
            for(int i = 0; i < 4; i++)
            {
                game_board[piece.y[i]][piece.x[i]] = piece.shape;
            }

            return piece;
        }

        Tetromino move_piece_right(Tetromino piece) 
        {
            
            // Clear old coordinates
            for (int i = 0; i < 4; i++) {
                game_board[piece.y[i]][piece.x[i]] = 0;
            }

            if (validation_move_right(piece)) {
                // Refresh new coordinates
                for (int i = 0; i < 4; i++) {
                    piece.x[i]++;
                }
                piece.prevX = piece.prevX + 1;
            }

            // Add new coordinates to board
            for (int i = 0; i < 4; i++) 
            {
                game_board[piece.y[i]][piece.x[i]] = piece.shape;
            }

            return piece;
        }
        
        Tetromino move_piece_down(Tetromino piece)
        {
            score += 10;
            // Clear old coordinates
            for(int i = 0; i < 4; i++)
            {
                game_board[piece.y[i]][piece.x[i]] = 0;
            }

            if(validation_move_down(piece,1))
            {
                // Refresh new coordinates
                for(int i = 0; i < 4; i++)
                {
                    piece.y[i] = piece.y[i] + 1;
                }
                piece.prevY = piece.prevY + 1;
            }
            else
            {
                piece.finished = true;
            }

            // Add new coordinates to board
            for(int i = 0; i < 4; i++)
            {
                game_board[piece.y[i]][piece.x[i]] = piece.shape;
            }

            return piece;
        }

        bool validation_move_down(Tetromino piece, int y)
        {
            for(int i = 0; i < 4; i++)
            {
                if(game_board[piece.y[i]+y][piece.x[i]] != 0 || piece.y[i]+y > 19)
                {
                    return false;
                }
            }
            
            return true;
        }
        bool validation_move_left(Tetromino piece, int x)
        {

            for(int i = 0; i < 4; i++)
            {
                if(game_board[piece.y[i]][piece.x[i]-x] != 0 || piece.x[i] - x < 0)
                {
                    return false;
                }
            }
            
            return true;
        }
        bool validation_move_right(Tetromino piece)
        {

            for(int i = 0; i < 4; i++)
            {
                if(game_board[piece.y[i]][piece.x[i] + 1] != 0 || piece.x[i] + 1 > 9)
                {
                    return false;
                }
            }
            
            return true;
        }
    
        bool validation_rot(Tetromino piece)
        {
            for(int i = 0; i < 4; i++)
            {
                if(game_board[piece.y[i]][piece.x[i] + 1] != 0 || piece.x[i] + 1 > 9)
                {
                    return false;
                }
            }
            
            return true;
        }
        void clear_board()
        {
            for(int x = 0; x < 20; x++)
            {
                for(int y = 0; y < 10; y++)
                {
                    game_board[x][y] = 0;
                }
            }
        }

        void clear_line(int line)
        {
            for(int i = 0; i < 10; i++)
            {
                game_board[line][i] = 0;
            }

            for(int i = line; i > 0; i--)
            {
                for(int j = 0; j < 10; j++)
                {
                    if(i-1 > 0)
                    {
                        if(game_board[i-1][j] != 0)
                        {
                            score += 10;
                            game_board[i][j] = game_board[i-1][j];
                            game_board[i-1][j] = 0;
                        }
                    }
                }

            }

        }
        void verification_lines()
        {
            for(int i = 0; i < 20; i++)
            {
                for(int j = 0; j < 10; j++)
                {
                    if(game_board[i][j] == 0)
                    {
                        break;
                    }
                    else
                    {
                        if(j == 9)
                        {
                            clear_line(i);
                            verification_lines();
                            return;
                        }
                    }
                }
            }
        }
        Tetromino move_piece_rotate(Tetromino piece)
        {

            Tetromino aux = piece;
            piece.rot = (piece.rot + 1) % 4;

            // Clear old coordinates
            for(int i = 0; i < 4; i++)
            {
                game_board[piece.y[i]][piece.x[i]] = 0;
            }

            for(int i = 0; i < 4; i++)
            {
                piece.x[i] = piece.shapes[piece.shape-1][piece.rot][i][0] + piece.prevX;
                piece.y[i] = piece.shapes[piece.shape-1][piece.rot][i][1] + piece.prevY;
            }

            for(int i = 0; i < 4; i++)
            {
                bool betweenX = (piece.x[i] < 9 && piece.x[i] > 0);
                bool betweenY = (piece.y[i] < 19 && piece.y[i] > 0);
                bool noPieceInPosition = (game_board[piece.y[i]][piece.x[i]] == 0);

                if (betweenX && betweenY && noPieceInPosition)
                {
                    continue;
                }
                else
                {
                    return aux;
                }
            }

            return piece;

        }

    
    

        
};
