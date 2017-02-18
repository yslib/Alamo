
#ifndef _ALAMO_APP_H_
#define _ALAMO_APP_H_

#include "Alamo.h"
#include "AlamoGame.h"
#include "AlamoError.h"
#include "AlamoScreenMode.h"

namespace Alamo {

	//struct
	const int ALAMO_MIN_TIMER_ID = 100;

	//Window startup info

	struct alaWindowsInitParams
	{
		alaString appWindowTitile;

		int defaultX, defaultY;
		int defaultHeight, defaultWidth;

		alaScreenMode screenMode;

		alaWindowsInitParams() {
			defaultX = defaultY = 0;
			defaultHeight = defaultWidth = 0;
		}
	};

	struct alaGameSystemInitParams
	{
		bool fullScreenWindow;
		unsigned int millisecondsBetweenFrames;

		alaGameSystemInitParams()
		{
			fullScreenWindow = false;
			millisecondsBetweenFrames = 0;
		}

	};

	struct alaOpenglInitParams
	{
		alaColorRGBA surfaceBackGroundColor;
		PIXELFORMATDESCRIPTOR pixelFormat;

		alaOpenglInitParams() :surfaceBackGroundColor(0.0f, 0.0f, 0.0f, 0.0f)
		{

		}

	};

	struct alaOpenalInitParams
	{

	};

	struct alaOpenInitParams :public alaGameSystemInitParams
	{
		alaOpenglInitParams openGLParams;
		alaOpenalInitParams openALParams;
	};

	struct alaInitParams
	{
		alaWindowsInitParams winParams;
		alaOpenInitParams openParams;
	};


	// AlamoApp
	//
	class AlamoApp
	{
	public:
		AlamoApp();
		~AlamoApp();
		bool Init_App(alaInitParams initParams);

		void End_Game();
		
		alaGame * Game();

		alaColorRGBA Background_Surface_Color();
		void Clear_Background();
		int Screen_Height();
		int Screen_Width();

		void Begin_Render_Now();
		void End_Render_Now();

		//bool Is_Key_Pressed(alaKeyCode keyToTest) { return ((SHORT)(::GetAsyncKeyState((int)keyToTest) & 0x8000)) ? true : false; }

		alaError App_Error(){return appError;}

		void App_Error(alaErrorStatus errorCode, alaString errorMessage = ""){appError.Error(errorCode, errorMessage);}

		void RWS_Set_Time_TO_Update_Frame(int aBool) { timeToUpdateFrame = aBool; }
#ifndef DEBUGOFF

		bool Open_LogFile(char *logFileName);

		bool Write_To_Log_File(char * stringToWrite);
		
		void Close_Log_File();
#endif

	private:

		//friend functions and classes
		friend INT WINAPI App_Main(
			HINSTANCE hInst,
			HINSTANCE,
			LPSTR,
			INT);

		friend LRESULT WINAPI App_Msg_Proc(
			HWND hWnd,
			UINT msg,
			WPARAM wParam,
			LPARAM lParam);

		friend class alaBitmap;
		friend class alaSound;

		friend void Create_Animation_Timer(HWND hWnd);
		friend VOID CALLBACK Animation_Timer_Handler(
			HWND hwnd,
			UINT uMsg,
			WPARAM idEvent,    
			DWORD dwTime);

		//Game
		bool Create_Game_Object();
		void Delete_Game_Object(void);


		bool Init_Game_Subsystem(HWND hWnd);
		void Cleanup_Game_Subsystem(bool timeToQuit);


		//OpenGL
		bool Init_OpenGL(HWND hWnd);
		VOID Cleanup_OpenGL(bool timeToQuit);
		void Create_OpenGL_Rendering_Surface(HWND hWnd);


		//OpenAL
		bool Init_OpenAL();
		void Cleanup_OpenAL();

		//Render
		bool Render();

		//Resolution
		bool Set_Screen_Resolution();

	private:
		bool appInitialized;

		bool openGLInitialized;

		bool openALInitialized;

		alaError appError;

		alaInitParams engineInitParams;

		alaGame *theGame;

		int screenWidth;
		int screenHeight;

		float minSoundGain;
		float maxSoundGain;

		bool timeToUpdateFrame;

		int renderNow;

		//Platform dependent 
		HGLRC renderingContext;
		HDC appDeviceContext;
		HWND mainWdinwoHandle;

#ifndef DEBUGOFF
		std::ofstream logFile;
#endif
	};

	inline AlamoApp::~AlamoApp()
	{

	}




#define  CREATE_GAME_OBJECT(GameClass)			\
bool AlamoApp::Create_Game_Object(void)			\
{												\
	bool gameObjectCreated = true;				\
	theGame = new GameClass;					\
	if(theGame ==NULL)							\
	{											\
		gameObjectCreated = false;				\
	}											\
	return (gameObjectedCreated);				\
}												\
void AlamoApp::Delete_Game_Object(void)			\
{												\
	if(theGame != NULL)							\
	{											\
		delete theGame;							\
	}											\
}												\


#ifndef EXTERN
#define  EXTERN extern
#endif // !EXTERN

	EXTERN AlamoApp theApp;			//声明外部全局变量		告诉所有包含此头文件的代码文件中若有 theApp，则它就是全局变量

}
Alamo::AlamoApp * GetAppObject();

#endif