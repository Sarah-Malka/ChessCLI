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

Piece* Piece::GetPiece(const PieceType type) const
{
	switch (type)
	{
	case PieceType::BISHOP:
		return new Bishop(color, position);
	case PieceType::KING:
		return new King(color, position);
	case PieceType::KNIGHT:
		return new Knight(color, position);
	case PieceType::PAWN:
		return new Pawn(color, position);
	case PieceType::QUEEN:
		return new Queen(color, position);
	case PieceType::ROCK:
		return new Rock(color, position);
	default:
		return nullptr;
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
		throw Exception(ErrorCode::PositaionOutOfBoard, L"Postition out of board");
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
bool Pawn::IsValidPieceMove(Coordinate targetPosition, const Board& board) const // unfinished
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
			//queening goes here
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
bool Knight::IsValidPieceMove(Coordinate targetPosition, const Board& board) const
{
	if (((abs(targetPosition.row - this->position.row) == 2) && (abs(targetPosition.collumn - this->position.collumn) == 1)) xor ((abs(targetPosition.row - this->position.row) == 1) && (abs(targetPosition.collumn - this->position.collumn) == 2)))
	{
		return true;
	}
	return false;
}
bool Bishop::IsValidPieceMove(Coordinate targetPosition, const Board& board) const
{
	if (!((this->position.row - this->position.collumn) == (targetPosition.row - targetPosition.collumn)) xor ((this->position.row + this->position.collumn) == (targetPosition.row + targetPosition.collumn)))
	{	
		return false;
	}
	//check if diagnol is empty
	std::vector<Coordinate> squaresInTheWay;
	if (this->position.row - this->position.collumn == targetPosition.row - targetPosition.collumn) //a1 to h8 type diagnal
	{
		int squareDiff = targetPosition.row - targetPosition.collumn;
		for (uint8_t i = std::min(position.row, targetPosition.row) + 1; i < std::max(position.row, targetPosition.row); i++) // add 1 to initial i to not chech the original square
		{

			squaresInTheWay.push_back(Coordinate{ i, unsigned char(i - squareDiff) }); //{row,collumn}
		}
	}
	else // a8 to h1 type diagnal
	{
		int squareDiff = targetPosition.row + targetPosition.collumn;
		for (uint8_t i = std::min(position.row, targetPosition.row) + 1; i < std::max(position.row, targetPosition.row); i++)
		{
			squaresInTheWay.push_back(Coordinate{ i, unsigned char(squareDiff - i) });
		}
	}

	for (int i = 0; i < squaresInTheWay.size(); i++)
	{
		if (board[squaresInTheWay[i]] != nullptr)
		{
			return false;
		}
	}

	return true;
}
bool Rock::IsValidPieceMove(Coordinate targetPosition, const Board& board) const
{
	if (targetPosition.row != position.row && targetPosition.collumn != position.collumn)
	{
		return false;
	}

	std::vector<Coordinate> squaresInTheWay;
	if (position.collumn == targetPosition.collumn)
	{
		for (uint8_t i = std::min(position.row, targetPosition.row) + 1; i < std::max(position.row, targetPosition.row); i++)
		{
			squaresInTheWay.push_back(Coordinate{ i, position.collumn });
		}
	}
	else
	{
		for (uint8_t i = std::min(position.collumn, targetPosition.collumn) + 1; i < std::max(position.collumn, targetPosition.collumn); i++)
		{
			squaresInTheWay.push_back(Coordinate{ position.row, i });
		}
	}

	for (int i = 0; i < squaresInTheWay.size(); i++)
	{
		if (board[squaresInTheWay[i]] != nullptr)
		{
			return false;
		}
	}

	return true;
}
bool Queen::IsValidPieceMove(Coordinate targetPosition, const Board& board) const
{
	Rock rock(color, position);
	Bishop bishop(color, position);

	return (rock.IsValidMove(targetPosition, board) || bishop.IsValidMove(targetPosition, board));
}