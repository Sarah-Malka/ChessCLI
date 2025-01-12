#pragma once
#include "types.h"
#include <string>

namespace GameUtils
{
	singleMove StringToMove(std::wstring move);
	bool isValidMove(struct singleMove);


};
