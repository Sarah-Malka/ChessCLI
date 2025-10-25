#pragma once
#include "GameInfo.h"
#include "board.h"

class Game
{
private:
	Board board;
	bool invalid_input = false;
	ErrorCode last_relevant_move_error = ErrorCode::Success;
	std::vector<Piece*> GetPossiblePiecesToMove(const singleMove move);
	bool GameHasEnded();
	bool LegalMoveExists(Color color);
	bool PieceHasLegalMoves(Piece *piece);

public:
	void Start();
};

