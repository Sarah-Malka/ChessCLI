#pragma once
#include "GameInfo.h"
#include "board.h"

class Game
{
private:
	Board board;
	bool invalid_move = false;
	ErrorCode last_relevant_move_error = ErrorCode::Success;
	std::vector<Piece*> GetPossiblePiecesToMove(const singleMove move);
	EndGameType GameHasEnded();
	bool EnPassantPrivilegesExists();

public:
	void Start();
};

