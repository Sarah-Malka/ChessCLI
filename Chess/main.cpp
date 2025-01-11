#include <iostream>
#include "board.h"
#include <locale>
#include <cstdlib>

int main()
{
    system("chcp 65001 > nul");
    setlocale(LC_ALL, ".UTF-8");
    wchar_t king = L'\u2654';
    std::wcout << king << " " << L'\u265A' << std::endl;

    std::cout << "Hello!\n";
    Board a;
    a.PrintBoard();
    return 0;
}