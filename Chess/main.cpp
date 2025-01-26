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

    wchar_t Notking = L'\u2655';

    std::wcout << Notking << " " << L'\u265A' << std::endl;

    std::cout << "Hello!\n";
    Board a;
    a.PrintBoard();
    return 0;
}