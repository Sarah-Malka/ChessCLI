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
			
			if (board.WillCauseCheck(colorToPlay, piece->getPosition(), move))
			{
				continue;
			}

			// if player gave us the moving piece's origin location:
			Coordinate origin = piece->getPosition();
			if (move.origin.collumn != 10) // 10 is the agreed-upon junk value
			{
				if (origin.collumn != move.origin.collumn)
				{
					continue;
				}
			}
			if (move.origin.row != 10)
			{
				if (origin.row != move.origin.row)
				{
					continue;
				}
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
			board.Move(pieceToMove->getPosition(), move);
			//check if coronation needs to happen, if no coronation request was submitted but a pawn is on 8 or 1 rank, handle
			GameUtils::GameSound(GameInfo::atelastMove);
			Sleep(130);
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
