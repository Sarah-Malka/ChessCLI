#include "Exception.h"

Exception::Exception(const ErrorCode errorCode) : error(errorCode)
{
}

ErrorCode Exception::GetError() const
{
	return error;
}
