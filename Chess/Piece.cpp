#include "Piece.h"



Piece::Piece(const PieceType type, const Color color, const Coordinate position)
	: type(type), color(color)
{
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


