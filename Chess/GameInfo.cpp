#include "GameInfo.h"

bool GameInfo::WhiteToPlay = true;
bool GameInfo::atelastMove = false;

bool GameInfo::whiteKingMoved = false;
bool GameInfo::a1WhiteRockMoved = false;
bool GameInfo::a8WhiteRockMoved = false;

bool GameInfo::blackKingMoved = false;
bool GameInfo::h1BlackRockMoved = false;
bool GameInfo::h8BlackRockMoved = false;

constexpr uint8_t outOfBoardRange = 10;
Coordinate GameInfo::pawnSkippedThisSquareLastTurn = {outOfBoardRange, outOfBoardRange};