#include "Game.h"
#include <iostream>
#include "GameUtils.h"
#include "Exception.h"

std::vector<Piece*> Game::GetPossiblePiecesToMove(const singleMove move) const
{
	std::vector<Piece*> possiblePieces;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Piece* piece = game_info.board[i][j];
			if (piece == nullptr)
			{
				continue;
			}
			if (piece->getType() != move.originalPiece)
			{
				continue;
			}
			Color colorToPlay = game_info.WhiteToPlay ? Color::WHITE : Color::BLACK;
			if (piece->getColor() != colorToPlay)
			{
				continue;
			}

			if (!piece->IsValidMove(move.destination, game_info.board))
			{
				continue;
			}

			if (game_info.board.IsCheck(colorToPlay))
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
		game_info.board.PrintBoard();
		
		std::wcout << L"Enter " << (game_info.WhiteToPlay ? L"white's " : L"black's ") << L"move: " << std::endl;
		std::wstring str_move = L"";
		std::wcin >> str_move;

		try
		{
			singleMove move = GameUtils::stringToMove(str_move);
			std::vector<Piece*> possiblePieces = GetPossiblePiecesToMove(move);
			if (possiblePieces.empty())
			{
				throw Exception(ErrorCode::NoPieceCanMove);
			}
			if (possiblePieces.size() > 1)
			{
				throw Exception(ErrorCode::MoreThanOneCompatiblePiece);
			}
			Piece* pieceToMove = possiblePieces[0];
			game_info.board.Move(pieceToMove->getPosition(), move.destination);
			game_info.WhiteToPlay = !game_info.WhiteToPlay;
		}
		catch (Exception ex)
		{
			std::wcout << L"Error! ErrorCode: " << (int)ex.GetError() << std::endl;
			continue;
		}
	}
}
