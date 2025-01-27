#pragma once
#include <vector>
#include "Piece.h"
//#include "types.h"

using array2D = std::vector<std::vector<Piece*>>;


class Board
{
public:
	array2D board;

	static bool alreadyCreated;
	static array2D GetToInitialState();

	static bool isCheckmate();
	static bool isStalemate();

public:
	Board();
	std::vector<Piece*>& operator[](std::size_t index);
	const std::vector<Piece*> operator[](std::size_t index) const;	
	void PrintBoard() const;
};