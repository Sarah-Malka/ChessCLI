#include <iostream>
#include "game.h"
#include <locale>
#include <cstdlib>
#include "gameUtils.h"
#include <windows.h>

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    MessageBoxA(NULL, "Hello", "Test", MB_OK);

    Game game;
    game.Start();

    return 0;
}