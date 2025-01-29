#pragma once
#include <vector>
#include "Piece.h"
//#include "types.h"

using array2D = std::vector<std::vector<Piece*>>;


class Board
{
private:
	std::vector<Coordinate> kings_locations;
public:
	array2D board;
	static array2D GetToInitialState();

	static bool isCheckmate();
	static bool isStalemate();

public:
	Board();
	std::vector<Piece*>& operator[](std::size_t index);
	const std::vector<Piece*> operator[](std::size_t index) const;

	Piece*& operator[](Coordinate position);
	Piece* const operator[](Coordinate position) const;
	void PrintBoard() const;
	void Move(const Coordinate source, const Coordinate dest);
	bool IsCheck(const Color color) const;
};