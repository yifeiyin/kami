#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <iostream>
#include <vector>
#include <string>
#include "kbhit.h"
#include "colorful.h"

using namespace std;

class GameManager
{
private:
    bool playing;
    int width, length;
    int focusX, focusY;
    char left, right, up, down, confirm, pause, quit;
    vector<vector<int>> board;
    string cache;

public:
    GameManager(int max_x, int max_y)
    {
        playing = true;
        srand(time(NULL));
        width = max_x;
        length = max_y;
        focusX = width / 2;
        focusY = length / 2;

        up = 'w'; left = 'a'; right = 'd'; down = 's';
        confirm = ' '; pause = 'p'; quit = 'q';

        board.resize(max_x);
        for (int x = 0; x < max_x; x++)
            board[x].resize(max_y);

        for (int x = 0; x < width; x++)
            for (int y = 0; y < length; y++)
                board[x][y] = rand()%6;

        cache = "";
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
                case 0: tmp += COLORFUL::bGRAY; break;
                case 1: tmp += COLORFUL::bPURPLE; break;
                case 2: tmp += COLORFUL::bRED; break;
                case 3: tmp += COLORFUL::bBLUE; break;
                case 4: tmp += COLORFUL::bBLUE_l; break;
                case 5: tmp += COLORFUL::bGREEN; break;
                default: tmp += COLORFUL::bORANGE;
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
