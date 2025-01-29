#pragma comment(lib, "winmm.lib")

#include "Game.h"
#include <iostream>
#include "GameUtils.h"
#include "Exception.h"
#include <Windows.h>

std::vector<Piece*> Game::GetPossiblePiecesToMove(const singleMove move) const
{
	std::vector<Piece*> possiblePieces;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Piece* piece = board[i][j];
			if (piece == nullptr)
			{
				continue;
			}
			if (piece->getType() != move.originalPiece)
			{
				continue;
			}
			Color colorToPlay = GameInfo::WhiteToPlay ? Color::WHITE : Color::BLACK;
			if (piece->getColor() != colorToPlay)
			{
				continue;
			}

			if (!piece->IsValidMove(move.destination, board))
			{
				continue;
			}
			
			if (board.WillCauseCheck(colorToPlay, piece->getPosition(), move.destination))
			{
				continue;
			}

			possiblePieces.push_back(piece);
		}
	}

	return possiblePieces;
}

void Game::Start()
{
	while (true)
	{
		if (!invalid_input)
		{
			board.PrintBoard();
		}
		
		std::wcout << L"Enter " << (GameInfo::WhiteToPlay ? L"white's " : L"black's ") << L"move: " << std::endl;
		std::wstring str_move = L"";
		std::wcin >> str_move;

		try
		{
			singleMove move = GameUtils::stringToMove(str_move);
			std::vector<Piece*> possiblePieces = GetPossiblePiecesToMove(move);
			if (possiblePieces.empty())
			{
				throw Exception(ErrorCode::NoPieceCanMove, L"There is no compatible piece");
			}
			if (possiblePieces.size() > 1)
			{
				throw Exception(ErrorCode::MoreThanOneCompatiblePiece, L"Ambigious command, more than one piece can do this move");
			}
			Piece* pieceToMove = possiblePieces[0];
			board.Move(pieceToMove->getPosition(), move.destination);
			if (GameInfo::atelastMove)
			{
				PlaySoundW(TEXT("Sounds\\eat.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			else
			{
				PlaySoundW(TEXT("Sounds\\move.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			invalid_input = false;
			GameInfo::WhiteToPlay = !GameInfo::WhiteToPlay;
		}
		catch (Exception ex)
		{
			invalid_input = true;
			std::wcout << L"Error! ErrorCode " << (int)ex.GetError() << L": " << ex.Message() << std::endl;
			continue;
		}
	}
}
