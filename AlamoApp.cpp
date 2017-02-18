//////////////////////////////////////////////////////////////////////////
/*
	File Name : AlamoApp.cpp

*/

//Include FIles-----------------------------


#define EXTERN

#include "Alamo.h"
#include "AlamoApp.h"
#include "AlamoType.h"
#include "AlamoError.h"
#include "AlamoInputDevice.h"
#include "AlamoScreenMode.h"
//
// Define the global variant theApp.The program is based on this variant.
// Please read AlomoApp.h to learn how the global variant works
Alamo::AlamoApp theApp;		
//END---------------------------

using namespace Alamo;

//
//The modifier static makes the variant referenced only in the current files,
//namely,the scope of the variant modified by static is the current file,which 
//is different from variant modified by nothing.
//

static const char *ALAMO_WINDOW_CLASS_NAME = "ALAMO";
static const UINT ALAMO_ANIMATION_TIMER_ID = 1;
static const alaColorRGBA NO_BACK_COLOR(-1.0f, -1.0f, -1.0f, -1.0f);

//Prototypes-------------------------------


LRESULT WINAPI Msg_Proc(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam);

namespace Alamo {
	INT WINAPI App_Main(HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPSTR lpCmdLine,
		INT nCmdShow);
}

//END PROTOTYPES

/*Program entry for all Win32 programs.
*As you can see,we use a wrapper function which is also 
*a friend function of theApp,to make our engine
*takes charge of the program at the begining.
*/
INT WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, 
	_In_ int nShowCmd)
{
	return (Alamo::App_Main(hInstance,
		hPrevInstance,
		lpCmdLine,
		nShowCmd));
}

LRESULT WINAPI Msg_Proc(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam) {
	return App_Msg_Proc(hWnd,
		msg,
		wParam, lParam);
}

namespace Alamo
{
	INT WINAPI App_Main(HINSTANCE hInstance,
		HINSTANCE hPrevInstance, 
		LPSTR lpCmdLine, 
		INT nCmdShow)
	{
		
		bool error= false;

		WNDCLASSEXW wc;

		HWND hWnd = 0;

		//#ifdef CLAC_FRAME_RATE
		//#endif

		//To run this call normally,you need attach the macro in the AlamoApp.h to your own class
		theApp.Create_Game_Object();
		//END------------------


		//error = theApp.theGame->On_App_Load();
		assert(theApp.appInitialized == true); 

		if (error == false) 
		{
			if (theApp.engineInitParams.openParams.fullScreenWindow == true)
			{
				error = theApp.Set_Screen_Resolution();

				if (error == false)		
				{
					::MessageBoxW(NULL,
						(LPCWSTR)("Your screen does not support the video mode this game uses"),
						NULL,
						MB_OK | MB_ICONSTOP | MB_SYSTEMMODAL);
					return (0);
				}
			}
		}

		if (error == false)
		{
			//Register the window class
			WNDCLASSEXW twc = {
				sizeof(WNDCLASSEXW),
				CS_CLASSDC,
				Msg_Proc,
				0L,
				0L,
				GetModuleHandleW(NULL),
				NULL,
				NULL,
				NULL,
				NULL,
				(LPCWSTR)(ALAMO_WINDOW_CLASS_NAME),
				NULL
			};

			wc = twc;
			if (RegisterClassExW(&wc) == 0)
			{
				alaError initIsOk(ALAES_CANT_CREATE_RAW_INPUT_BUFFER);
				throw initIsOk;
				return (0);
			}
		}

		if (error == false) {

			HDC screenDC = GetDC(NULL);

			theApp.screenWidth = GetDeviceCaps(screenDC, HORZRES);
			theApp.screenHeight = GetDeviceCaps(screenDC, VERTRES);

			int h, w, x, y;
			if ((theApp.engineInitParams.winParams.defaultHeight <= 0) &&
				(theApp.engineInitParams.winParams.defaultWidth)) {
				x = y = 0;
				h = theApp.screenHeight;
				w = theApp.screenWidth;
			}
			else
			{
				x = theApp.engineInitParams.winParams.defaultX;
				y = theApp.engineInitParams.winParams.defaultY;
				h = theApp.engineInitParams.winParams.defaultHeight;
				w = theApp.engineInitParams.winParams.defaultWidth;
			}

			alaString title = theApp.engineInitParams.winParams.appWindowTitile;

			if (theApp.engineInitParams.openParams.fullScreenWindow == true)
			{
				hWnd = CreateWindowExW(
					WS_EX_APPWINDOW | WS_EX_TOPMOST,
					(LPCWSTR)ALAMO_WINDOW_CLASS_NAME,
					(LPCWSTR)title.c_str(),
					WS_POPUP,
					x,
					y,
					w,
					y,
					GetDesktopWindow(),
					NULL, wc.hInstance, NULL);
			}
			else
			{
				hWnd = CreateWindowW(
					(LPCWSTR)ALAMO_WINDOW_CLASS_NAME,
					(LPCWSTR)title.c_str(),
					WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS |
					WS_CLIPCHILDREN | WS_MAXIMIZE,
					x,
					y,
					w,
					h,
					GetDesktopWindow(),
					NULL, wc.hInstance, NULL);
			}

			if (hWnd == NULL)
			{
				error = true;
				throw alaError(ALAES_CANT_CREATE_WINDOW);
			}

		}

		if (error == false)
		{
			error = theApp.Init_Game_Subsystem(hWnd);
		}

		if (error == false)
		{
			//error = theApp.theGame->Init_Game();
			if (error == true)
			{
				throw alaError(ALAES_CANT_INIT_GAME);
			}
		}

		if (error == false)
		{
			ShowWindow(hWnd, SW_SHOWDEFAULT);
			UpdateWindow(hWnd);

			UINT frameTime = theApp.engineInitParams.openParams.millisecondsBetweenFrames;

			if (frameTime == 0)
			{
				theApp.timeToUpdateFrame = true;
			}
			else
			{
				theApp.timeToUpdateFrame = false;
				//
				Create_Animation_Timer(hWnd);
			}

			bool levelIsOk = true;

			MSG msg;
			ZeroMemory(&msg, sizeof(msg));

			while (msg.message != WM_QUIT)			//Quit Message 
			{
				if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
				{
					if (theApp.timeToUpdateFrame)
					{
						if (theApp.theGame->Update_Frame() == false)
						{
							::MessageBoxW(NULL,
								(LPCWSTR)theApp.App_Error().Error_Mesaage().c_str(),
								NULL,
								MB_OK | MB_ICONSTOP | MB_SYSTEMMODAL);
							theApp.End_Game();
						}
					}
					theApp.mainWdinwoHandle = hWnd;

					if (theApp.Render() == false)
					{
						::MessageBoxA(NULL,
							theApp.App_Error().Error_Mesaage().c_str(),
							NULL, MB_OK | MB_ICONSTOP | MB_SYSTEMMODAL);
						theApp.End_Game();
					}
					if (frameTime > 0)
					{
						theApp.timeToUpdateFrame = false;
					}
					if (theApp.theGame->Game_Over() == true)
					{
						if (theApp.theGame->Do_Game_Over() == false)
						{
							theApp.End_Game();
						}
					}
					if (theApp.theGame->Level_Done() == true)
					{
						levelIsOk = theApp.theGame->Do_Level_Done();
						if (levelIsOk)
						{
							levelIsOk = theApp.theGame->Init_Level();
						}
						else
						{
							theApp.End_Game();
						}
					}
				}
			}

		}
		if (theApp.theGame != NULL)
		{
			theApp.Delete_Game_Object();
		}
		UnregisterClassW((LPCWSTR)ALAMO_WINDOW_CLASS_NAME, wc.hInstance);
		return 0;
	}

	LRESULT WINAPI App_Msg_Proc(HWND hWnd, 
		UINT msg, 
		WPARAM wParam, 
		LPARAM lParam)
	{
		assert(theApp.appInitialized);
		PAINTSTRUCT ps;

		if (theApp.Game()->Handle_Mesaage(hWnd, msg, wParam, lParam) == false)
		{
			switch (msg)
			{
			case WM_CREATE:
			{
				theApp.Create_OpenGL_Rendering_Surface(hWnd);
			}
			break;
			case WM_PAINT:
				::BeginPaint(hWnd, &ps);
				::EndPaint(hWnd, &ps);
				break;
			case WM_KEYDOWN:
			case WM_KEYUP:
				//           case WM_MOUSEHOVER:
				//           case WM_MOUSELEAVE:
			case WM_MOUSEMOVE:
				//           case WM_MOUSEWHEEL:                   在Xp的这个系统下不支持本消息
			case WM_LBUTTONDBLCLK:
			case WM_LBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_MBUTTONDBLCLK:
			case WM_MBUTTONDOWN:
			case WM_MBUTTONUP:
			case WM_RBUTTONDBLCLK:
			case WM_RBUTTONDOWN:
			case WM_RBUTTONUP:
			{
				alaWindowsInputMessage theMesaage;

				theMesaage.type = WINDOWS_INPUT_MESSAGE;
				theMesaage.id = msg;
				theMesaage.windowHandle = hWnd;
				theMesaage.wPrarm = wParam;
				theMesaage.lParam = lParam;

				theApp.theGame->Process_Input_Message_Map(theMesaage);
			}
			break;

			case WM_ACTIVATE:
				break;

			case WM_DESTROY:
				theApp.End_Game();
				return 0;
			default:
				break;
			}
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	AlamoApp::AlamoApp()
	{
		theGame = NULL;

		screenWidth = 0;
		screenHeight = 0;
		minSoundGain = 0.0f;
		maxSoundGain = 0.0f;

		engineInitParams.winParams.defaultX = 0;
		engineInitParams.winParams.defaultY = 0;
		engineInitParams.winParams.defaultHeight = 0;
		engineInitParams.winParams.defaultWidth = 0;

		renderingContext = NULL;
		openGLInitialized = false;
		openALInitialized = false;

		appError.Error(ALAES_NO_ERROR);
		appInitialized = false;

		renderNow = 0;
	}

	bool AlamoApp::Init_App(alaInitParams initParams)
	{
		engineInitParams = initParams;

		appInitialized = true;

		return appInitialized;
	}

	bool AlamoApp::Init_OpenGL(HWND hWnd)
	{
		return openGLInitialized;
	}

	bool AlamoApp::Init_OpenAL()
	{
		bool initOK = true;

		alutInit(0, NULL);

		alGetError();

		ALfloat listenerPosition[] = { 0.0,0.0,0.0 };
		ALfloat listenerVelocity[] = { 0.0,0.0,0.0 };
		ALfloat listenerOrientation[] = { 0.0,0.0,0.0,0.0,1.0,0.0 };

		alListenerfv(AL_POSITION, listenerPosition);
		if (alGetError() != AL_NO_ERROR)
		{
			initOK = false;
		}

		alListenerfv(AL_VELOCITY, listenerPosition);
		if (alGetError() != AL_NO_ERROR)
		{
			initOK = false;
		}

		alListenerfv(AL_ORIENTATION, listenerPosition);
		if (alGetError() != AL_NO_ERROR)
		{
			initOK = false;
		}

		if (initOK)
		{
			openALInitialized = true;
		}

		return (initOK);
		
	}

	bool AlamoApp::Render()
	{
		bool ok = true;
		assert(appInitialized);

		Clear_Background();
		renderNow++;
		ok = theGame->Render_Frame();
		renderNow--;

		if (ok == true)
		{
			glFlush();
			ok = (SwapBuffers(appDeviceContext) == TRUE) ? true : false;
		}
		else
		{
			theApp.App_Error(ALAES_FATAL_RENDERING_ERROR);
		}
		
		return ok;
	}

	void AlamoApp::Begin_Render_Now()
	{
		assert(renderNow == 0);
		renderNow++;
	}
	void AlamoApp::End_Render_Now()
	{
		assert(appInitialized);
		assert(renderNow == 1);

		glFlush();
		SwapBuffers(appDeviceContext);
		renderNow--;
	}


	bool AlamoApp::Init_Game_Subsystem(HWND hWnd)
	{
		bool ok = true;
		if (Init_OpenGL(hWnd))
		{

			ok = Init_OpenAL();

			if (ok == false)
			{
				App_Error(ALAES_OPENAL_INIT_FAILED);

			}
		}
		else
		{
			App_Error(ALAES_OPENGL_INIT_FAILED);
		}

		return (ok);

	}

	void AlamoApp::Cleanup_Game_Subsystem(bool timeToQuit)
	{
		Cleanup_OpenGL(timeToQuit);
		Cleanup_OpenAL();
	}

	void AlamoApp::Cleanup_OpenGL(bool timeToQuit)
	{
		if (timeToQuit)
		{
			ChangeDisplaySettings(NULL, 0);

			wglDeleteContext(theApp.renderingContext);
			theApp.renderingContext = NULL;
		}
	}

	void AlamoApp::Cleanup_OpenAL()
	{
		alutExit();
	}

	void AlamoApp::Create_OpenGL_Rendering_Surface(HWND hWnd)
	{
		bool ok = true;

		appDeviceContext = GetDC(hWnd);

		//pixel formate descriptor
		PIXELFORMATDESCRIPTOR pfd = {
			sizeof(PIXELFORMATDESCRIPTOR),		// size of this pfd
			1,									// version number
			PFD_DRAW_TO_WINDOW |				// support window
			PFD_SUPPORT_OPENGL |				// support OpenGL
			PFD_DOUBLEBUFFER,					// double buffered
			PFD_TYPE_RGBA,						// RGBA type
			24,									// 24-bit color depth
			0, 0, 0, 0, 0, 0,					// color bits ignored
			0,									// no alpha buffer
			0,									// shift bit ignored
			0,									// no accumulation buffer
			0, 0, 0, 0,							// accum bits ignored
			32,									// 32-bit z-buffer
			0,									// no stencil buffer
			0,									// no auxiliary buffer
			PFD_MAIN_PLANE,						// main layer
			0,									// reserved
			0, 0, 0								// layer masks ignored
		};

		//pixel formate index
		int pfi = ChoosePixelFormat(appDeviceContext, &pfd);

		//slected pixel format
		int spf = theGame->Check_Pixel_Format(pfi, &pfd);


		if (spf != pfi)
		{
			ok = SetPixelFormat(appDeviceContext, spf, &pfd);
		}
		else
		{
			ok = SetPixelFormat(appDeviceContext, pfi, &pfd);
		}

		if (ok == false)
		{
			App_Error(ALAES_OPENGL_INIT_FAILED);
			openGLInitialized = false;
		}
		else
		{
			renderingContext = wglCreateContext(appDeviceContext);

			if (renderingContext != NULL)
			{
				ok = wglMakeCurrent(appDeviceContext, renderingContext);
			}
		}

		if (ok == true)
		{
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, screenHeight, screenHeight, 0, -1, -1);
		}
		openGLInitialized = ok;
	}

	void AlamoApp::End_Game()
	{
		theApp.theGame->Game_Cleanup();

		theApp.Cleanup_Game_Subsystem(true);

		//Send message to the message que;
		PostQuitMessage(0);
	}

	inline alaGame * AlamoApp::Game()
	{
		assert(appInitialized);
		return (theGame);
	}

	void AlamoApp::Clear_Background()
	{
		alaColorRGBA backColor = Background_Surface_Color();
		if (Background_Surface_Color() != NO_BACK_COLOR)
		{
			glClearColor(
				backColor.R,
				backColor.G,
				backColor.B,
				backColor.A);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		}
	}

		inline alaColorRGBA AlamoApp::Background_Surface_Color()
	{
		return engineInitParams.openParams.openGLParams.surfaceBackGroundColor;
	}

	inline int AlamoApp::Screen_Height()
	{
		return (screenHeight);
	}

	inline int AlamoApp::Screen_Width()
	{
		return (screenWidth);
	}

	bool AlamoApp::Set_Screen_Resolution()
	{
		bool ok = false;
		int items = engineInitParams.winParams.screenMode.totalItems;

		if (items <= 0)
		{
			return true;
		}

		DEVMODE screenSettings;

		memset(&screenSettings, 0, sizeof(DEVMODE));

		alaScreenResolution res;

		DWORD width, height, bits;

		for(int i=0;i< items && ok == false;i++)
		{
			res = engineInitParams.winParams.screenMode.resolutions[i];

			switch (res)
			{
				case Alamo::ALASR_640X480X24:
					width = 640;
					height = 480;
					bits = 24;
					break;
				case Alamo::ALASR_640X480X32:
					width = 640;
					height = 480;
					bits = 32;
					break;
				case Alamo::ALASR_800X600X24:
					width = 800;
					height = 600;
					bits = 24;
					break;
				case Alamo::ALASR_800X600X32:
					width = 640;
					height = 480;
					bits = 32;
					break;
				case Alamo::ALASR_1024X768X24:
					width = 1024;
					height = 768;
					bits = 24;
					break;
				case Alamo::ALASR_1024X768X32:
					width = 1024;
					height = 768;
					bits = 32;
					break;
				case Alamo::ALASR_1152X864X24:
					width = 1152;
					height = 864;
					bits = 24;
					break;
				case Alamo::ALASR_1152X864X32:
					width = 1152;
					height = 864;
					bits = 32;
					break;
				default:
					App_Error(ALAES_INVALID_SCREEN_RESOLUTION);
					return false;
					break;
			}
			screenSettings.dmPelsHeight = width;
			screenSettings.dmPelsHeight = height;
			screenSettings.dmBitsPerPel = bits;
			screenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
			if (ChangeDisplaySettings(&screenSettings, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL)
			{
				ok = true;
			}
		} 

		return ok;
		
	}


	VOID CALLBACK Animation_Timer_Handler(HWND hwnd, 
		UINT uMsg,
		WPARAM isEvent,
		DWORD dwTime)
	{
		::theApp.RWS_Set_Time_TO_Update_Frame(true);
		Create_Animation_Timer(hwnd);
	}

	void Create_Animation_Timer(HWND hWnd)
	{
		::SetTimer(hWnd,
			ALAMO_ANIMATION_TIMER_ID,
			::theApp.engineInitParams.openParams.millisecondsBetweenFrames,
			&Animation_Timer_Handler);
	}

#ifndef DEBUGOFF
	bool AlamoApp::Open_LogFile(char *logFileName)
	{
		logFile.open(logFileName);
		return logFile.is_open();
	}

	bool AlamoApp::Write_To_Log_File(char *stringToWrite)
	{
		logFile << stringToWrite << "\n";
		return true;
	}

	void AlamoApp::Close_Log_File()
	{
		logFile.close();
	}
#endif

}

/* END AlamoApp.cpp*/