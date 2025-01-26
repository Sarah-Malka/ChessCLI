#pragma once
#include "types.h"
#include <string>
#include <iostream>

class GameUtils
{
public:
	static singleMove stringToMove(std::wstring move);
	static bool isValidMove(struct singleMove);
private:
	static std::wstring removeUnnececeryEnding(std::wstring move);
public:
	static Coordinate squareToCoordinate(std::wstring destinationSquare);
};
