#include "GameUtils.h"
bool lastMoveWasCapture = false;
PieceType pieceForCoronation = PAWN;

singleMove GameUtils::stringToMove(std::wstring move)
{
	// this function returns only destination and . if the input string isn't a move, the function returns an empty move

	// define return var
	singleMove ret;
	ret.origin.collumn = 0;
	ret.origin.row = 0;
	ret.destination.collumn = 0;
	ret.destination.row = 0;
	ret.originalPiece = PieceType::PAWN;

	move = removeUnnececeryEnding(move); //do i really need this function at all?
	if (move.empty())
	{
		std::cout << "empty move!" << std::endl;
		return ret; //this is a way of expressing an error. give player another turn instead.
	}

	if (move[0] == 'K')
	{
		ret.originalPiece = PieceType::KING;
		move.erase(0, 1); // erase 1 characters starting with position 0
	}
	else if (move[0] == 'Q')
	{
		ret.originalPiece = PieceType::QUEEN;
		move.erase(0, 1);
	}
	else if (move[0] == 'R')
	{
		ret.originalPiece = PieceType::ROCK;
		move.erase(0, 1);
	}
	else if (move[0] == 'B')
	{
		ret.originalPiece = PieceType::BISHOP;
		move.erase(0, 1);
	}
	else if (move[0] == 'N')
	{
		ret.originalPiece = PieceType::KNIGHT; // all legit so far
		move.erase(0, 1);
	}

	lastMoveWasCapture = false;
	if (!move.empty() && (move[0] == 'x' || move[0] == 'X'))
	{
		move.erase(0, 1); 
		lastMoveWasCapture = true;
	}
	if (move.length() < 2 || move[0] < 'a' || move[0] > 'h' || move[1] < 1 || move[1] > 8) // this will be non legit
	{
		ret.originalPiece = PAWN;
		return ret;
	}
	
	ret.destination.collumn = move[0] - 'a';
	ret.destination.row = move[1] - '1';
	move.erase(0, 2);
	if (move.length() >= 2)
	{
		if (move[0] == '=')
		{
			if (move[1] == 'Q' || move[1] == 'q')
			{
				pieceForCoronation = QUEEN;
			}
			else if (move[1] == 'R' || move[1] == 'r')
			{
				pieceForCoronation = ROCK;
			}
			else if (move[1] == 'B' || move[1] == 'b')
			{
				pieceForCoronation = BISHOP;
			}
			else if (move[1] == 'N' || move[1] == 'n')
			{
				pieceForCoronation = KNIGHT;
			}
			else if (move[1] == 'K' || move[1] == 'k')
			{
				pieceForCoronation = KING; // just to give a proper error message in case of a pawn trying that.
			}

		}
	}

	// find what piece is moving: piece type and color, what piece can get there.
	// if it ends with "=Q", with "#" or with "+" then handel. before them will be the destination square
	// maybe unless the moving piece was a pawn, which you can know by seeing if the first letter is capital
	// if an "x" was out of place but the move was legal, mention that (and ask if sure?)
	// if queening - need function to change the piece in the destination coordinate, to the premoted piece

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

std::wstring GameUtils::removeUnnececeryEnding(std::wstring move)
{
	if (move.empty())
	{
		return move;
	}
	if (move.back() == '#' || move.back() == '+')
	{
		move.pop_back();
	}
	return move;
}

Coordinate GameUtils::squareToCoordinate(std::wstring destinationSquare)
{
	Coordinate ret;
	
	ret.collumn = destinationSquare[0] - 'a';
	ret.row = destinationSquare[1] - 1;
	// fix bug it shows "row 51" and stuff

	return ret;
}
