#include "Piece.h"
#include "exception.h"
#include "board.h"
#include <cmath>
#include "GameInfo.h"

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

Piece* Piece::GetCopy()
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

bool Piece::IsValidMove(const singleMove move, const Board& board) const
{
	const Coordinate targetPosition = move.destination;
	if (IsStaying(targetPosition))
	{
		return false;
	}
	if (IsEatingHisColor(targetPosition, board))
	{
		return false;
	}
	return IsValidPieceMove(move, board);
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

bool King::IsValidPieceMove(const singleMove move, const Board& board) const
{
	if (move.isCastlation)
	{
		if ((GameInfo::WhiteToPlay && GameInfo::whiteKingMoved) || (!GameInfo::WhiteToPlay && GameInfo::blackKingMoved))
		{
			return false; // TODO: make sure king move is changing the GameInfo::blackKingMoved value (same with the rocks)
			// TODO: complete castling logic and checks.
		}
		if (GameInfo::WhiteToPlay && ((move.destination.collumn == 6 && GameInfo::a8WhiteRockMoved) || (move.destination.collumn == 2 && GameInfo::a1WhiteRockMoved)))
		{
			return false;
		}
		if (!GameInfo::WhiteToPlay && ((move.destination.collumn == 6 && GameInfo::h8BlackRockMoved) || (move.destination.collumn == 2 && GameInfo::h1BlackRockMoved)))
		{
			return false;
		}

		//if (GameInfo::WhiteToPlay && there is nothing between the king and rock)
		//if (!GameInfo::WhiteToPlay && there is nothing between the king and rock)

		//if(king and two other squares are not in check)
	}
	if (std::abs(position.row - move.destination.row) > 1 || std::abs(position.collumn - move.destination.collumn) > 1)
	{
		return false;
	}

	return true;
}
bool Pawn::IsValidPieceMove(const singleMove move, const Board& board) const // unfinished
{
	if (this->color == Color::WHITE)
	{
		if (this->position.collumn == move.destination.collumn) // not a capture
		{
			if (this->position.row + 2 == move.destination.row) // first time the pawn has moved?
			{
				if (this->position.row == 1 && board[this->position.row + 1][this->position.collumn] == nullptr && board[this->position.row + 2][this->position.collumn] == nullptr)// note that the row and collumn are in this order
				{
					return true;
				}
				return false;
			}
			else if (this->position.row + 1 == move.destination.row && board[this->position.row + 1][this->position.collumn] == nullptr)
			{
				// something something queenning something?
				return true;
			}
			return false;
		}
		else if (this->position.collumn != move.destination.collumn) // this is a capture
		{
			if (this->position.collumn + 1 != move.destination.collumn && this->position.collumn - 1 != move.destination.collumn) //move exactly one to the side
			{
				return false;
			}
			if (this->position.row + 1 != move.destination.row)
			{
				return false;
			}
			if (board[move.destination.row][move.destination.collumn] == nullptr) //make sure there's something to eat
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
		if (this->position.collumn == move.destination.collumn) // not a capture
		{
			if (this->position.row - 2 == move.destination.row) // first time the pawn has moved?
			{
				if (this->position.row == 6 && board[this->position.row - 1][this->position.collumn] == nullptr && board[this->position.row - 2][this->position.collumn] == nullptr)// note that the row and collumn are in this order
				{
					return true;
				}
				return false;
			}
			else if (this->position.row - 1 == move.destination.row && board[this->position.row - 1][this->position.collumn] == nullptr)
			{
				// something something queenning something?
				return true;
			}
			return false;
		}
		else if (this->position.collumn != move.destination.collumn) // this is a capture
		{
			if (this->position.collumn - 1 != move.destination.collumn && this->position.collumn + 1 != move.destination.collumn) //move exactly one to the side
			{
				return false;
			}
			if (this->position.row - 1 != move.destination.row)
			{
				return false;
			}
			if (board[move.destination.row][move.destination.collumn] == nullptr) //make sure there's something to eat
			{
				// here goes some logic to allow en-passant
				return false;
			}
			return true;
		}
	}
}
bool Knight::IsValidPieceMove(const singleMove move, const Board& board) const
{
	if (((abs(move.destination.row - this->position.row) == 2) && (abs(move.destination.collumn - this->position.collumn) == 1)) xor ((abs(move.destination.row - this->position.row) == 1) && (abs(move.destination.collumn - this->position.collumn) == 2)))
	{
		return true;
	}
	return false;
}
bool Bishop::IsValidPieceMove(const singleMove move, const Board& board) const
{
	if (!((this->position.row - this->position.collumn) == (move.destination.row - move.destination.collumn)) xor ((this->position.row + this->position.collumn) == (move.destination.row + move.destination.collumn)))
	{	
		return false;
	}
	//check if diagnol is empty
	std::vector<Coordinate> squaresInTheWay;
	if (this->position.row - this->position.collumn == move.destination.row - move.destination.collumn) //a1 to h8 type diagnal
	{
		int squareDiff = move.destination.row - move.destination.collumn;
		for (uint8_t i = std::min(position.row, move.destination.row) + 1; i < std::max(position.row, move.destination.row); i++) // add 1 to initial i to not chech the original square
		{

			squaresInTheWay.push_back(Coordinate{ i, unsigned char(i - squareDiff) }); //{row,collumn}
		}
	}
	else // a8 to h1 type diagnal
	{
		int squareDiff = move.destination.row + move.destination.collumn;
		for (uint8_t i = std::min(position.row, move.destination.row) + 1; i < std::max(position.row, move.destination.row); i++)
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
bool Rock::IsValidPieceMove(const singleMove move, const Board& board) const
{
	if (move.destination.row != position.row && move.destination.collumn != position.collumn)
	{
		return false;
	}

	std::vector<Coordinate> squaresInTheWay;
	if (position.collumn == move.destination.collumn)
	{
		for (uint8_t i = std::min(position.row, move.destination.row) + 1; i < std::max(position.row, move.destination.row); i++)
		{
			squaresInTheWay.push_back(Coordinate{ i, position.collumn });
		}
	}
	else
	{
		for (uint8_t i = std::min(position.collumn, move.destination.collumn) + 1; i < std::max(position.collumn, move.destination.collumn); i++)
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
bool Queen::IsValidPieceMove(const singleMove move, const Board& board) const
{
	Rock rock(color, position);
	Bishop bishop(color, position);

	return (rock.IsValidMove(move, board) || bishop.IsValidMove(move, board));
}