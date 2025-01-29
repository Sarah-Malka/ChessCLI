#pragma once
#include "GameInfo.h"
#include "board.h"

class Game
{
private:
	Board board;
	bool invalid_input = false;
	std::vector<Piece*> GetPossiblePiecesToMove(const singleMove move)const;

public:
	void Start();
};

