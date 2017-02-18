
#ifndef _ALAMO_GAME_H_
#define _ALAMO_GAME_H_

#include "Alamo.h"
#include "AlamoType.h"
#include "AlamoMsgMap.h"

namespace Alamo
{

	typedef int alaBitmapId;

	static const alaBitmapId BMPID_UNKNOWN_BITMAP = -1;

	class alaGame
	{
	public:

		alaGame();
		~alaGame();

		virtual bool On_App_Load();
		virtual bool Init_Game();
		virtual bool Init_Level();


		virtual bool Handle_Mesaage(
			HWND hWnd,
			UINT msg,
			WPARAM wParam,
			LPARAM lParam);

		virtual bool Update_Frame();
		virtual bool Render_Frame();
		virtual bool Game_Cleanup();

		bool alaGame::Load_Background(
			alaString fileName,
			int width,
			int height);

		virtual void Level_Done(bool levelIsDone);
		virtual bool Level_Done();
		virtual bool Do_Level_Done();

		virtual void Game_Over(bool gameIsOver);
		virtual bool Game_Over();
		virtual bool Do_Game_Over();

		virtual int Check_Pixel_Format(int currentPixelFormat,PIXELFORMATDESCRIPTOR *formatDescriptor);

		virtual alaVector2D Game_Coords_To_Screen_Coords(const alaVector2D & vec2d);

		
		ATTACH_MESSAGE_MAP;

	private:


	protected:
		bool BlitBackground();

	private:
		bool gameOver;
		bool levelDone;

	};

	inline alaGame::~alaGame()
	{

	}

	inline bool
		alaGame::Init_Level()
	{
		levelDone = false;
		return true;
	}

	inline void
		alaGame::Level_Done(bool levelIsDone)
	{
		levelDone = levelIsDone;
	}

	inline bool
		alaGame::Level_Done()
	{
		return (levelDone = true);
	}

	inline bool
		alaGame::Do_Level_Done()
	{
		return (true);
	}

	inline void
		alaGame::Game_Over(bool gameIsOver)
	{
		gameOver = gameIsOver;
	}

	inline bool
		alaGame::Game_Over()
	{
		return gameOver;
	}


	
}//Namespace


#endif // !_ALAMO_GAME_H_

