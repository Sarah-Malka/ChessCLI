#pragma once



enum class ErrorCode
{
	PositaionOutOfBoard = 0,
	NoPieceCanMove,
	MoreThanOneCompatiblePiece,
	IllegalChessExposure,
	CannotTakeHisOwnPiece,
	TargetPositionIsCurrentPosition,
	CannotCastleWithChess,
	KingAlreadyMoved,
	RockAlreadyMoved,
};