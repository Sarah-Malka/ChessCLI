#pragma comment(lib, "winmm.lib")

#include "GameUtils.h"
#include <Windows.h>

bool lastMoveWasCapture = false;
PieceType pieceForCoronation = PieceType::PAWN;

void GameUtils::GameSound(const bool eat)
{
	if (eat)
	{
		PlaySoundW(TEXT("Sounds\\eat.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
	else
	{
		PlaySoundW(TEXT("Sounds\\move.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
}

singleMove GameUtils::stringToMove(std::wstring move)
{
	// if the input string isn't a move, the function returns an empty move

	// define return var
	singleMove ret;
	ret.origin.collumn = 10; // junk value
	ret.origin.row = 10;
	ret.destination.collumn = 0;
	ret.destination.row = 0;
	ret.originalPiece = PieceType::PAWN;
	ret.coronationRequest = PieceType::QUEEN;

	if (move.empty())
	{
		std::cout << "empty move!" << std::endl;
		return ret; //this is a way of expressing an error. give player another turn instead.
	}

	if (move[0] >= L'a' && move[0] <= L'h' && move[1] == L'x')
	{
		ret.origin.collumn = move[0] - L'a';
		move.erase(0, 2);
	}
	else if (move[0] == L'K')
	{
		ret.originalPiece = PieceType::KING;
		move.erase(0, 1); // erase 1 characters starting with position 0
	}
	else if (move[0] == L'Q')
	{
		ret.originalPiece = PieceType::QUEEN;
		move.erase(0, 1);
	}
	else if (move[0] == L'R')
	{
		ret.originalPiece = PieceType::ROCK;
		move.erase(0, 1);
	}
	else if (move[0] == L'B')
	{
		ret.originalPiece = PieceType::BISHOP;
		move.erase(0, 1);
	}
	else if (move[0] == L'N')
	{
		ret.originalPiece = PieceType::KNIGHT; // all legit so far
		move.erase(0, 1);
	}

	if (move.empty())
	{
		return ret; // error?
	}

	//look for coronation attempt:
	if (move.length() > 2)
	{
		size_t len = move.length();
		if (move[len - 2] == L'=')
		{
			switch (move[len-1])
			{
			case L'N':
			case L'n':
				ret.coronationRequest = PieceType::KNIGHT;
				break;
			case L'B':
			case L'b':
				ret.coronationRequest = PieceType::BISHOP;
				break;
			case L'R':
			case L'r':
				ret.coronationRequest = PieceType::ROCK;
				break;
			default:
				ret.coronationRequest = PieceType::QUEEN;
			}
		}
	}


	move = removeUnnececeryEnding(move); // use to alarm player that took or gave check without knowing?
	if (move[0] == L'x')
	{
		move.erase(0, 1);
	}

	// handle player telling us what origin piece is moving
	if (move.length() > 2)
	{
		if (move[0] >= L'a' && move[0] <= L'h')
		{
			ret.origin.collumn = move[0] - L'a';
			move.erase(0, 1);
		}
		if (move[0] >= L'1' && move[0] <= L'8')
		{
			ret.origin.row = move[0] - L'1';
			move.erase(0, 1);
		}
	}
	if (move[0] == L'x')
	{
		move.erase(0, 1);
	}

	// destination
	if (move.length() != 2 || move[0] < L'a' || move[0] > L'h' || move[1] < L'1' || move[1] > L'8') // this will be non legit
	{
		// Error!
		//ret.originalPiece = PAWN;
		std::cout << "No valid destination! " << std::endl;
		return ret;
	}
	
	ret.destination.collumn = move[0] - L'a';
	ret.destination.row = move[1] - L'1';
	move.erase(0, 2);
	if (move.length() >= 2)
	{
		if (move[0] == L'=')
		{
			if (move[1] == L'Q' || move[1] == L'q')
			{
				pieceForCoronation = QUEEN;
			}
			else if (move[1] == L'R' || move[1] == L'r')
			{
				pieceForCoronation = ROCK;
			}
			else if (move[1] == L'B' || move[1] == L'b')
			{
				pieceForCoronation = BISHOP;
			}
			else if (move[1] == L'N' || move[1] == L'n')
			{
				pieceForCoronation = KNIGHT;
			}
			else if (move[1] == L'K' || move[1] == L'k')
			{
				pieceForCoronation = KING; // just to give a proper error message in case of a pawn trying that.
			}

		}
	}

	// if an "x" was out of place but the move was legal, mention that (and ask if sure?)
	// if queening - need function to change the piece in the destination coordinate - to the premoted piece
	// special moves (castling, en-passant)

	return ret;
}

std::wstring GameUtils::removeUnnececeryEnding(std::wstring move)
{
	while (move.back() > L'8' or move.back() < L'1')
	{
		move.pop_back();
	}

	//while (move.back() == '#' || move.back() == '+')
		// fails to "d8=Q"
	return move;
}

std::wstring GameUtils::removeX(std::wstring move)
{
	uint8_t j = 0;
	for (uint8_t i = 0; i < move.length(); i++)
	{
		if (move[i] != L'x') 
		{
			move[j++] = move[i];
		}
	}
	move[j] = '\0'; // Null-terminate the modified string

	return move;
}
