#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <iostream>
#include <vector>
#include <string>
#include "kbhit.h"
#include "colorful.h"
#include "level.h"

using namespace std;

class GameManager
{
private:
    bool playing;
    int width, length;
    int focusX, focusY;
    char left, right, up, down, confirm, pause, quit;
    Level level;
    vector<vector<int>> board;
    string cache;

public:
    GameManager(int max_x, int max_y)
    {
        playing = true;
        srand(time(NULL));

        up = 'w'; left = 'a'; right = 'd'; down = 's';
        confirm = ' '; pause = 'p'; quit = 'q';

        cache = "";

        level = Level (max_x, max_y);

        Load();
    }

    void Load()
    {
        width = level.GetWidth();
        length = level.GetLength();
        focusX = width / 2;
        focusY = length / 2;

        board = level.GetBoard();
    }

    void Print()
    {
        string tmp;

        tmp += "\n";

        tmp += "  ";
        tmp += COLORFUL::bBLACK;
        for (int i = 0; i < width + 1; i++)
             tmp += "    ";
        tmp += COLORFUL::RESET;
        tmp += "\n";

        for (int y = 0; y < length * 2; y++)
        {
            tmp += "  ";
            tmp += COLORFUL::bBLACK;
            tmp += "  ";
            tmp += COLORFUL::RESET;

            for(int x = 0; x < width; x++)
            {
                switch (board[x][y/2])
                {
                case 0: tmp += COLORFUL::bORANGE; break;
                case 1: tmp += COLORFUL::bPURPLE; break;
                case 2: tmp += COLORFUL::bRED; break;
                case 3: tmp += COLORFUL::bBLUE; break;
                case 4: tmp += COLORFUL::bBLUE_l; break;
                case 5: tmp += COLORFUL::bGREEN; break;
                default: tmp += COLORFUL::bGRAY;
                }
                if (x == focusX && y/2 == focusY)
                {
                    if (y%2 == 0) tmp += "┌──┐";
                    if (y%2 == 1) tmp += "└──┘";
                }
                else
                {
                    tmp += "    ";
                }
                tmp += COLORFUL::RESET;
            }
            tmp += COLORFUL::bBLACK;
            tmp += "  ";
            tmp += COLORFUL::RESET;
            tmp += "  ";
        }

        tmp += "  ";
        tmp += COLORFUL::bBLACK;
        for (int i = 0; i < width + 1; i++)
             tmp += "    ";
        tmp += COLORFUL::RESET;
        tmp += "\n";

        if (tmp != cache)
        {
            system("clear");
            cout << tmp;
            cache = tmp;
        }
    }

    bool Fill(int color)
    {
        if (color < 0 || color >= level.GetColorAmount())
            return false;

        _Fill_Recursion(focusX,focusY,board[focusX][focusY],color);

        return true;
    }

    void _Fill_Recursion(int x, int y, int original, int final)
    {
        if (board[x][y] != original)
                return;

        board[x][y] = final;

            if (x > 0)
                _Fill_Recursion(x-1,y,original,final);
            if (x < width - 1)
                _Fill_Recursion(x+1,y,original,final);
            if (y > 0)
                _Fill_Recursion(x,y-1,original,final);
            if (y < length - 1)
                _Fill_Recursion(x,y+1,original,final);
    }

    void Input()
    {
        if (kbhit())
        {
            char ch = cin.get();

            if (ch == left)
            {
                if (focusX > 0)
                    focusX--;
            }

            else if (ch == right)
            {
                if (focusX < width - 1)
                    focusX++;
            }

            else if (ch == up)
            {
                if (focusY > 0)
                    focusY--;
            }

            else if (ch == down)
            {
                if (focusY < length - 1)
                    focusY++;
            }

            // else if (ch == confirm)

            // else if (ch == pause)

            else if (ch == '0')
                Fill(0);

            else if (ch == '1')
                Fill(1);

            else if (ch == '2')
                Fill(2);

            else if (ch == quit)
            {
                playing = false;
            }

        }
    }

    void Start()
    {
        while (playing)
        {
            Print();
            Input();
        }
        cout << endl;
    }
};


#endif // GAMEMANAGER_H
