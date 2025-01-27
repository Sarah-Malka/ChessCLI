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

    /*Board a;

    a.PrintBoard();
    std::wstring move = L"";
    std::wcin >> move;
    singleMove myMove = GameUtils::stringToMove(move);


    bool valid = a[2][1]->IsValidMove(myMove.destination, a);
    if (valid)
    {
        a.Move(Coordinate{ 2,1 }, myMove.destination);
    }
    a.PrintBoard();*/


    return 0;
}