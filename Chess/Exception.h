#pragma once
#include "error.h"
#include <string>

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

