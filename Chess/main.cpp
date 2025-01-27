#include <iostream>
#include "board.h"
#include <locale>
#include <cstdlib>
#include "gameUtils.h"

int main()
{
    system("chcp 65001 > nul");
    setlocale(LC_ALL, ".UTF-8");

    singleMove myMove = GameUtils::stringToMove(L"Nf3");

    Board a;
    a.PrintBoard();
    return 0;
}