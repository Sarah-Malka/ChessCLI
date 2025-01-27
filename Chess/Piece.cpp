#include "Piece.h"
#include "exception.h"
#include "board.h"
#include <cmath>

Piece::Piece(const PieceType type, const Color color, const Coordinate position)
	: type(type), color(color)
{
	if (position.row > 7 || position.collumn > 7)
	{
		throw Exception(ErrorCode::PositaionOutOfBoard);
	}
	this->position.collumn = position.collumn;
	this->position.row = position.row;
}

Piece::Piece(PieceType type, Color color, uint8_t row, uint8_t colomn) :
	Piece(type, color, Coordinate{ row, colomn }
)
{

}

void Piece::Move(Coordinate targetPosition)
{
	position.collumn = targetPosition.collumn;
	position.row = targetPosition.row;
}

PieceType Piece::getType() const
{
	return type;
}

Color Piece::getColor() const
{
	return color;
}

bool King::IsValidMove(Coordinate targetPosition, const Board& board)
{
	int row = this->position.row;
	int colomn = this->position.collumn;
	int targetRow = targetPosition.row;
	int targetColomn = targetPosition.collumn;

	if (board[targetRow][targetColomn] != nullptr)
	{
		if (board[targetRow][targetColomn]->getColor() == this->color)
		{
			return false;
		}
	}

	if ((targetPosition.row == position.row) && (targetPosition.collumn == position.collumn))
	{
		return false;
	}

	if (std::abs(position.row - targetPosition.row) > 1 || std::abs(position.collumn - targetPosition.collumn) > 1)
	{
		return false;
	}

	return true;
}
