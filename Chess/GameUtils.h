#pragma once
#include "types.h"
#include <string>
#include <iostream>

class GameUtils
{

public:
	static singleMove stringToMove(std::wstring move);
	static singleMove thisPieceCanMoveThere(singleMove);
private:
	static std::wstring removeUnnececeryEnding(std::wstring move);
};
