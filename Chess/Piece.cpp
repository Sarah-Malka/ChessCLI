#include "Piece.h"
#include "exception.h"
#include "board.h"
#include <cmath>

bool Piece::IsStaying(const Coordinate targetPosition) const
{
	return ((targetPosition.row == position.row) && (targetPosition.collumn == position.collumn));
}

bool Piece::IsEatingHisColor(const Coordinate targetPosition, const Board& board) const
{
	if (board[targetPosition.row][targetPosition.collumn] != nullptr)
	{
		if (board[targetPosition.row][targetPosition.collumn]->getColor() == this->color)
		{
			return true;
		}
	}
}

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
	if (IsStaying(targetPosition))
	{
		return false;
	}
	if (IsEatingHisColor(targetPosition, board))
	{
		return false;
	}

	if (std::abs(position.row - targetPosition.row) > 1 || std::abs(position.collumn - targetPosition.collumn) > 1)
	{
		return false;
	}

	return true;
}
bool Pawn::IsValidMove(Coordinate targetPosition, const Board& board)
{
	if (GameInfo::WhiteToPlay)
	{
		if (this->position.collumn == targetPosition.collumn) // not a capture
		{
			if (this->position.row + 2 == targetPosition.row) // first time the pawn has moved?
			{
				if (this->position.row == 1 && board[this->position.row + 1][this->position.collumn + 1] == nullptr && board[this->position.row + 2][this->position.collumn + 2] == nullptr)// note that the row and collumn are in this order
				{
					return true;
				}
			}
		}
	}
}
