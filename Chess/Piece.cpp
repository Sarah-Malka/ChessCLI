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

bool Piece::IsValidMove(const Coordinate targetPosition, const Board& board) const
{
	if (IsStaying(targetPosition))
	{
		return false;
	}
	if (IsEatingHisColor(targetPosition, board))
	{
		return false;
	}
	return IsValidPieceMove(targetPosition, board);
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

Coordinate Piece::getPosition() const
{
	return position;
}

bool King::IsValidPieceMove(Coordinate targetPosition, const Board& board) const
{
	if (std::abs(position.row - targetPosition.row) > 1 || std::abs(position.collumn - targetPosition.collumn) > 1)
	{
		return false;
	}

	return true;
}
bool Pawn::IsValidPieceMove(Coordinate targetPosition, const Board& board) const
{
	if (this->color == Color::WHITE)
	{
		if (this->position.collumn == targetPosition.collumn) // not a capture
		{
			if (this->position.row + 2 == targetPosition.row) // first time the pawn has moved?
			{
				if (this->position.row == 1 && board[this->position.row + 1][this->position.collumn] == nullptr && board[this->position.row + 2][this->position.collumn] == nullptr)// note that the row and collumn are in this order
				{
					return true;
				}
				return false;
			}
			else if (this->position.row + 1 == targetPosition.row && board[this->position.row + 1][this->position.collumn] == nullptr)
			{
				// something something queenning something?
				return true;
			}
			return false;
		}
		else if (this->position.collumn != targetPosition.collumn) // this is a capture
		{
			if (this->position.collumn + 1 != targetPosition.collumn && this->position.collumn - 1 != targetPosition.collumn) //move exactly one to the side
			{
				return false;
			}
			if (this->position.row + 1 != targetPosition.row)
			{
				return false;
			}
			if (board[targetPosition.row][targetPosition.collumn] == nullptr) //make sure there's something to eat
			{
				// here goes some logic to allow en-passant
				return false;
			}
			return true;
		}
	}
	else if (this->color == Color::BLACK)
	{
		if (this->position.collumn == targetPosition.collumn) // not a capture
		{
			if (this->position.row - 2 == targetPosition.row) // first time the pawn has moved?
			{
				if (this->position.row == 6 && board[this->position.row - 1][this->position.collumn] == nullptr && board[this->position.row - 2][this->position.collumn] == nullptr)// note that the row and collumn are in this order
				{
					return true;
				}
				return false;
			}
			else if (this->position.row - 1 == targetPosition.row && board[this->position.row - 1][this->position.collumn] == nullptr)
			{
				// something something queenning something?
				return true;
			}
			return false;
		}
		else if (this->position.collumn != targetPosition.collumn) // this is a capture
		{
			if (this->position.collumn - 1 != targetPosition.collumn && this->position.collumn + 1 != targetPosition.collumn) //move exactly one to the side
			{
				return false;
			}
			if (this->position.row - 1 != targetPosition.row)
			{
				return false;
			}
			if (board[targetPosition.row][targetPosition.collumn] == nullptr) //make sure there's something to eat
			{
				// here goes some logic to allow en-passant
				return false;
			}
			return true;
		}
	}
}