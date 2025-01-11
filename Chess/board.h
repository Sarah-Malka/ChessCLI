#pragma once
#include <vector>
#include "types.h"

using array2D = std::vector<std::vector<Square>>;


class Board
{
private:
	array2D board;
	singleMove lastMove;
	bool WhiteToPlay = true;

	static bool alreadyCreated;
	static array2D GetToInitialState();
	bool isValidMove(struct singleMove);
	singleMove StringToMove(char* move);

public:
	Board();

	void PrintBoard() const;
};