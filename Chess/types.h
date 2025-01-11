#pragma once
#include <cstdint>

enum Color : uint8_t
{
	WHITE = 0,
	BLACK
};

enum Piece : uint8_t
{
	KING = 0,
	QUEEN,
	ROCK,
	BISHOP,
	KNIGHT,
	PAWN

};

struct Square
{
	bool occupied = false;
	Color color;
	Piece piece;
};

struct Coordinate
{
	uint8_t row;
	uint8_t collumn;
};

struct singleMove
{
	Coordinate origin;
	Coordinate destination;
};
