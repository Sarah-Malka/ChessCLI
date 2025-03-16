#pragma once
#include "basicTypes.h"
#include "types.h"
#include "error.h"

class Board;

class Piece
{
protected:
	PieceType type;
	Color color;
	Coordinate position;
	bool IsStaying(const Coordinate targetPosition) const;
	bool IsEatingHisColor(const Coordinate targetPosition, const Board& board) const;
	virtual ErrorCode IsValidPieceMove(const singleMove move, const Board& board)const = 0;
public: 
	Piece(PieceType type, Color color, Coordinate position);
	Piece(PieceType type, Color color, uint8_t row, uint8_t colomn);
	Piece* GetPiece(const PieceType type) const;

	PieceType getType() const;
	Color getColor() const;
	Coordinate getPosition() const;

	ErrorCode IsValidMove(const singleMove move, const Board& board) const;
	void Move(Coordinate targetPositiond);
};

class Pawn : public Piece
{
public:
	Pawn(Color color, int row, int colomn) : Piece(PieceType::PAWN, color, row, colomn) {};
	Pawn(Color color, Coordinate position) : Piece(PieceType::PAWN, color, position) {};
protected:
	ErrorCode IsValidPieceMove(const singleMove move, const Board& board) const override;
	ErrorCode IsValidCapture(const singleMove move, const Board& board) const;
	ErrorCode IsValidDoubleStep(const singleMove move, const Board& board) const;
	bool DidNotMove() const;
	bool IsMovingForward(const singleMove move) const;
};
class King : public Piece
{
public:
	King(Color color, int row, int colomn) : Piece(PieceType::KING, color, row, colomn) {};
	King(Color color, Coordinate position) : Piece(PieceType::KING, color, position) {};
protected:
	ErrorCode IsValidPieceMove(const singleMove move, const Board& board) const override;
};
class Queen : public Piece
{
public:
	Queen(Color color, int row, int colomn) : Piece(PieceType::QUEEN, color, row, colomn) {};
	Queen(Color color, Coordinate position) : Piece(PieceType::QUEEN, color, position) {};
protected:
	ErrorCode IsValidPieceMove(const singleMove move, const Board& board) const override;
};
class Bishop : public Piece
{
public:
	Bishop(Color color, int row, int colomn) : Piece(PieceType::BISHOP, color, row, colomn) {};
	Bishop(Color color, Coordinate position) : Piece(PieceType::BISHOP, color, position) {};

protected:
	ErrorCode IsValidPieceMove(const singleMove move, const Board& board) const override;
};
class Knight : public Piece
{
public:
	Knight(Color color, int row, int colomn) : Piece(PieceType::KNIGHT, color, row, colomn) {};
	Knight(Color color, Coordinate position) : Piece(PieceType::KNIGHT, color, position) {};
protected:
	ErrorCode IsValidPieceMove(const singleMove move, const Board& board) const override;
};
class Rock : public Piece
{
public:
	Rock(Color color, int row, int colomn) : Piece(PieceType::ROCK, color, row, colomn){};
	Rock(Color color, Coordinate position) : Piece(PieceType::ROCK, color, position) {};
protected:
	ErrorCode IsValidPieceMove(const singleMove move, const Board& board) const override;
};