#include "Game.h"
#include <iostream>
#include "GameUtils.h"
#include "Exception.h"
#include <Windows.h>

std::vector<Piece*> Game::GetPossiblePiecesToMove(const singleMove move)
{
	Color colorToPlay = GameInfo::WhiteToPlay ? Color::WHITE : Color::BLACK;
	std::vector<Piece*> possiblePiecesBeforeCheckValidation;
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
			if (piece->getColor() != colorToPlay)
			{
				continue;
			}

			// if player gave us the moving piece's origin location:
			if (!move.isCastlation) //if move is castling, we want a more indicative error, that will be returned in IsValidMove function
			{
				Coordinate origin = piece->getPosition();
				if (move.origin.collumn != 10) // 10 is the agreed-upon junk value
				{
					if (origin.collumn != move.origin.collumn)
					{
						last_relevant_move_error = ErrorCode::NoPieceFoundAtOriginPosition;
						continue;
					}
				}
				if (move.origin.row != 10)
				{
					if (origin.row != move.origin.row)
					{
						last_relevant_move_error = ErrorCode::NoPieceFoundAtOriginPosition;
						continue;
					}
				}
			}

			ErrorCode move_status = piece->IsValidMove(move, board);
			if (move_status != ErrorCode::Success)
			{
				if (move_status < last_relevant_move_error)
				{
					last_relevant_move_error = move_status;
				}
				continue;
			}

			possiblePiecesBeforeCheckValidation.push_back(piece);
		}
	}

	for (std::vector<Piece*>::iterator it = possiblePiecesBeforeCheckValidation.begin(); it != possiblePiecesBeforeCheckValidation.end(); ++it)
	{
		if (board.WillCauseCheck(colorToPlay, (*it)->getPosition(), move))
		{
			last_relevant_move_error = board.IsCheck(colorToPlay) ? ErrorCode::YouAreInCheck : ErrorCode::IllegalCheckExposure;
		}
		else
		{
			possiblePieces.push_back(*it);
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
		if (std::wcin.eof()) break; // quit if Ctrl+Z

		try
		{
			singleMove move = GameUtils::stringToMove(str_move); // get move Coordinates
			last_relevant_move_error = ErrorCode::Success;
			std::vector<Piece*> possiblePieces = GetPossiblePiecesToMove(move); // what piece might move there?
			if (possiblePieces.empty())
			{
				throw Exception(last_relevant_move_error, L"There is no compatible piece");
			}
			if (possiblePieces.size() > 1)
			{
				throw Exception(ErrorCode::MoreThanOneCompatiblePiece, L"Ambigious command");
			}
			Piece* pieceToMove = possiblePieces[0];
			board.Move(pieceToMove->getPosition(), move, true); // the actual moving
			GameUtils::GameSound(GameInfo::atelastMove);
			Sleep(130);
			invalid_input = false;
			GameInfo::WhiteToPlay = !GameInfo::WhiteToPlay;
		}
		catch (Exception ex)
		{
			invalid_input = true;
			std::wcout << ex.Message() << L". ErrorCode " << (int)ex.GetError() << L": " << errorCodeToMessage.at(ex.GetError()) << std::endl;
			continue;
		}
	}
}
