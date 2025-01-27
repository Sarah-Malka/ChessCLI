#pragma once
#include "types.h"
#include "board.h"

class GameInfo
{
public:
	Board board;
	singleMove lastMove;
	static bool WhiteToPlay;


	bool whiteKingMoved = false;
	bool a1WhiteRockMoved = false;
	bool a8WhiteRockMoved = false;

	bool blackKingMoved = false;
	bool h1BlackRockMoved = false;
	bool h8BlackRockMoved = false;

	bool lastMoveWasDoubleMoveByPawn = false;//should save the location of that pawn?
};

