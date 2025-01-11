#include "board.h"
#include <iostream>
bool Board::alreadyCreated = false;

Board::Board()
{
	board = GetInitialState();
}

void Board::PrintBoard() const
{

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			std::cout << int(board[i][j].piece) << " ";
		}
		std::cout << std::endl;
	}
}

array2D Board::GetInitialState()
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

void stam()
{
	int a = 7;
	int* pointer;
	pointer = &a;
}