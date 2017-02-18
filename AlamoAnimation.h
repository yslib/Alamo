
#ifndef _ALAMO_ANIMATION_H_
#define _ALAMO_ANIMATION_H_

#include "AlamoType.h"
#include "AlamoImageFileBase.h"
#include "AlamoTexture.h"


namespace Alamo
{
	class alaAnimation
	{
	public:
		enum alaAnimationStatus
		{
			AN_NOT_STARTED,
			AN_PLAYING,
			AN_DONE,
			AN_AT_END_OF_LOOP,
			AN_ANIMATION_ERROR
		};
		enum alaLoopStyle
		{
			AN_FORWARD,
			AN_REVERSE,
			AN_FORWARD_THEN_REVERSE
		};

	public:
		alaAnimation();
		~alaAnimation();

		bool Load_Image(alaString fileName, alaImageFileBase::alaImageFileFormat fileFormat);

		int BitmapHeight();
		int BitmapWidth();

		void Loop_Animation(bool loopAnimation, 
			alaAnimation::alaLoopStyle loopDirection = alaAnimation::alaLoopStyle::AN_FORWARD);

		bool Loop_Animation();

		void Bitmap_Transparent_Color(alaColorRGB color);

		alaColorRGB Bitmap_Transparent_Color();

		void Current_Frame(int index);

		int Current_Frame();

		int Total_Frames();

		void Reset();

		bool Play();

		alaAnimation::alaAnimationStatus Status();
		
	private:
		class alaAnimationFrame
		{
		public:
			alaAnimationFrame();
			~alaAnimationFrame();

			bool Load_Image(alaString fileName, alaImageFileBase::alaImageFileFormat fileFormat);

			void Bitmap_Transparent_Color(alaColorRGB color);

			alaColorRGB Bitmap_Transparent_Color();

			int BitmapHeight();

			int BitmapWidth();

			bool Render();

		private:
			alaTexture spriteImage;
			GLuint displayListID;
		};

	private:
		std::vector<alaAnimationFrame *> allFrames;

		int currentFrame;

		bool loop;

		alaLoopStyle loopStyle;
		alaLoopStyle currentLoopDirection;

		alaAnimationStatus currentStatus;

		alaColorRGB transparentColor;

	};
}//Namespace
#endif