#include "GameInfo.h"

bool GameInfo::WhiteToPlay = true;
bool GameInfo::atelastMove = false;

bool GameInfo::whiteKingMoved = false;
bool GameInfo::a1WhiteRockMoved = false;
bool GameInfo::a8WhiteRockMoved = false;

bool GameInfo::blackKingMoved = false;
bool GameInfo::h1BlackRockMoved = false;
bool GameInfo::h8BlackRockMoved = false;

uint8_t GameInfo::number_of_pieces_on_board = 32;

Coordinate GameInfo::pawnSkippedThisSquareLastTurn = {outOfBoardRange, outOfBoardRange};
bool GameInfo::doubleMoveWasAttemptedThisTurn = false;

size_t GameInfo::numberOfMovesFor50MoveRule = 0;
