#pragma once
#include "basicTypes.h"
class Piece;

struct singleMove
{
	Coordinate origin;
	Coordinate destination;
	PieceType originalPiece;
	PieceType coronationRequest;
};
