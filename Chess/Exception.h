#pragma once
#include "error.h"

class Exception
{
private:
	ErrorCode error;
	std::wstring message;
public:
	Exception(const ErrorCode errorCode, const std::wstring errorMessage);
	ErrorCode GetError()const;
	std::wstring Message()const;
};

