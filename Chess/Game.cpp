#include "Game.h"
#include <iostream>
#include "GameUtils.h"
#include "Exception.h"
#include <Windows.h>

void Game::Start()
{
	board.AppendCurrentStateToHashMap();

	while (true)
	{
		if (!invalid_move)
		{
			board.PrintBoard();
			
			if (GameInfo::atelastMove)
			{
				GameInfo::numberOfMovesFor50MoveRule = 0;
				GameInfo::number_of_pieces_on_board -= 1;
			}
		}

		if (GameHasEnded())
		{
			Color color = WHITE;
			if (GameInfo::WhiteToPlay == false)
			{
				color = BLACK;
			}

			if (board.isCheckmated(color))
			{
				std::wcout << (GameInfo::WhiteToPlay ? L"0-1\n" : L"1-0\n") << L"Checkmate, " << (GameInfo::WhiteToPlay ? L"black " : L"white ") << L"wins!\n";
			}
			else
			{
				std::wcout << L'\u00BD' << L"-" << L'\u00BD' << L"\nDraw!\n";
			}
			break;
		}

		std::wcout << L"Enter " << (GameInfo::WhiteToPlay ? L"white's " : L"black's ") << L"move: " << std::endl;
		std::wstring str_move = L"";
		std::wcin >> str_move;
		if (std::wcin.eof()) break; // quit if Ctrl+Z

		try
		{
			singleMove move = GameUtils::stringToMove(str_move); // get move Coordinates
			if (move.destination.row == GameUtils::NonValideIndex || move.destination.collumn == GameUtils::NonValideIndex)
			{
				throw Exception(ErrorCode::FailedParsingMove);
			}
			last_relevant_move_error = ErrorCode::Success;	// initializations of start of turn
			GameInfo::doubleMoveWasAttemptedThisTurn = false;

			std::vector<Piece*> possiblePieces = GetPossiblePiecesToMove(move); // what piece might move there?
			if (possiblePieces.empty())
			{
				throw Exception(last_relevant_move_error);
			}
			if (possiblePieces.size() > 1)
			{
				throw Exception(ErrorCode::MoreThanOneCompatiblePiece);
			}
			Piece* pieceToMove = possiblePieces[0];
			board.Move(pieceToMove->getPosition(), move, true); // the actual moving
			GameUtils::GameSound(GameInfo::atelastMove);
			Sleep(130);
			invalid_move = false;
			GameInfo::numberOfMovesFor50MoveRule += 1;

			if (GameInfo::atelastMove || move.originalPiece == PAWN)
			{
				board.ClearHashMap();
			}
			if (!EnPassantPrivilegesExists())
			{
				board.AppendCurrentStateToHashMap();
			}

			GameInfo::WhiteToPlay = !GameInfo::WhiteToPlay; // has to go after the hash updater
		}
		catch (Exception ex)
		{
			invalid_move = true;
			std::wcout << L"ErrorCode " << (int)ex.GetError() << L": " << errorCodeToMessage.at(ex.GetError()) << std::endl;
			continue;
		}
	}
}

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
			last_relevant_move_error = board.IsInCheck(colorToPlay) ? ErrorCode::YouAreInCheck : ErrorCode::IllegalCheckExposure;
		}
		else
		{
			possiblePieces.push_back(*it);
		}
	}
	return possiblePieces;
}

bool Game::GameHasEnded()
{
	//TODO
	// draw offer/surrender

	if (GameInfo::numberOfMovesFor50MoveRule > 100)
	{
		return true;
	}

	if (board.ThreeFoldRepetition())
	{
		return true;
	}

	if (board.InsufficientMaterial())
	{
		return true;
	}

	Color color = GameInfo::WhiteToPlay ? Color::WHITE : Color::BLACK;
	if (!board.LegalMoveExists(color))
	{
		return true;
	}
	
	return false;
}

bool Game::EnPassantPrivilegesExists()
{
	const int rowOffset = GameInfo::WhiteToPlay ? +1 : -1;
	Color ColorDoingTheEnPassant = GameInfo::WhiteToPlay ? Color::BLACK : Color::WHITE;

	Coordinate skippedSquare = GameInfo::pawnSkippedThisSquareLastTurn;
	Coordinate OutOfRange = { GameInfo::outOfBoardRange, GameInfo::outOfBoardRange };
	if (skippedSquare == OutOfRange)
	{
		return false;
	}

	if (skippedSquare.collumn < 7)
	{
		Piece* capturingPiece = board[skippedSquare.row + rowOffset][skippedSquare.collumn + 1];
		if (capturingPiece != nullptr
			&& capturingPiece->getType() == PieceType::PAWN
			&& capturingPiece->getColor() == ColorDoingTheEnPassant)
		{
			Coordinate EnPassantOriginSquare = { skippedSquare.row + rowOffset,skippedSquare.collumn + 1 };
			singleMove Capture = { OutOfRange, skippedSquare, PieceType::PAWN, PieceType::INVALID, false };

			if (!board.WillCauseCheck(ColorDoingTheEnPassant, EnPassantOriginSquare, Capture))
			{
				return true;
			}
		}
	}
	if (GameInfo::pawnSkippedThisSquareLastTurn.collumn > 0)
	{
		Piece* capturingPiece = board[skippedSquare.row + rowOffset][skippedSquare.collumn - 1];
		if (capturingPiece != nullptr
			&& capturingPiece->getType() == PieceType::PAWN
			&& capturingPiece->getColor() == ColorDoingTheEnPassant)
		{
			Coordinate EnPassantOriginSquare = { skippedSquare.row + rowOffset,skippedSquare.collumn - 1 };
			singleMove Capture = { OutOfRange, skippedSquare, PieceType::PAWN, PieceType::INVALID, false };

			if (!board.WillCauseCheck(ColorDoingTheEnPassant, EnPassantOriginSquare, Capture))
			{
				return true;
			}
		}
	}

	return false;
}
