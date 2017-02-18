
#ifndef _ALAMO_INPUT_DEVICE_H_
#define _ALAMO_INPUT_DEVICE_H_

//This file contains keycode enum type ,message type structure
#include "Alamo.h"

namespace Alamo
{

#define MAKE_KEYBOARD_MESSAGE(msg) (*((alaKeybordInputMessage *)(msg)))


	enum alaInputMessageType
	{
		UNKNOWN_TYPE,
		WINDOWS_INPUT_MESSAGE,
		KEYBOARD_INPUT_MESSAGE

	};
	enum alaButtonState
	{
		BUTTON_UP,
		BUTTON_DOWN
	};

	
	enum alaKeyCode
	{
		KC_LBUTTON = VK_LBUTTON,         // Left mouse button
		KC_RBUTTON = VK_RBUTTON,         // Right mouse button
		KC_CANCEL = VK_CANCEL,           // Control-break processing
		KC_MBUTTON = VK_MBUTTON,         // Middle mouse button (three-button mouse)
		KC_BACKSPACE = VK_BACK,          // BACKSPACE key
		KC_TAB = VK_TAB,                 // TAB key
		KC_CLEAR = VK_CLEAR,             // CLEAR key
		KC_RETURN = VK_RETURN,           // ENTER key
		KC_SHIFT = VK_SHIFT,             // SHIFT key
		KC_CONTROL = VK_CONTROL,         // CTRL key
		KC_ALT = VK_MENU,                // ALT key
		KC_PAUSE = VK_PAUSE,             // PAUSE key
		KC_CAPS_LOCK = VK_CAPITAL,       // CAPS LOCK key
		KC_KANA = VK_KANA,               // Input Method Editor (IME) Kana mode
		KC_HANGUL = VK_HANGUL,           // IME Hangul mode
		KC_JUNJA = VK_JUNJA,             // IME Junja mode
		KC_FINAL = VK_FINAL,             // IME final mode
		KC_HANJA = VK_HANJA,             // IME Hanja mode
		KC_KANJI = VK_KANJI,             // IME Kanji mode
		KC_ESCAPE = VK_ESCAPE,           // ESC key
		KC_CONVERT = VK_CONVERT,         // IME convert
		KC_NONCONVERT = VK_NONCONVERT,   // IME nonconvert
		KC_ACCEPT = VK_ACCEPT,           // IME accept
		KC_MODECHANGE = VK_MODECHANGE,   // IME mode change request
		KC_SPACEBAR = VK_SPACE,          // SPACEBAR
		KC_PRIOR = VK_PRIOR,             // PAGE UP key
		KC_PAGE_DOWN = VK_NEXT,          // PAGE DOWN key
		KC_END = VK_END,                 // END key
		KC_HOME = VK_HOME,               // HOME key
		KC_LEFT_ARROW = VK_LEFT,         // LEFT ARROW key
		KC_UP_ARROW = VK_UP,             // UP ARROW key
		KC_RIGHT_ARROW = VK_RIGHT,       // RIGHT ARROW key
		KC_DOWN_ARROW = VK_DOWN,         // DOWN ARROW key
		KC_SELECT = VK_SELECT,           // SELECT key
		KC_PRINT = VK_PRINT,             // PRINT key
		KC_EXECUTE = VK_EXECUTE,         // EXECUTE key
		KC_PRINT_SCREEN = VK_SNAPSHOT,   // PRINT SCREEN key
		KC_INSERT = VK_INSERT,           // INS key
		KC_DELETE = VK_DELETE,           // DEL key
		KC_HELP = VK_HELP,               // HELP key
		KC_0 = 0x30,                     // 0 key
		KC_1 = 0x31,                     // 1 key
		KC_2 = 0x32,                     // 2 key
		KC_3 = 0x33,                     // 3 key
		KC_4 = 0x34,                     // 4 key
		KC_5 = 0x35,                     // 5 key
		KC_6 = 0x36,                     // 6 key
		KC_7 = 0x37,                     // 7 key
		KC_8 = 0x38,                     // 8 key
		KC_9 = 0x39,                     // 9 key
		KC_A = 0x41,                     // A key
		KC_B = 0x42,                     // B key
		KC_C = 0x43,                     // C key
		KC_D = 0x44,                     // D key
		KC_E = 0x45,                     // E key
		KC_F = 0x46,                     // F key
		KC_G = 0x47,                     // G key
		KC_H = 0x48,                     // H key
		KC_I = 0x49,                     // I key
		KC_J = 0x4A,                     // J key
		KC_K = 0x4B,                     // K key
		KC_L = 0x4C,                     // L key
		KC_M = 0x4D,                     // M key
		KC_N = 0x4E,                     // N key
		KC_O = 0x4F,                     // O key
		KC_P = 0x50,                     // P key
		KC_Q = 0x51,                     // Q key
		KC_R = 0x52,                     // R key
		KC_S = 0x53,                     // S key
		KC_T = 0x54,                     // T key
		KC_U = 0x55,                     // U key
		KC_V = 0x56,                     // V key
		KC_W = 0x57,                     // W key
		KC_X = 0x58,                     // X key
		KC_Y = 0x59,                     // Y key
		KC_Z = 0x5A,                     // Z key
		KC_LWIN = VK_LWIN,               // Left Windows key (Microsoft Natural keyboard) 
		KC_RWIN = VK_RWIN,               // Right Windows key (Natural keyboard)
		KC_APPS = VK_APPS,               // Applications key (Natural keyboard)
										 //    KC_SLEEP = VK_SLEEP,             // Computer Sleep key
		KC_NUMPAD0 = VK_NUMPAD0,         // Numeric keypad 0 key
		KC_NUMPAD1 = VK_NUMPAD1,         // Numeric keypad 1 key
		KC_NUMPAD2 = VK_NUMPAD2,         // Numeric keypad 2 key
		KC_NUMPAD3 = VK_NUMPAD3,         // Numeric keypad 3 key
		KC_NUMPAD4 = VK_NUMPAD4,         // Numeric keypad 4 key
		KC_NUMPAD5 = VK_NUMPAD5,         // Numeric keypad 5 key
		KC_NUMPAD6 = VK_NUMPAD6,         // Numeric keypad 6 key
		KC_NUMPAD7 = VK_NUMPAD7,         // Numeric keypad 7 key
		KC_NUMPAD8 = VK_NUMPAD8,         // Numeric keypad 8 key
		KC_NUMPAD9 = VK_NUMPAD9,         // Numeric keypad 9 key
		KC_NUMPAD_MULTIPLY = VK_MULTIPLY,// Multiply key
		KC_NUMPAD_ADD = VK_ADD,          // Add key
		KC_SEPARATOR = VK_SEPARATOR,     // Separator key
		KC_NUMPAD_SUBTRACT = VK_SUBTRACT,// Subtract key
		KC_NUMPAD_DECIMAL = VK_DECIMAL,  // Decimal key
		KC_NUMPAD_DIVIDE = VK_DIVIDE,    // Divide key
		KC_F1 = VK_F1,                   // F1 key
		KC_F2 = VK_F2,                   // F2 key
		KC_F3 = VK_F3,                   // F3 key
		KC_F4 = VK_F4,                   // F4 key
		KC_F5 = VK_F5,                   // F5 key
		KC_F6 = VK_F6,                   // F6 key
		KC_F7 = VK_F7,                   // F7 key
		KC_F8 = VK_F8,                   // F8 key
		KC_F9 = VK_F9,                   // F9 key
		KC_F10 = VK_F10,                 // F10 key
		KC_F11 = VK_F11,                 // F11 key
		KC_F12 = VK_F12,                 // F12 key
		KC_F13 = VK_F13,                 // F13 key
		KC_F14 = VK_F14,                 // F14 key
		KC_F15 = VK_F15,                 // F15 key
		KC_F16 = VK_F16,                 // F16 key
		KC_F17 = VK_F17,                 // F17 key
		KC_F18 = VK_F18,                 // F18 key
		KC_F19 = VK_F19,                 // F19 key
		KC_F20 = VK_F20,                 // F20 key
		KC_F21 = VK_F21,                 // F21 key
		KC_F22 = VK_F22,                 // F22 key
		KC_F23 = VK_F23,                 // F23 key
		KC_F24 = VK_F24,                 // F24 key
		KC_NUMLOCK = VK_NUMLOCK,         // NUM LOCK key
		KC_SCROLL_LOCK = VK_SCROLL,      // SCROLL LOCK key
		KC_LEFT_SHIFT = VK_LSHIFT,       // Left SHIFT key
		KC_RIGHT_SHIFT = VK_RSHIFT,      // Right SHIFT key
		KC_LEFT_CONTROL = VK_LCONTROL,   // Left CONTROL key
		KC_RIGTH_CONTROL = VK_RCONTROL,  // Right CONTROL key
		KC_LEFT_MENU = VK_LMENU,         // Left MENU key
		KC_RIGHT_MENU = VK_RMENU,        // Right MENU key
		/*********************************************************
		KC_VK_OEM_1 = VK_OEM_1,           // Used for miscellaneous characters; it can vary by keyboard. Windows 2000/XP: For the US standard keyboard, the ';:' key
		KC_OEM_2 = VK_OEM_2,   // Used for miscellaneous characters; it can vary by keyboard. Windows 2000/XP: For the US standard keyboard, the '/?' key
		KC_OEM_3 = VK_OEM_3,   // Used for miscellaneous characters; it can vary by keyboard. Windows 2000/XP: For the US standard keyboard, the '`~' key
		KC_OEM_4 = VK_OEM_4,   // Used for miscellaneous characters; it can vary by keyboard. Windows 2000/XP: For the US standard keyboard, the '[{' key
		KC_OEM_5 = VK_OEM_5,   // Used for miscellaneous characters; it can vary by keyboard. Windows 2000/XP: For the US standard keyboard, the '\|' key
		KC_OEM_6 = VK_OEM_6,   // Used for miscellaneous characters; it can vary by keyboard. Windows 2000/XP: For the US standard keyboard, the ']}' key
		KC_OEM_7 = VK_OEM_7,   // Used for miscellaneous characters; it can vary by keyboard. Windows 2000/XP: For the US standard keyboard, the 'single-quote/double-quote' key
		KC_OEM_8 = VK_OEM_8,   // Used for miscellaneous characters; it can vary by keyboard.
		**************************************************************/
		KC_PROCESSKEY = VK_PROCESSKEY,   // Windows 95/98/Me, Windows NT 4.0, Windows 2000/XP: IME PROCESS key
		KC_ATTN = VK_ATTN,     // Attn key
		KC_CRSEL = VK_CRSEL,   // CrSel key
		KC_EXSEL = VK_EXSEL,   // ExSel key
		KC_EREOF = VK_EREOF,   // Erase EOF key
		KC_PLAY = VK_PLAY,     // Play key
		KC_ZOOM = VK_ZOOM,     // Zoom key
		KC_PA1 = VK_PA1,       // PA1 key
		KC_OEM_CLEAR = VK_OEM_CLEAR
	};

	struct alaInputMessage
	{
		alaInputMessageType type;
	};

	struct alaWindowsInputMessage :public alaInputMessage
	{
		DWORD id;
		HWND windowHandle;
		WPARAM wPrarm;
		LPARAM lParam;

		alaWindowsInputMessage()
		{
			type = WINDOWS_INPUT_MESSAGE;
			id = UNKNOWN_TYPE;
			windowHandle = NULL;
			wPrarm = 0;
			lParam = 0;
		}
	};

	struct alaKeybordInputMessage :public alaWindowsInputMessage
	{
		alaKeyCode keyCode;
		int repeatCount;
		unsigned scanCode;
		bool isExtendedKey;
		alaButtonState previousState;

		alaKeybordInputMessage() :alaWindowsInputMessage()
		{
			keyCode = (alaKeyCode)0x00;
			repeatCount = 0;
			scanCode = 0;
			isExtendedKey = false;
			previousState = BUTTON_UP;
		}

	};

	struct alaCharacterMessage :public alaWindowsInputMessage
	{
		char theChar;

		alaCharacterMessage() :alaWindowsInputMessage()
		{
			theChar = '\0';
		}
	};

}


#endif // !ALA_INPUT_DEVICE_H_
