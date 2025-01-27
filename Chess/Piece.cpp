#include "Piece.h"
#include "exception.h"


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

bool Pawn::IsValidMove(Coordinate targetPosition, const Board& board)
{
	if (GameInfo::WhiteToPlay)
	{
		if (this->position.collumn == targetPosition.collumn) // not a capture
			if (this->position.row + 2 == targetPosition.row) // first time the pawn has moved?
			{
				if (this->position.row == 1 && board[0][0] == )
			}
	}
}
