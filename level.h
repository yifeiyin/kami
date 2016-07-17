#ifndef LEVEL_H
#define LEVEL_H

#include <vector>

using namespace std;

class Level
{
private:
    int width, length;
    int color_amount;
    int * color;
    vector<vector <int>> board;

public:
    Level()
    {
        Level(10,10);
    }

    Level(int max_x, int max_y)
    {
        width = max_x;
        length = max_y;

        color_amount = 3;
        color = new int [color_amount];
        for (int i = 0; i < color_amount; i++)
            color[i] = i;

        board.resize(max_x);
        for (int x = 0; x < max_x; x++)
            board[x].resize(max_y);

        if (Generate() == false)
            for (int x = 0; x < width; x++)
                for (int y = 0; y < length; y++)
                    board[x][y] = 0;


    }

    bool Generate()
    {
        for (int x = 0; x < width; x++)
            for (int y = 0; y < length; y++)
                board[x][y] = rand()%color_amount;

        for (int x = 0; x < width; x++)
            for (int y = 0; y < length; y++)
            {
                if (board[x][y] != board[x>0?x-1:x+1][y>0?y-1:y+1] &&
                        board[x][y] != board[x>0?x-1:x+1][y<length-1?y+1:y-1] &&
                        board[x][y] != board[x<width-1?x+1:x-1][y>0?y-1:y+1] &&
                        board[x][y] != board[x<width-1?x+1:x-1][y<length-1?y+1:y-1])
                    switch (rand() % 4)
                    {
                    case 0: board[x][y] = board[x>0?x-1:x+1][y>0?y-1:y+1]; break;
                    case 1: board[x][y] = board[x>0?x-1:x+1][y<length-1?y+1:y-1]; break;
                    case 2: board[x][y] = board[x<width-1?x+1:x-1][y>0?y-1:y+1]; break;
                    case 3: board[x][y] = board[x<width-1?x+1:x-1][y<length-1?y+1:y-1]; break;
                    default: return false;
                    }
            }

        return true;
    }

    inline int GetWidth() { return width; }
    inline int GetLength() { return length; }
    inline int GetColorAmount() { return color_amount; }
    inline int GetColor(int index) { return (index < color_amount && index >= 0)?color[index]:0; }
    inline vector<vector<int>> GetBoard() { return board; }

};

#endif // LEVEL_H
