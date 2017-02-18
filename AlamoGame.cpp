#include "Alamo.h"
#include "AlamoGame.h"
#include "AlamoApp.h"

namespace Alamo
{
	START_MESSAGE_MAP(alaGame)


	END_MESSAGE_MAP(alaGame)

	alaGame::alaGame()
	{
		gameOver = false;
		levelDone = false;
	}

	bool alaGame::On_App_Load()
	{
		bool ok = true;

		alaInitParams initParams;
		initParams.winParams.appWindowTitile = "Game";
		initParams.winParams.defaultHeight = -1;
		initParams.winParams.defaultWidth = -1;
		initParams.openParams.millisecondsBetweenFrames = 0;


		//Initialize OPENGL

		//Initialize OPENAL

		theApp.Init_App(initParams);

		return ok;
	}

	int alaGame::Check_Pixel_Format(int currentPixelFormat,
		PIXELFORMATDESCRIPTOR *formatDescriptor)
	{
		return currentPixelFormat;
	}

	bool alaGame::Init_Game()
	{
		bool ok = true;

		return ok;
	}

	bool alaGame::Handle_Mesaage(HWND hWnd,
		UINT msg,
		WPARAM wParam,
		LPARAM lParam)
	{
		//switch (msg)
		//{
		//default:
		//	break;
		//}

		return false;
	}

	bool alaGame::Update_Frame()
	{
		return (true);
	}

	bool alaGame::Render_Frame()
	{
		return true;
	}

	bool alaGame::Game_Cleanup()
	{
		return (true);
	}

	bool alaGame::Load_Background(alaString fileName,
		int width, 
		int height)
	{
		return (true);
	}

	bool alaGame::Do_Game_Over()
	{
		theApp.End_Game();
		return true;
	}

	alaVector2D
		alaGame::Game_Coords_To_Screen_Coords(const alaVector2D & vec2d)
	{
		assert(false);
		return (alaVector2D(0, 0));
	}

}//Namespace 