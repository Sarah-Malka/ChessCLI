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

	//bool isValidMove(struct singleMove);
	static bool isCheckmate();
	static bool isStalemate();
	//singleMove StringToMove(char* move);

public:
	Board();

	void PrintBoard() const;
};