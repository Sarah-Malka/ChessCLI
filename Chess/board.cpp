#include "board.h"
#include <iostream>
bool Board::alreadyCreated = false;

Board::Board()
{
	board = GetToInitialState();
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