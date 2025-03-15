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
	bool operator==(const Coordinate& other) const {
		return (row == other.row) && (collumn == other.collumn);
	}
};

enum class CastleType : uint8_t
{
	NO_CASTLING = 0,
	SMALL,
	BIG
};