#include <iostream>
#include "game.h"
#include <locale>
#include <cstdlib>
#include "gameUtils.h"

int main()
{
    system("chcp 65001 > nul");
    setlocale(LC_ALL, ".UTF-8");

    Game game;
    game.Start();

    return 0;
}