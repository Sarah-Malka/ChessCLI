#pragma once
#include "basicTypes.h"
#include <map>
#include <string>

class Piece;

class singleMove
{
public:
	Coordinate origin;
	Coordinate destination;
	PieceType originalPiece;
	PieceType coronationRequest;
	bool isCastlation = false;
};


enum class EndGameType : uint8_t
{
	NOT_ENDED = 0,
	CHECKMATE,
	STALEMATE,
	THREE_FOLD_REPETITION,
	FIFTY_MOVES,
	INSUFICIENT_MATERIAL
};

static std::map<EndGameType, std::wstring> endGameTypeToMessage = {
	{EndGameType::NOT_ENDED, L"Game didn't end"},
	{EndGameType::CHECKMATE, L"Checkmate"},
	{EndGameType::STALEMATE, L"Stalmate"},
	{EndGameType::THREE_FOLD_REPETITION, L"Three fold repetition"},
	{EndGameType::FIFTY_MOVES, L"Fifty moves rule"},
	{EndGameType::INSUFICIENT_MATERIAL, L"Insuficient material"}
};