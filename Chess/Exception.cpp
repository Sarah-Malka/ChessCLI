#include "Exception.h"

Exception::Exception(const ErrorCode errorCode, const std::wstring errorMessage = L"")
	: error(errorCode), message(errorMessage)
{
}

ErrorCode Exception::GetError() const
{
	return error;
}

std::wstring Exception::Message() const
{
	return message;
}
