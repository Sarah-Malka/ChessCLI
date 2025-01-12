#include "GameUtils.h"

singleMove GameUtils::StringToMove(std::wstring move)
{
	// define return var
	singleMove ret;
	ret.origin.collumn = 0;
	ret.origin.row = 0;
	ret.destination.collumn = 0;
	ret.destination.row = 0;

	// find what piece is moving: piece type, what piece can get there.
	// if it ends with "=Q", with "#" or with "+" then handel. before them will be the destination square
	// maybe unless the moving piece was a pawn, which you can know by seeing if the first letter is capital
	// if an "x" was out of place but the move was legal, mention that (and ask if sure?)

	return ret;
}

bool GameUtils::isValidMove(struct singleMove)
{
	// color of the starting piece matching the players turn
	// can the type of piece move this way?
	// use "isCheck(color)" function
	// any blocking pieces?
	// special moves (castling, en-passant)
	// pawn moves (can go only to empty, can capture only to filled)

	return false;
}
