#pragma once
#include <vector>
#include "Piece.h"
#include "types.h"

using array2D = std::vector<std::vector<Piece*>>;


class Board
{
private:
	std::vector<Coordinate> kings_locations;
	std::map<std::wstring, std::uint8_t> threeFoldMap; //map to count the number of position repititions

	Board(const Board& other);
	bool shouldCoronate(singleMove move);

public:
	array2D board;
	static array2D GetToInitialState();

	bool isCheckmate(Color color);
	bool isStalemate(Color color);
	bool ThreeFoldRepetition();
	void UpdateHashMap();
	void ClearHashMap();

public:
	Board();
	~Board();
	std::vector<Piece*>& operator[](std::size_t index);
	const std::vector<Piece*> operator[](std::size_t index) const;

	Piece*& operator[](Coordinate position);
	Piece* const operator[](Coordinate position) const;
	void PrintBoard() const;
	void Move(const Coordinate source, const singleMove move, bool realMove);
	bool IsCheck(const Color color) const;
	bool IsCheck(const Color color, Coordinate sqr) const;
	bool WillCauseCheck(const Color color, const Coordinate source, const singleMove move) const;
	bool LegalMoveExists(Color color);
	bool PieceHasLegalMoves(Piece* piece);
};