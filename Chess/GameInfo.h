#pragma once
#include "types.h"

class GameInfo
{
public:
	static bool WhiteToPlay;

	static bool atelastMove;

	static bool whiteKingMoved;
	static bool a1WhiteRockMoved;
	static bool a8WhiteRockMoved;

	static bool blackKingMoved;
	static bool h1BlackRockMoved;
	static bool h8BlackRockMoved;

	static Coordinate pawnSkippedThisSquareLastTurn;


};

