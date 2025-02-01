#pragma once
#include <cstdint>

enum Color : uint8_t
{
	WHITE = 0,
	BLACK
};

enum PieceType : uint8_t
{
	KING = 0,
	QUEEN,
	ROCK,
	BISHOP,
	KNIGHT,
	PAWN,
	INVALID

};
struct Coordinate
{
	uint8_t row;
	uint8_t collumn;
};