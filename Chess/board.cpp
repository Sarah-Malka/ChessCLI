#include "board.h"
#include "VisualUtils.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>

bool Board::alreadyCreated = false;

Board::Board()
{
	board = GetToInitialState();
}

std::vector<Piece*>& Board::operator[](std::size_t index)
{
	return board[index];
}

const std::vector<Piece*> Board::operator[](std::size_t index) const
{
	return board[index];
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

void Board::PrintBoard() const
{
	for (int i = 7; i >= 0; i--)
	{
		for (int j = 0; j < 8; j++)
		{
			ChangeColor();
			if (board[i][j] == nullptr)
			{
				std::wcout << L"  ";
				continue;
			}
			bool flipColor = ((i + j) % 2 == 0);
			wchar_t PieceType_symbol = VisualUtils::GetPieceRepresentation(board[i][j]->getColor(), board[i][j]->getType(), flipColor);
			std::wcout << PieceType_symbol << L" ";
		}
		DefaultColor();
		std::cout << std::endl;
		ChangeColor();
	}
	DefaultColor();

	std::cout << std::endl;

}

void Board::Move(const Coordinate source, const Coordinate dest)
{
	Piece* sourcePiece = board[source.row][source.collumn];
	board[source.row][source.collumn] = nullptr;
	board[dest.row][dest.collumn] = sourcePiece;

	sourcePiece->Move(dest);
}

bool Board::isCheckmate()
{
	return false;
}

bool Board::isStalemate()
{
	return false;
}

array2D Board::GetToInitialState()
{
	array2D init = {
		{new Rock(Color::WHITE, 0, 0), new Knight(Color::WHITE, 0, 1), new Bishop(Color::WHITE, 0, 2), new Queen(Color::WHITE, 0, 3), new King(Color::WHITE, 0, 4), new Bishop(Color::WHITE, 0, 5), new Knight(Color::WHITE, 0, 6), new Rock(Color::WHITE, 0, 7)},
		{new Pawn(Color::WHITE, 1, 0), new Pawn(Color::WHITE, 1, 1), new Pawn(Color::WHITE, 1, 2), new Pawn(Color::WHITE, 1, 3), new Pawn(Color::WHITE, 1, 4), new Pawn(Color::WHITE, 1, 5), new Pawn(Color::WHITE, 1, 6), new Pawn(Color::WHITE, 1, 7)},
		{nullptr, new King(Color::WHITE, 2, 1), nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
		{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
		{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
		{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
		{new Pawn(Color::BLACK, 6, 0), new Pawn(Color::BLACK, 6, 1), new Pawn(Color::BLACK, 6, 2), new Pawn(Color::BLACK, 6, 3), new Pawn(Color::BLACK, 6, 4), new Pawn(Color::BLACK, 6, 5), new Pawn(Color::BLACK, 6, 6), new Pawn(Color::BLACK, 6, 7)},
		{new Rock(Color::BLACK, 7, 0), new Knight(Color::BLACK, 7, 1), new Bishop(Color::BLACK, 7, 2), new Queen(Color::BLACK, 7, 3), new King(Color::BLACK, 7, 4), new Bishop(Color::BLACK, 7, 5), new Knight(Color::BLACK, 7, 6), new Rock(Color::BLACK, 7, 7)}
	};
	return init;
}


void stam()
{
	int a = 7;
	int* pointer;
	pointer = &a;
}