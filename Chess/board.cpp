#include "board.h"
#include "VisualUtils.h"
#include "GameInfo.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>

Board::Board() :
	kings_locations({ Coordinate{0,4}, Coordinate{7,4} })
{
	board = GetToInitialState();
}

Board::~Board()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] != nullptr)
			{
				delete board[i][j];
				board[i][j] = nullptr;
			}
		}
	}
}

std::vector<Piece*>& Board::operator[](std::size_t index)
{
	return board[index];
}

const std::vector<Piece*> Board::operator[](std::size_t index) const
{
	return board[index];
}

Piece*& Board::operator[](Coordinate position)
{
	return board[position.row][position.collumn];
}

Piece* const Board::operator[](Coordinate position) const
{
	return board[position.row][position.collumn];
}

void ChangeColor()
{
	static bool white = 0;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if (!white)
	{
		SetConsoleTextAttribute(hStdOut, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	}
	else
	{
		SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	}
	white = !white;
}

void DefaultColor()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void RedColor(const Color foreground)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (foreground == Color::BLACK)
	{
		SetConsoleTextAttribute(hStdOut, BACKGROUND_RED);
	}
	else
	{
		SetConsoleTextAttribute(hStdOut, BACKGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	}
}

void Board::PrintBoard() const
{
	std::cout << std::endl;
	for (int i = 7; i >= 0; i--)
	{
		DefaultColor();
		std::wcout << i+1 << L" ";
		for (int j = 0; j < 8; j++)
		{
			ChangeColor();
			Piece* piece = board[i][j];
			if (piece == nullptr)
			{
				std::wcout << L"  ";
				continue;
			}
			bool flipColor = ((i + j) % 2 == 0);
			wchar_t PieceType_symbol = VisualUtils::GetPieceRepresentation(piece->getColor(), piece->getType(), flipColor);
			if (piece->getType() == PieceType::KING && IsCheck(piece->getColor()))
			{
				PieceType_symbol = L'\u265A';
				RedColor(piece->getColor());
			}
			std::wcout << PieceType_symbol << L" ";
		}
		DefaultColor();
		std::cout << std::endl;
		ChangeColor();
	}
	DefaultColor();
	std::wcout << L"  a b c d e f g h";
	std::cout << std::endl;

}

Coordinate GetCastlationRockSourcePosition(singleMove move)
{
	Coordinate rockPosition = { 10,10 };
	bool isKingSideCastelation = move.destination.collumn == 6;
	rockPosition.collumn = isKingSideCastelation ? 7 : 0;
	rockPosition.row = GameInfo::WhiteToPlay ? 0 : 7;

	return rockPosition;
}

Coordinate GetCastlationRockTargetPosition(singleMove move)
{
	Coordinate rockPosition = { 10,10 };
	bool isKingSideCastelation = move.destination.collumn == 6;
	rockPosition.collumn = isKingSideCastelation ? 5 : 3;
	rockPosition.row = GameInfo::WhiteToPlay ? 0 : 7;

	return rockPosition;
}

void Board::Move(const Coordinate source, const singleMove move, bool realMove) // this is the actual moving
{
	Piece* sourcePiece = board[source.row][source.collumn];
	Piece* destPiece = board[move.destination.row][move.destination.collumn];

	if (move.isCastlation)
	{
		Coordinate RockSourcePosition = GetCastlationRockSourcePosition(move);
		Coordinate RockTargetPosition = GetCastlationRockTargetPosition(move);

		Piece* Rock = operator[](RockSourcePosition);
		operator[](RockSourcePosition) = nullptr;
		operator[](RockTargetPosition) = Rock;
		Rock->Move(RockTargetPosition);
	}

	board[source.row][source.collumn] = nullptr; // because the piece moved from there
	board[move.destination.row][move.destination.collumn] = sourcePiece;
	sourcePiece->Move(move.destination);

	// if en-passant
	if (sourcePiece->getType() == PieceType::PAWN && sourcePiece->getPosition() == GameInfo::pawnSkippedThisSquareLastTurn)
	{
		Coordinate capturedPawnCoordinate = { sourcePiece->getColor() ==  Color::BLACK ? (uint8_t)3 : (uint8_t)4, sourcePiece->getPosition().collumn };
		delete board[capturedPawnCoordinate.row][capturedPawnCoordinate.collumn];
		board[capturedPawnCoordinate.row][capturedPawnCoordinate.collumn] = nullptr;
	}
	if (sourcePiece->getType() == PieceType::KING)
	{
		kings_locations[sourcePiece->getColor()] = sourcePiece->getPosition();
	}

	if (realMove)
	{
		// Set global game info variables
		if (sourcePiece->getType() == PieceType::KING)
		{
			if (sourcePiece->getColor() == WHITE)
			{
				GameInfo::whiteKingMoved = true;
			}
			else
			{
				GameInfo::blackKingMoved = true;
			}
		}
		if (sourcePiece->getType() == PieceType::ROCK)
		{
			if (sourcePiece->getColor() == WHITE)
			{
				if (sourcePiece->getPosition() == Coordinate{ 0,0 })
					GameInfo::a1WhiteRockMoved = true;
				else if (sourcePiece->getPosition() == Coordinate{ 0,7 })
					GameInfo::a8WhiteRockMoved = true;
			}
			else
			{
				if (sourcePiece->getPosition() == Coordinate{ 7,0 })
					GameInfo::h1BlackRockMoved = true;
				else if (sourcePiece->getPosition() == Coordinate{ 7,7 })
					GameInfo::h8BlackRockMoved = true;
			}
		}
		if (sourcePiece->getType() == PieceType::PAWN)
		{
			GameInfo::numberOfMovesFor50MoveRule = 0;
		}
		GameInfo::atelastMove = destPiece != nullptr;
		if (GameInfo::doubleMoveWasAttemptedThisTurn)
		{
			GameInfo::pawnSkippedThisSquareLastTurn = { sourcePiece->getColor() == Color::WHITE ? (uint8_t)2 : (uint8_t)5, sourcePiece->getPosition().collumn };
		}
		else
		{
			GameInfo::pawnSkippedThisSquareLastTurn = { GameInfo::outOfBoardRange, GameInfo::outOfBoardRange };
		}
	}

	if (shouldCoronate(move))
	{
		(*this)[move.destination] = sourcePiece->GetPiece(move.coronationRequest);
		delete sourcePiece;
		sourcePiece = (*this)[move.destination];
	}
}

bool Board::IsCheck(const Color color) const
{
	return IsCheck(color, kings_locations[color]);
}

bool Board::IsCheck(const Color color, Coordinate king_location) const
{
	singleMove captureKing;
	captureKing.destination = king_location;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] == nullptr)
			{
				continue;
			}
			if (board[i][j]->getColor() == color)
			{
				continue;
			}
			if (board[i][j]->IsValidMove(captureKing, *this) == ErrorCode::Success)
			{
				return true;
			}
		}
	}

	return false;
}

bool Board::WillCauseCheck(const Color color, const Coordinate source, const singleMove move) const
{
	Board copy_board(*this);
	copy_board.Move(source, move, false);
	return copy_board.IsCheck(color);
}

bool Board::isCheckmate()
{
	return false;
}

bool Board::isStalemate()
{
	return false;
}

Board::Board(const Board& other) // copy constructor
	: kings_locations(other.kings_locations)
{
	board.resize(8);
	for (int i = 0; i < 8; i++)
	{
		board[i].resize(8);
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Piece* otherPiece = other.board[i][j];
			if (otherPiece == nullptr)
			{
				board[i][j] = nullptr;
				continue;
			}
			board[i][j] = otherPiece->GetPiece(otherPiece->getType());
		}
	}
}

bool Board::shouldCoronate(singleMove move)
{
	if (move.originalPiece != PieceType::PAWN)
	{
		return false;
	}
	if (!(move.destination.row == 7 && GameInfo::WhiteToPlay) && !(move.destination.row == 0 && !GameInfo::WhiteToPlay))
	{
		return false;
	}

	return true;
}

array2D Board::GetToInitialState()
{
	array2D init = {
		{new Rock(Color::WHITE, 0, 0), new Knight(Color::WHITE, 0, 1), new Bishop(Color::WHITE, 0, 2), new Queen(Color::WHITE, 0, 3), new King(Color::WHITE, 0, 4), new Bishop(Color::WHITE, 0, 5), new Knight(Color::WHITE, 0, 6), new Rock(Color::WHITE, 0, 7)},
		{new Pawn(Color::WHITE, 1, 0), new Pawn(Color::WHITE, 1, 1), new Pawn(Color::WHITE, 1, 2), new Pawn(Color::WHITE, 1, 3), new Pawn(Color::WHITE, 1, 4), new Pawn(Color::WHITE, 1, 5), new Pawn(Color::WHITE, 1, 6), new Pawn(Color::WHITE, 1, 7)},
		{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
		{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
		{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
		{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
		{new Pawn(Color::BLACK, 6, 0), new Pawn(Color::BLACK, 6, 1), new Pawn(Color::BLACK, 6, 2), new Pawn(Color::BLACK, 6, 3), new Pawn(Color::BLACK, 6, 4), new Pawn(Color::BLACK, 6, 5), new Pawn(Color::BLACK, 6, 6), new Pawn(Color::BLACK, 6, 7)},
		{new Rock(Color::BLACK, 7, 0), new Knight(Color::BLACK, 7, 1), new Bishop(Color::BLACK, 7, 2), new Queen(Color::BLACK, 7, 3), new King(Color::BLACK, 7, 4), new Bishop(Color::BLACK, 7, 5), new Knight(Color::BLACK, 7, 6), new Rock(Color::BLACK, 7, 7)}
	};
	return init;
}