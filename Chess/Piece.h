#pragma once
#include "basicTypes.h"

class Board;

class Piece
{
protected:
	PieceType type;
	Color color;
	Coordinate position;
	bool IsStaying(const Coordinate targetPosition) const;
	bool IsEatingHisColor(const Coordinate targetPosition, const Board& board) const;
	virtual bool IsValidPieceMove(Coordinate targetPosition, const Board& board)const = 0;

public: 
	bool IsValidMove(const Coordinate targetPosition, const Board& board) const;
	Piece(PieceType type, Color color, Coordinate position);
	Piece(PieceType type, Color color, uint8_t row, uint8_t colomn);
	void Move(Coordinate targetPositiond);
	PieceType getType() const;
	Color getColor() const;
	Coordinate getPosition() const;
};

class Pawn : public Piece
{
public:
	Pawn(Color color, int row, int colomn) : Piece(PieceType::PAWN, color, row, colomn) {};
protected:
	bool IsValidPieceMove(Coordinate targetPosition, const Board& board) const override;
};
class King : public Piece
{
public:
	King(Color color, int row, int colomn) : Piece(PieceType::KING, color, row, colomn) {};
protected:
	bool IsValidPieceMove(Coordinate targetPosition, const Board& board) const override;
};
class Queen : public Piece
{
public:
	Queen(Color color, int row, int colomn) : Piece(PieceType::QUEEN, color, row, colomn) {};
protected:
	bool IsValidPieceMove(Coordinate targetPosition, const Board& board) const override { return true; };
};
class Bishop : public Piece
{
public:
	Bishop(Color color, int row, int colomn) : Piece(PieceType::BISHOP, color, row, colomn) {};
protected:
	bool IsValidPieceMove(Coordinate targetPosition, const Board& board) const override { return true; };
};
class Knight : public Piece
{
public:
	Knight(Color color, int row, int colomn) : Piece(PieceType::KNIGHT, color, row, colomn) {};
protected:
	bool IsValidPieceMove(Coordinate targetPosition, const Board& board) const override;
};
class Rock : public Piece
{
public:
	Rock(Color color, int row, int colomn) : Piece(PieceType::ROCK, color, row, colomn){};
protected:
	bool IsValidPieceMove(Coordinate targetPosition, const Board& board) const override { return true; };
};