#pragma once
#include "types.h"

class GameInfo
{
public:
	static bool WhiteToPlay;

	static bool atelastMove;

	bool whiteKingMoved = false;
	bool a1WhiteRockMoved = false;
	bool a8WhiteRockMoved = false;

	bool blackKingMoved = false;
	bool h1BlackRockMoved = false;
	bool h8BlackRockMoved = false;

	bool lastMoveWasDoubleMoveByPawn = false;//should save the location of that pawn?
};

