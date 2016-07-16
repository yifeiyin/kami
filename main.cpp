#include <iostream>
#include <vector>
#include <string>
#include "kbhit.h"
#include "colorful.h"
#include "gamemanager.h"

using namespace std;

int main()
{
    GameManager game(10,10);
    game.Start();
    return 0;
}
