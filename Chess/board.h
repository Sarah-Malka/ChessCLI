#pragma once
#include <vector>
#include "Piece.h"
//#include "types.h"

using array2D = std::vector<std::vector<Piece*>>;


class Board
{
private:
	array2D board;

	static bool alreadyCreated;
	static array2D GetToInitialState();

	static bool isCheckmate();
	static bool isStalemate();

public:
	Board();

	void PrintBoard() const;
};