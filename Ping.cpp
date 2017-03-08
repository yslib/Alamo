#include "Alamo.h"
#include "AlamoApp.h"
#include "Paddle.h"
#include "AlamoInputDevice.h"
#include "AlamoGame.h"
#include "AlamoScreenMode.h"
#include "Ball.h"
#include <ctime>

class ping :public Alamo::alaGame
{
public:
	bool On_App_Load();
	bool Init_Game();
	bool Init_Level();
	bool Update_Frame();
	bool Render_Frame();

	ATTACH_MESSAGE_MAP;

	bool On_Key_Down(Alamo::alaKeybordInputMessage &theMsg);
	bool Ball_Hit_Paddle();

	void Set_Ball_Start_Position();

	void Set_Ball_Start_Direction();

	bool Do_Level_Done();
	bool Do_Game_Over();

private:
	ball theBall;
	paddle leftPaddle;
	paddle rightPaddle;
	Alamo::alaSprite theTrophy;

	Alamo::alaSprite scoreMarker;

	int player1Score;
	int player2Score;

	Alamo::alaBitmapRegion areaOfPlay;

};

CREATE_GAME_OBJECT(ping)

START_MESSAGE_MAP(ping)
	ON_WMKEYDOWN(On_Key_Down)
END_MESSAGE_MAP(ping)

bool ping::On_App_Load()
{
	bool ok = true;

	Alamo::alaInitParams initParams;
	initParams.openParams.fullScreenWindow = true;
	
	//initParams.winParams.screenMode.Add_Supported_Resolution(Alamo::alaScreenResolution::ALASR_1024X768X24);

	initParams.openParams.millisecondsBetweenFrames = 0;

	Alamo::theApp.Init_App(initParams);

	return ok;
}

bool ping::Init_Game()
{
	bool ok = true;

	Alamo::alaBitmapRegion boundingRect;

	areaOfPlay.top = 0;
	areaOfPlay.bottom = Alamo::theApp.Screen_Height() - 20;
	areaOfPlay.left = 0;
	areaOfPlay.right = Alamo::theApp.Screen_Width();

	theBall.Bitmap_Transparent_Color(Alamo::alaColorRGB(0.0f,1.0f,0.0f));

	ok = theBall.Load_Image("ball.bmp", Alamo::alaImageFileBase::ALAIFF_WINDOWS_BMP);

	if (ok == true) {
		srand((unsigned)time(NULL));

		boundingRect.top = 0;
		boundingRect.bottom = theBall.Bitmap_Height();
		boundingRect.left = 0;
		boundingRect.right = theBall.Bitmap_Width();
	}
	else
	{
		::MessageBoxA(NULL,
			Alamo::theApp.App_Error().Error_Mesaage().c_str(),
			NULL, 
			MB_OK| MB_ICONSTOP | MB_SYSTEMMODAL);
	}

	if (ok == true) 
	{
		leftPaddle.Bitmap_Transparent_Color(Alamo::alaColorRGB(0.0f, 1.0f, 0.0f));

		ok = leftPaddle.Load_Image("paddle.bmp", Alamo::alaImageFileBase::ALAIFF_WINDOWS_BMP);

		if (ok == false) {
			::MessageBoxA(NULL,
				Alamo::theApp.App_Error().Error_Mesaage().c_str(),
				NULL,
				MB_OK | MB_ICONSTOP | MB_SYSTEMMODAL);
		}
	}

		//if (ok == true) {
		//	scoreMarker.Bitmap_Transparent_Color(Alamo::alaColorRGB(0.0f, 1.0f, 0.0f));

		//	ok = scoreMarker.Load_Image("scoremarker.bmp", Alamo::alaImageFileBase::ALAIFF_WINDOWS_BMP);

		//	if (ok == false) {
		//		::MessageBoxA(NULL,
		//			Alamo::theApp.App_Error().Error_Mesaage().c_str(),
		//			NULL,
		//			MB_OK | MB_ICONSTOP | MB_SYSTEMMODAL);
		//	}
		//}

		//if (ok == true) {
		//	theTrophy.Bitmap_Transparent_Color(Alamo::alaColorRGB(0.0f, 1.0f, 0.0f));

		//	ok = theTrophy.Load_Image("trophy.bmp", Alamo::alaImageFileBase::ALAIFF_WINDOWS_BMP);
		//
		//}

	if (ok == true) {
		boundingRect.top = 3;
		boundingRect.left = 10;
		boundingRect.bottom = 63;
		boundingRect.right = 22;
		leftPaddle.Bounding_Rectangle(boundingRect);
		rightPaddle = leftPaddle;

		player1Score = player2Score = 0;

		Init_Level();
	}
	return ok;
}

bool ping::Init_Level()
{
	bool ok = true;

	Alamo::alaBitmapRegion boundingRect = leftPaddle.Bounding_Rectangle();

	leftPaddle.X(5);
	int paddlHeight = boundingRect.bottom - boundingRect.top;
	int initY = (areaOfPlay.bottom - areaOfPlay.top) / 2 - paddlHeight / 2;

	leftPaddle.Y(initY);

	int bitmapWidth = rightPaddle.Bitmap_Width();

	int initX = areaOfPlay.right - bitmapWidth - 5;
	rightPaddle.X(initX);

	rightPaddle.Y(initY);

	Set_Ball_Start_Direction();
	Set_Ball_Start_Position();

	Level_Done(false);

	return ok;

}

void ping::Set_Ball_Start_Position()
{
	int startX = rand();

	while (startX >= areaOfPlay.right) {
		startX /= 10;
	}

	int startY = rand();

	while (startY >= areaOfPlay.bottom) {
		startY /= 10;
	}

	theBall.X(startX);
	theBall.Y(startY);


}

void ping::Set_Ball_Start_Direction()
{
	int xDirection = rand();

	while (xDirection > 10) {
		xDirection /= 10;
	}
	if (xDirection < 3) {
		xDirection = 3;
	}

	int yDirection = rand();
	while (yDirection > 10) {
		yDirection /= 10;
	}
	if (yDirection < 3) {
		yDirection = 3;
	}

	if (theBall.X() >= (areaOfPlay.right - areaOfPlay.left) / 2) {
		xDirection *= -1;
	}
	if (theBall.Y() >= (areaOfPlay.bottom - areaOfPlay.top) / 2) {
		yDirection *= -1;
	}
}

bool ping::On_Key_Down(Alamo::alaKeybordInputMessage &theMsg)
{
	Alamo::alaVector2D paddlDirection;
	switch (theMsg.keyCode)
	{
	case Alamo::KC_UP_ARROW:
		paddlDirection.Y(-15);
		rightPaddle.Movement(paddlDirection);
		break;

	case Alamo::KC_DOWN_ARROW:
		paddlDirection.Y(15);
		rightPaddle.Movement(paddlDirection);
		break;

	case Alamo::KC_A:
		paddlDirection.Y(-15);
		leftPaddle.Movement(paddlDirection);
		break;
	case Alamo::KC_Z:
		paddlDirection.Y(15);
		leftPaddle.Movement(paddlDirection);
		break;
	default:
		break;
	}
	return false;		//不再向上传递
}

bool ping::Update_Frame()
{
	bool ok = true;

	if (Game_Over() == false) {
		theBall.Move();
		rightPaddle.Move();
		leftPaddle.Move();

		if (Ball_Hit_Paddle()) {
			theBall.Bounce(ball::X_DIRECTION);
		}

		if (theBall.X() + theBall.Bitmap_Width() < areaOfPlay.left) {
			player1Score++;

			if (player1Score >= 5) {
				Game_Over(true);
			}
			else
			{
				Level_Done(true);
			}
		}
		else if (theBall.X() > areaOfPlay.right) {
			player2Score++;
			if (player2Score >= 5) {
				Game_Over(true);
			}
			else
			{
				Level_Done(true);
			}
		}

		if (theBall.Y() <= areaOfPlay.top) {
			theBall.Y(1);
			theBall.Bounce(ball::Y_DIRECTION);
		}
		else if (theBall.Y() + theBall.Bounding_Rectangle().bottom >= areaOfPlay.bottom) {
			theBall.Y(areaOfPlay.bottom - theBall.Bounding_Rectangle().bottom - 1);
			theBall.Bounce(ball::Y_DIRECTION);
		}

		if (leftPaddle.Y() < areaOfPlay.top)
		{
			leftPaddle.Y(0);
		}
		else if (leftPaddle.Y() + leftPaddle.Bitmap_Height() > areaOfPlay.bottom)
		{
			leftPaddle.Y(areaOfPlay.bottom - leftPaddle.Bitmap_Height());
		}

		if (rightPaddle.Y() < areaOfPlay.top)
		{
			rightPaddle.Y(0);
		}
		else if (rightPaddle.Y() + rightPaddle.Bitmap_Height() > areaOfPlay.bottom)
		{
			rightPaddle.Y(areaOfPlay.bottom - rightPaddle.Bitmap_Height());
		}

	}

	return ok;
}

bool ping::Ball_Hit_Paddle()
{
	bool hitted = false;
	int paddleLeft, paddleRight, paddleTop, paddleBottom;
	int ballLeft, ballRight, ballTop, ballBottom;

	ballLeft = theBall.X() + theBall.Bounding_Rectangle().left;
	ballRight = theBall.X() + theBall.Bounding_Rectangle().right;
	ballTop = theBall.Y() + theBall.Bounding_Rectangle().top;
	ballBottom = theBall.Y() + theBall.Bounding_Rectangle().bottom;

	paddleLeft = leftPaddle.X() + leftPaddle.Bounding_Rectangle().left;
	paddleRight = leftPaddle.X() + leftPaddle.Bounding_Rectangle().right;
	paddleTop = leftPaddle.Y() + leftPaddle.Bounding_Rectangle().top;
	paddleBottom = leftPaddle.Y() + leftPaddle.Bounding_Rectangle().bottom;


	bool leftEdge = (ballLeft <= paddleRight) ? true : false;

	bool topEdge = (ballTop >= paddleTop && ballTop <= paddleBottom) ? true : false;

	bool bottomEdge = (ballBottom >= paddleTop && ballBottom <= paddleBottom) ? true : false;

	if ((leftEdge) && (topEdge || bottomEdge)) {
		theBall.X(paddleRight + 1);
		hitted = true;
	}
	else
	{
		paddleLeft = rightPaddle.X() + rightPaddle.Bounding_Rectangle().left;
		paddleRight = rightPaddle.X() + rightPaddle.Bounding_Rectangle().right;
		paddleTop = rightPaddle.Y() + rightPaddle.Bounding_Rectangle().top;
		paddleBottom = rightPaddle.Y() + rightPaddle.Bounding_Rectangle().bottom;


		bool leftEdge = (ballLeft <= paddleRight) ? true : false;

		bool topEdge = (ballTop >= paddleTop && ballTop <= paddleBottom) ? true : false;

		bool bottomEdge = (ballBottom >= paddleTop && ballBottom <= paddleBottom) ? true : false;



		bool rightEdge = (ballRight >= paddleLeft) ? true : false;

		topEdge = (ballTop >= paddleTop && ballTop <= paddleBottom) ? true : false;

		bottomEdge = (ballBottom >= paddleTop && ballBottom <= paddleBottom) ? true : false;

		if ((rightEdge) && (topEdge || bottomEdge)) {
			theBall.X(paddleRight + 1);
			hitted = true;

		}
	}
	return hitted;
}

bool ping::Render_Frame()
{
	theBall.Render();
	rightPaddle.Render();
	leftPaddle.Render();

	return true;
}

bool ping::Do_Level_Done()
{
	::Sleep(2000);
	return true;
}

bool ping::Do_Game_Over()
{
	bool noError = true;

	Alamo::theApp.Begin_Render_Now();
	//something rendering
	Alamo::theApp.End_Render_Now();

	//只有在Init_Level Do_Level_Done Do_Game_Over 中才能调用

	::Sleep(4000);

	alaGame::Do_Game_Over();			//always be called at the end of your Do_Game_Over()
	return noError;
}