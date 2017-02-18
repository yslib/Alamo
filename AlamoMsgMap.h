
#ifndef _ALAMO_MSG_MAP_H_
#define _ALAMO_MSG_MAP_H_
//#include "Alamo.h"
#include "AlamoInputDevice.h"

namespace Alamo
{

#define START_MESSAGE_MAP(classname)			\
	void classname::Process_Input_Message_Map(	\
	alaWindowsInputMessage &theMessage)			\
	{											\
		bool callParent = false;				\
		if(callParent != false){}				
#define ONMESSAGE(msgid,fnname)					\
		else if(theMessage.id == msgid)			\
		{										\
			callParent = fnname(theMessage);	\
		}				
#define ON_WMKEYDOWN(fnname)					\
		else if(theMessage.id == WM_KEYDOWN)	\
		{										\
			alaKeybordInputMessage keyboardMessage;							\
			keyboardMessage.id = theMessage.id;								\
			keyboardMessage.windowHandle = theMessage.windowHandle;			\
			keyboardMessage.wParam = theMessage.wParam;						\
			keyboardMessage.lParam = theMessage.lParam;						\
			keyboardMessage.keyCode = (alaKeyCode)theMessage.wParam			\
			keyboardMessage.repeatCount =									\
			keyboardMessage.lParam & 0x0FFFF;								\
			keyboardMessage.scanCode =										\
			(theMessage.lParam & 0x0FF0000) >> 16;							\
			keyboardMessage.isExtendeKey =									\
			((theMessage.lParam & 0x01000000) == 0) ?						\
			false:true;														\
			keyboardMessage.previousState =									\
			((theMessage.lParam & 0xFE000000) == 0) ?						\
			BUTTON_UP:BUTTON_DOWN;											\
			callParent = fnname(keyboardMessage);							\
		}																	
#define ON_WMCHAR(fnname)													\
		if(theMessage.ID() == WM_CHAR)										\
		{																	\
			alaCharacterMessage charMessage;								\
			charMessage.id = theMessag.id;									\
			charMessage.windowHandle = theMessage.windowHandle;				\
			charMessage.wParam = the MEssage.wParam;						\
			charMessage.lParam = theMessage.lParam;							\
			charMessage.theChar = (char)theMessage.wParam;					\
			callParent = fnname(charMessage);								\
		}																	
#define END_MESSAGE_MAP(parentname)											\
		if((#parentname != "alaGame") && (callParent == true))				\
			parentname::Process_Input_Message_Map(theMessage);				\
}																			


#define ATTACH_MESSAGE_MAP													\
	virtual void Process_Input_Message_Map(alaWindowsInputMessage &theMessage);



}/*namespace*/
#endif