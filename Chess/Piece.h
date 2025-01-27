#pragma once
#include "basicTypes.h"
#include "GameInfo.h"

class Board;

class Piece
{
protected:
	PieceType type;
	Color color;
	Coordinate position;
	bool IsStaying(const Coordinate targetPosition) const;
	bool IsEatingHisColor(const Coordinate targetPosition, const Board& board) const;

public: 
	Piece(PieceType type, Color color, Coordinate position);
	Piece(PieceType type, Color color, uint8_t row, uint8_t colomn);
	virtual bool IsValidMove(Coordinate targetPosition, const Board& board) = 0;
	void Move(Coordinate targetPositiond);
	PieceType getType() const;
	Color getColor() const;
};

class Pawn : public Piece
{
public:
	Pawn(Color color, int row, int colomn) : Piece(PieceType::PAWN, color, row, colomn) {};
	bool IsValidMove(Coordinate targetPosition, const Board& board) override;
};
class King : public Piece
{
public:
	King(Color color, int row, int colomn) : Piece(PieceType::KING, color, row, colomn) {};
	bool IsValidMove(Coordinate targetPosition, const Board& board) override;
};
class Queen : public Piece
{
public:
	Queen(Color color, int row, int colomn) : Piece(PieceType::QUEEN, color, row, colomn) {};
	bool IsValidMove(Coordinate targetPosition, const Board& board) override { return true; };
};
class Bishop : public Piece
{
public:
	Bishop(Color color, int row, int colomn) : Piece(PieceType::BISHOP, color, row, colomn) {};
	bool IsValidMove(Coordinate targetPosition, const Board& board) override { return true; };
};
class Knight : public Piece
{
public:
	Knight(Color color, int row, int colomn) : Piece(PieceType::KNIGHT, color, row, colomn) {};
	bool IsValidMove(Coordinate targetPosition, const Board& board) override { return true; };
};
class Rock : public Piece
{
public:
	Rock(Color color, int row, int colomn) : Piece(PieceType::ROCK, color, row, colomn){};
	bool IsValidMove(Coordinate targetPosition, const Board& board) override { return true; };
};