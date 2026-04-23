#pragma once
#include "types.h"

class GameInfo
{
public:
	static bool WhiteToPlay;

	static bool atelastMove;
	static uint8_t number_of_pieces_on_board;

	static bool whiteKingMoved;
	static bool a1WhiteRockMoved;
	static bool a8WhiteRockMoved;

	static bool blackKingMoved;
	static bool h1BlackRockMoved;
	static bool h8BlackRockMoved;

	static constexpr uint8_t outOfBoardRange = 10;
	static Coordinate pawnSkippedThisSquareLastTurn;
	static bool doubleMoveWasAttemptedThisTurn;

	static size_t numberOfMovesFor50MoveRule;
};

