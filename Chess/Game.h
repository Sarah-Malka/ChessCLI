#pragma once
#include "GameInfo.h"

class Game
{
private:
	GameInfo game_info;
	std::vector<Piece*> GetPossiblePiecesToMove(const singleMove move)const;

public:
	void Start();
};

