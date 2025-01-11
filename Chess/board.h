#pragma once
#include <vector>
#include "types.h"

using array2D = std::vector<std::vector<Square>>;

class Board
{
private:
	array2D board;

	static bool alreadyCreated;
	static array2D GetInitialState();

public:
	Board();

	void PrintBoard() const;
};