#include "Tetromino.cpp"

class Score
{
    public:
        int score_board[20][10];

        // Construct
        Score() 
        {
            for(int x = 0; x < 20; x++)
            {
                for(int y = 0; y < 10; y++)
                {
                    score_board[x][y] = 0;
                }
            }
        }      
};
