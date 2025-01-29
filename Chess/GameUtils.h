#pragma once
#include "types.h"
#include <string>
#include <iostream>

class GameUtils
{

public:
	static singleMove stringToMove(std::wstring move);
private:
	static std::wstring removeUnnececeryEnding(std::wstring move);
	static std::wstring removeX(std::wstring move);

};
