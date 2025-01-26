#pragma once
#include "basicTypes.h"
class Piece;


//struct Square
//{
//	bool occupied = false;
//	Piece* piece;
//	Square(bool occupied, const std::string& pieceType, const std::string& pieceColor)
//		: occupied(occupied), piece(new Piece(PieceType::BISHOP, Color::BLACK, 0, 0) {}
//};


struct singleMove
{
	Coordinate origin;
	Coordinate destination;
	PieceType originalPiece;
};
