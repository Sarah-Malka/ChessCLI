#pragma once

#include <map>
#include <string>

enum class ErrorCode //Order Is important
{
	PositionOutOfBoard = 0,
	YouAreInCheck,
	TargetPositionIsCurrentPosition,

	SquaresNotEmptyBetweenKingAndRock,
	KingAlreadyMoved,
	RockAlreadyMoved,
	IllegalCheckExposureDuringCastlation,
	KingCanMoveOnlyOneSquare,

	CannotGoThroughOtherPieces,
	RockMustStayInRowOrColumn,
	BishopMustStayInHisDiagonal,

	PawnAlreadyMoved,
	PawnMustMoveForward,
	SquareIsOccupied,
	NoOpponentPieceToEat,
	PawnCanMoveOnlyOneSquare,

	InvalidQueenMove,
	InvalidKnightMove,
	InvalidPawnMove,
	
	SquareOccupiedByYourOwnPiece,

	IllegalCheckExposure,
	NoPieceFoundAtOriginPosition,
	MoreThanOneCompatiblePiece,

	Success
};

static std::map<ErrorCode, std::wstring> errorCodeToMessage = {
	{ErrorCode::Success, L"Success"},
	{ErrorCode::PositionOutOfBoard, L"PositaionOutOfBoard"},
	{ErrorCode::TargetPositionIsCurrentPosition, L"TargetPositionIsCurrentPosition"},
	{ErrorCode::SquaresNotEmptyBetweenKingAndRock, L"SquaresNotEmptyBetweenKingAndRock"},
	{ErrorCode::KingAlreadyMoved, L"KingAlreadyMoved"},
	{ErrorCode::RockAlreadyMoved, L"RockAlreadyMoved"},
	{ErrorCode::IllegalCheckExposureDuringCastlation, L"IllegalCheckExposureDuringCastlation"},
	{ErrorCode::KingCanMoveOnlyOneSquare, L"KingCanMoveOnlyOneSquare"},
	{ErrorCode::RockMustStayInRowOrColumn, L"RockMustStayInRowOrColumn"},
	{ErrorCode::BishopMustStayInHisDiagonal, L"BishopMustStayInHisDiagonal"},
	{ErrorCode::CannotGoThroughOtherPieces, L"CannotGoThroughOtherPieces"},
	{ErrorCode::PawnAlreadyMoved, L"PawnAlreadyMoved"},
	{ErrorCode::PawnMustMoveForward, L"PawnMustMoveForward"},
	{ErrorCode::PawnCanMoveOnlyOneSquare, L"PawnCanMoveOnlyOneSquare"},
	{ErrorCode::SquareIsOccupied, L"SquareIsOccupied"},
	{ErrorCode::NoOpponentPieceToEat, L"NoOpponentPieceToEat"},
	{ErrorCode::InvalidQueenMove, L"InvalidQueenMove"},
	{ErrorCode::InvalidKnightMove, L"InvalidKnightMove"},
	{ErrorCode::InvalidPawnMove, L"InvalidPawnMove"},
	{ErrorCode::SquareOccupiedByYourOwnPiece, L"SquareOccupiedByYourOwnPiece"},
	{ErrorCode::IllegalCheckExposure, L"IllegalCheckExposure"},
	{ErrorCode::MoreThanOneCompatiblePiece, L"MoreThanOneCompatiblePiece"},
	{ErrorCode::YouAreInCheck, L"YouAreInCheck"},
	{ErrorCode::NoPieceFoundAtOriginPosition, L"NoPieceFoundAtOriginPosition"},
};

