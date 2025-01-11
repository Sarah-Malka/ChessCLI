#include "board.h"
#include "VisualUtils.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
bool Board::alreadyCreated = false;

Board::Board()
{
	board = GetToInitialState();
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

void Board::PrintBoard() const
{
	for (int i = 7; i >= 0; i--)
	{
		for (int j = 0; j < 8; j++)
		{
			ChangeColor();
			if (!board[i][j].occupied)
			{
				std::wcout << L"0 ";
				continue;
			}
			bool flipColor = ((i + j) % 2 == 1);
			wchar_t piece_symbol = VisualUtils::GetPieceRepresentation(board[i][j].color, board[i][j].piece, flipColor);
			std::wcout << piece_symbol << L" ";
		}
		std::cout << std::endl;
		ChangeColor();
	}
}

array2D Board::GetToInitialState()
{
	array2D init = {
		{{true, Color::WHITE, Piece::ROCK}, { true, Color::WHITE, Piece::KNIGHT }, {true, Color::WHITE, Piece::BISHOP}, { true, Color::WHITE, Piece::QUEEN }, {true, Color::WHITE, Piece::KING}, { true, Color::WHITE, Piece::BISHOP }, {true, Color::WHITE, Piece::KNIGHT}, { true, Color::WHITE, Piece::ROCK }},
		{{true, Color::WHITE, Piece::PAWN}, { true, Color::WHITE, Piece::PAWN }, {true, Color::WHITE, Piece::PAWN}, { true, Color::WHITE, Piece::PAWN }, {true, Color::WHITE, Piece::PAWN}, { true, Color::WHITE, Piece::PAWN }, {true, Color::WHITE, Piece::PAWN}, { true, Color::WHITE, Piece::PAWN }},
		{{false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}},
		{{false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}},
		{{false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}},
		{{false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}},
		{{true, Color::BLACK, Piece::PAWN}, { true, Color::BLACK, Piece::PAWN }, {true, Color::BLACK, Piece::PAWN}, { true, Color::BLACK, Piece::PAWN }, {true, Color::BLACK, Piece::PAWN}, { true, Color::BLACK, Piece::PAWN }, {true, Color::BLACK, Piece::PAWN}, { true, Color::BLACK, Piece::PAWN }},
		{{true, Color::BLACK, Piece::ROCK}, { true, Color::BLACK, Piece::KNIGHT }, {true, Color::BLACK, Piece::BISHOP}, { true, Color::BLACK, Piece::QUEEN }, {true, Color::BLACK, Piece::KING}, { true, Color::BLACK, Piece::BISHOP }, {true, Color::BLACK, Piece::KNIGHT}, { true, Color::BLACK, Piece::ROCK }}
	};
	return init;
}

bool Board::isValidMove(struct singleMove)
{
	// color of the starting piece matching the players turn
	// can the type of piece move this way?
	// use "isCheck(color)" function
	// any blocking pieces?
	// special moves (castling, en-passant)
	// pawn moves (can go only to empty, can capture only to filled)

	return false;
}

singleMove Board::StringToMove(char* move)
{
	// define return var
	singleMove ret;
	ret.origin.collumn = 0;
	ret.origin.row= 0;
	ret.destination.collumn = 0;
	ret.destination.row= 0;

	// find what piece is moving: piece type, what piece can get there.
	// if it ends with "=Q", with "3" or with "+" then handel. before them will be the destination square
	// maybe unless the moving piece was a pawn, which you can know by seeing if the first letter is capital
	// if an "x" was out of place but the move was legal, mention that (and ask if sure?)

	return ret;
}



void stam()
{
	int a = 7;
	int* pointer;
	pointer = &a;
}