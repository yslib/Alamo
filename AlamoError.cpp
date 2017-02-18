#include "Alamo.h"
#include "AlamoError.h"

namespace Alamo
{

	//platform dependent
	//ƽ̨��ش���

	alaOsErrorCode alaError::Get_Last_OS_Error_Code()
	{
		return ((alaOsErrorCode)GetLastError());
	}

	alaString alaError::Get_Last_OS_Error_Message()
	{
		alaOsErrorCode errorCode = GetLastError();

		const int MESSAGE_BUFFER_SIZE = 1024;
		TCHAR errorMessage[MESSAGE_BUFFER_SIZE];


		//���ݴ����룬��ȡϵͳ������Ϣ

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