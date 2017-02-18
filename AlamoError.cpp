#include "Alamo.h"
#include "AlamoError.h"

namespace Alamo
{

	//platform dependent
	//平台相关代码

	alaOsErrorCode alaError::Get_Last_OS_Error_Code()
	{
		return ((alaOsErrorCode)GetLastError());
	}

	alaString alaError::Get_Last_OS_Error_Message()
	{
		alaOsErrorCode errorCode = GetLastError();

		const int MESSAGE_BUFFER_SIZE = 1024;
		TCHAR errorMessage[MESSAGE_BUFFER_SIZE];


		//根据错误码，获取系统错误信息

		::FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			errorCode,
			0,
			errorMessage,
			MESSAGE_BUFFER_SIZE,
			NULL);
		alaString messageString((char *)errorMessage);

		return messageString;
	}
}