#include "Piece.h"
#include "exception.h"
#include "board.h"
#include <cmath>
#include "GameInfo.h"

#define THROW_OR_RETURN_FALSE(throw_on_error, error_code, message)	if ((throw_on_error)) {throw Exception((error_code), (message));} else {return false;}


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

	return false;
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

ErrorCode Piece::IsValidMove(const singleMove move, const Board& board) const
{
	const Coordinate targetPosition = move.destination;
	if (IsStaying(targetPosition))
	{
		return ErrorCode::TargetPositionIsCurrentPosition;
	}
	if (IsEatingHisColor(targetPosition, board))
	{
		return ErrorCode::SquareOccupiedByYourOwnPiece;
	}
	return IsValidPieceMove(move, board);
}

Piece::Piece(const PieceType type, const Color color, const Coordinate position)
	: type(type), color(color)
{
	if (position.row > 7 || position.collumn > 7)
	{
		throw Exception(ErrorCode::PositionOutOfBoard, L"Position out of board");
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

ErrorCode King::IsValidPieceMove(const singleMove move, const Board& board) const
{
	if (move.isCastlation)
	{
		bool isKingSideCastelation = move.destination.collumn == 6;
		// no king has moved
		if ((GameInfo::WhiteToPlay && GameInfo::whiteKingMoved) || (!GameInfo::WhiteToPlay && GameInfo::blackKingMoved))
		{
			return ErrorCode::KingAlreadyMoved;
			// TODO: make sure king move is changing the GameInfo::blackKingMoved value (same with the rocks)
		}

		// relevant Rock hasn't moved (white)
		if (GameInfo::WhiteToPlay && ((isKingSideCastelation && GameInfo::a8WhiteRockMoved) || (!isKingSideCastelation && GameInfo::a1WhiteRockMoved)))
		{
			return ErrorCode::RockAlreadyMoved;
		}

		// relevant Rock hasn't moved (black)
		if (!GameInfo::WhiteToPlay && ((isKingSideCastelation && GameInfo::h8BlackRockMoved) || (!isKingSideCastelation && GameInfo::h1BlackRockMoved)))
		{
			return ErrorCode::RockAlreadyMoved;
		}

		Color colorToPlay = GameInfo::WhiteToPlay ? Color::WHITE : Color::BLACK;

		//there is nothing between King and Rock
		for (uint8_t i = !isKingSideCastelation ? 1 : 5; i < (!isKingSideCastelation ? 4:7); i++)
		{
			Coordinate coor = { GameInfo::WhiteToPlay ? 0 : 7, i };
			if (board[coor] != nullptr)
			{
				return ErrorCode::SquaresNotEmptyBetweenKingAndRock;
			}
		}

		// there is no check in kingSquare to destinationSquare
		for (uint8_t i = std::min(position.collumn, move.destination.collumn); i <= std::max(position.collumn, move.destination.collumn); i++)
		{
			Coordinate coor = { GameInfo::WhiteToPlay ? 0 : 7, i };
			if (board.IsCheck(colorToPlay, coor))
			{
				return ErrorCode::IllegalCheckExposureDuringCastlation;
			}
		}
		return ErrorCode::Success;
	}

	if (std::abs(position.row - move.destination.row) > 1 || std::abs(position.collumn - move.destination.collumn) > 1)
	{
		return ErrorCode::KingCanMoveOnlyOneSquare;
	}

	return ErrorCode::Success;
}

ErrorCode Pawn::IsValidDoubleStep(const singleMove move, const Board& board) const
{
	if (!DidNotMove())
	{
		return ErrorCode::PawnAlreadyMoved;
	}
	if (board[move.destination] != nullptr)
	{
		return ErrorCode::SquareIsOccupied;
	}
	Coordinate squareInTheWay = { color == Color::WHITE ? 2 : 5, position.collumn }; // note that the row and collumn are in this order
	if (board[squareInTheWay] != nullptr)
	{
		return ErrorCode::CannotGoThroughOtherPieces;
	}
	return ErrorCode::Success;
}
bool Pawn::DidNotMove() const
{
	return (color == Color::WHITE && position.row == 1) || (color == Color::BLACK && position.row == 6);
}
bool Pawn::IsMovingForward(const singleMove move) const
{
	return (color == Color::WHITE && move.destination.row > position.row) || (color == Color::BLACK && move.destination.row < position.row);
}
ErrorCode Pawn::IsValidCapture(const singleMove move, const Board& board) const
{
	if (this->position.collumn + 1 != move.destination.collumn && this->position.collumn - 1 != move.destination.collumn) //move exactly one to the side
	{
		return ErrorCode::InvalidPawnMove;
	}
	if ((this->color == Color::WHITE && this->position.row + 1 != move.destination.row) || (this->color == Color::BLACK && this->position.row -1 != move.destination.row))
	{
		return ErrorCode::InvalidPawnMove;
	}
	if (board[move.destination.row][move.destination.collumn] == nullptr) //make sure there's something to eat
	{
		// here goes some logic to allow en-passant
		return ErrorCode::NoOpponentPieceToEat;
	}
	return ErrorCode::Success;
}
ErrorCode Pawn::IsValidPieceMove(const singleMove move, const Board& board) const // unfinished
{
	if (!IsMovingForward(move))
	{
		return ErrorCode::PawnMustMoveForward;
	}
	if (this->position.collumn != move.destination.collumn)
	{
		return IsValidCapture(move, board);
	}
	if (abs(position.row - move.destination.row) == 2) // first time the pawn has moved?
	{
		return IsValidDoubleStep(move, board);
	}
	if (abs(position.row - move.destination.row) != 1)
	{
		return ErrorCode::PawnCanMoveOnlyOneSquare;
	}
	if (board[move.destination] != nullptr)
	{
		// something something queenning something?
		return ErrorCode::SquareIsOccupied;
	}
	return ErrorCode::Success;
	//
	//else if (this->color == Color::BLACK)
	//{
	//	if (this->position.collumn == move.destination.collumn) // not a capture
	//	{
	//		if (this->position.row - 2 == move.destination.row) // first time the pawn has moved?
	//		{
	//			if (this->position.row == 6 && board[this->position.row - 1][this->position.collumn] == nullptr && board[this->position.row - 2][this->position.collumn] == nullptr)// note that the row and collumn are in this order
	//			{
	//				return ErrorCode::Success;
	//			}
	//			return false;
	//		}
	//		else if (this->position.row - 1 == move.destination.row && board[this->position.row - 1][this->position.collumn] == nullptr)
	//		{
	//			// something something queenning something?
	//			return ErrorCode::Success;
	//		}
	//		return false;
	//	}
	//	return IsValidCapture(move, board);
	//}
}
ErrorCode Knight::IsValidPieceMove(const singleMove move, const Board& board) const
{
	if (((abs(move.destination.row - this->position.row) == 2) && (abs(move.destination.collumn - this->position.collumn) == 1)) xor ((abs(move.destination.row - this->position.row) == 1) && (abs(move.destination.collumn - this->position.collumn) == 2)))
	{
		return ErrorCode::Success;
	}
	return ErrorCode::InvalidKnightMove;
}
ErrorCode Bishop::IsValidPieceMove(const singleMove move, const Board& board) const
{
	if (!((this->position.row - this->position.collumn) == (move.destination.row - move.destination.collumn)) xor ((this->position.row + this->position.collumn) == (move.destination.row + move.destination.collumn)))
	{	
		return ErrorCode::BishopMustStayInHisDiagonal;
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
			return ErrorCode::CannotGoThroughOtherPieces;
		}
	}

	return ErrorCode::Success;
}
ErrorCode Rock::IsValidPieceMove(const singleMove move, const Board& board) const
{
	if (move.destination.row != position.row && move.destination.collumn != position.collumn)
	{
		return ErrorCode::RockMustStayInRowOrColumn;
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
			return ErrorCode::CannotGoThroughOtherPieces;
		}
	}

	return ErrorCode::Success;
}
ErrorCode Queen::IsValidPieceMove(const singleMove move, const Board& board) const
{
	Rock rock(color, position);
	Bishop bishop(color, position);

	const ErrorCode rock_move = rock.IsValidMove(move, board);
	const ErrorCode bishop_move = bishop.IsValidMove(move, board);
	if (rock_move == ErrorCode::Success || bishop_move == ErrorCode::Success)
	{
		return ErrorCode::Success;
	}

	if (rock_move == ErrorCode::CannotGoThroughOtherPieces || bishop_move == ErrorCode::CannotGoThroughOtherPieces)
	{
		return ErrorCode::CannotGoThroughOtherPieces;
	}

	return ErrorCode::InvalidQueenMove;
}