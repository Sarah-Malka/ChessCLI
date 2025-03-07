#pragma once
#include "basicTypes.h"
class Piece;

class singleMove
{
public:
	Coordinate origin;
	Coordinate destination;
	PieceType originalPiece;
	PieceType coronationRequest;
	bool isCastlation;
};
