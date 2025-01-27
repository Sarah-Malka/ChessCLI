#pragma once
#include "error.h"

class Exception
{
private:
	ErrorCode error;
public:
	Exception(const ErrorCode errorCode);
	ErrorCode GetError()const;
};

