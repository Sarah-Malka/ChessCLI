#pragma once
#include "types.h"
#include "board.h"

static class GameInfo
{
	Board board;
	singleMove lastMove;
	bool WhiteToPlay = true;


	bool whiteKingMoved = false;
	bool a1WhiteRockMoved = false;
	bool a8WhiteRockMoved = false;

	bool blackKingMoved = false;
	bool h1BlackRockMoved = false;
	bool h8BlackRockMoved = false;

	bool lastMoveWasDoubleMoveByPawn = false;
};

