#pragma comment(lib, "winmm.lib")

#include "GameUtils.h"
#include <Windows.h>
#include "GameInfo.h"

const size_t NonValideIndex = 10;

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

singleMove GameUtils::getInvalidMove()
{
	singleMove ret;
	ret.origin.collumn = NonValideIndex; // junk value
	ret.origin.row = NonValideIndex;
	ret.destination.collumn = NonValideIndex;
	ret.destination.row = NonValideIndex;
	ret.originalPiece = PieceType::PAWN;
	ret.coronationRequest = PieceType::QUEEN;
	ret.isCastlation = false;
	
	return ret;
}

bool IsKingSideCastling(const std::wstring& move)
{
	return (move == L"0-0" || move == L"o-o" || move == L"O-O");
}

bool IsQueenSideCastling(const std::wstring& move)
{
	return (move == L"0-0-0" || move == L"o-o-o" || move == L"O-O-O");
}

singleMove GameUtils::stringToMove(std::wstring move)
{
	// if the input string isn't a move, the function returns a defalte non-legal move
	
	// define return var
	singleMove ret = getInvalidMove();

	try
	{
		move = removeUnnececeryEnding(move); // use to alarm player that took or gave check without knowing?
		move = removeX(move);

		if (move.empty())
			{
				std::cout << "empty move!" << std::endl;
				return ret; //this is a way of expressing an error. give player another turn instead.
			}
		if (IsKingSideCastling(move) || IsQueenSideCastling(move))
		{
			ret.originalPiece = PieceType::KING;
			ret.isCastlation = true;

			ret.origin.collumn = 4;
			ret.origin.row = GameInfo::WhiteToPlay ? 0 : 7;

			ret.destination.collumn = IsQueenSideCastling(move) ? 2:6;
			ret.destination.row = GameInfo::WhiteToPlay ? 0 : 7;

			return ret;
		}

		// pawn moves
		if (move[0] >= L'a' && move[0] <= L'h')
		{
			if (move.length() > 1 && move[1] >= L'a' && move[1] <= L'h')
			{
				ret.origin.collumn = move[0] - L'a';  // what about queening to a bishop and not saying the row?
				ret.destination.collumn = move[1] - L'a';
				move.erase(0, 2);
			}
			else 
			{
				ret.destination.collumn = move[0] - L'a';
				move.erase(0, 1);
			}
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

		// look for coronation attempt:
		if (move.length() >= 2)
		{
			size_t len = move.length();
			if (move[len - 2] == L'=')
			{
				if (move[len - 1] == L'Q' || move[len - 1] == L'q')
				{
					ret.coronationRequest = PieceType::QUEEN;
				}
				if (move[len - 1] == L'R' || move[len - 1] == L'r')
				{
					ret.coronationRequest = PieceType::ROCK;
				}
				if (move[len - 1] == L'B' || move[len - 1] == L'b')
				{
					ret.coronationRequest = PieceType::BISHOP;
				}
				if (move[len - 1] == L'N' || move[len - 1] == L'n')
				{
					ret.coronationRequest = PieceType::KNIGHT;
				}
				move.pop_back();
				move.pop_back();
			}
		}

		// destination
		if (!move.empty())
		{
			size_t len = move.length();
			if (move[len - 1] >= L'1' && move[len - 1] <= L'8')
			{
				ret.destination.row = move[len - 1] - L'1';
				move.pop_back();
			}
			len = move.length();
			if (!move.empty() && move[len - 1] >= L'a' && move[len - 1] <= L'h')
			{
				ret.destination.collumn = move[len - 1] - L'a';
				move.pop_back();
			}
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


		// destination
		//if (!move.empty()) // this will be non legit
		//{
		//	std::cout << "No valid destination! " << std::endl;
		//	return ret;
		//}
	}
	catch (...)
	{
		return getInvalidMove();
	}

	// special moves (castling, en-passant)

	return ret;
}

std::wstring GameUtils::removeUnnececeryEnding(std::wstring move)
{
	while (!move.empty() && (move.back() > L'8' or move.back() < L'1') &&
		move.back() != L'R' &&
		move.back() != L'r' &&
		move.back() != L'B' &&
		move.back() != L'b' &&
		move.back() != L'N' &&
		move.back() != L'n')
	{
		move.pop_back();
	}
	return move;
}

std::wstring GameUtils::removeX(std::wstring move)
{
	uint8_t j = 0;
	for (uint8_t i = 0; i < move.length(); i++)
	{
		if (move[i] != L'x' && move[i] != L'X')
		{
			move[j++] = move[i];
		}
	}
	//move[j] = '\0'; // Null-terminate the modified string
	move.resize(j);

	return move;
}
