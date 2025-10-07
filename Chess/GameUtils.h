#pragma once
#include "types.h"
#include <string>
#include <iostream>

class GameUtils
{

public:
	static size_t NonValideIndex;

	static void GameSound(const bool eat);
	static singleMove stringToMove(std::wstring move);
	static singleMove getInvalidMove();
private:
	static std::wstring removeUnnececeryEnding(std::wstring move);
	static std::wstring removeX(std::wstring move);
};
