#include "Alamo.h"
#include "AlamoAnimation.h"
#include "AlamoError.h"
#include "AlamoApp.h"
namespace Alamo
{

#define ALAMO_ANIMATION_NOT_PLAYING -10
	

	alaAnimation::alaAnimationFrame::alaAnimationFrame()
	{
		displayListID = 0;
	}
	alaAnimation::alaAnimationFrame::~alaAnimationFrame()
	{
		glDeleteLists(displayListID, 1);
	}
	bool alaAnimation::alaAnimationFrame::Load_Image(alaString fileName, 
		alaImageFileBase::alaImageFileFormat fileFormat)
	{
		bool ok = true;
		switch (fileFormat)
		{
		case Alamo::alaImageFileBase::ALAIFF_WINDOWS_BMP:
			ok = spriteImage.Load_From_BMP(fileName);
			break;
		case Alamo::alaImageFileBase::ALAIFF_TGA:
			ok = spriteImage.Load_From_TGA(fileName);
			break;
		default:
			ok = false;
			theApp.App_Error(ALAES_INVALID_FILE_TYPE);
			break;
		}

		displayListID = glGenLists(1);

		glNewList(displayListID, GL_COMPILE);

		spriteImage.Pre_Render();

		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 1.0f);
		glVertex2i(0, 0);

		glTexCoord2f(1.0f, 1.0f);
		glVertex2i(spriteImage.Width(), 0);

		glTexCoord2f(1.0f, 1.0f);
		glVertex2i(spriteImage.Width(), spriteImage.Height());

		glTexCoord2f(0.0f, 0.0f);
		glVertex2i(0, spriteImage.Height());
		glEnd();

		glEndList();

		return ok;

	}
	void alaAnimation::alaAnimationFrame::Bitmap_Transparent_Color(alaColorRGB color)
	{
		spriteImage.Transparent_Color(color);
	}
	alaColorRGB alaAnimation::alaAnimationFrame::Bitmap_Transparent_Color()
	{
		return spriteImage.Transparent_Color();
	}
	int alaAnimation::alaAnimationFrame::BitmapHeight()
	{
		return (spriteImage.Height());
	}
	int alaAnimation::alaAnimationFrame::BitmapWidth()
	{
		return (spriteImage.Width());
	}
	bool alaAnimation::alaAnimationFrame::Render()
	{
		bool ok = true;

		glCallList(displayListID);
		ok = (glGetError() == GL_NO_ERROR);
		return ok;
	}
	alaAnimation::alaAnimation()
	{
		currentFrame = 0;
		loop = false;
		loopStyle = alaAnimation::AN_FORWARD;
		currentLoopDirection = alaAnimation::AN_FORWARD;

		transparentColor = ALAMO_TEX_NO_TRANSPARENT_COLOR;
		currentStatus = alaAnimation::AN_NOT_STARTED;
	}
	alaAnimation::~alaAnimation()
	{
		for (unsigned int i = 0; i < allFrames.size(); i++) {
			if (allFrames[i] != NULL)
			{
				delete allFrames[i];
				allFrames[i] = NULL;
			}
		}
	}
	bool alaAnimation::Load_Image(alaString fileName,
		alaImageFileBase::alaImageFileFormat fileFormat)
	{
		bool ok = true;
		alaAnimationFrame * frame = new alaAnimationFrame;
		if (frame != NULL)
		{
			frame->Bitmap_Transparent_Color(transparentColor);

			ok = frame->Load_Image(fileName, fileFormat);
		}
		else
		{
			ok = false;
			theApp.App_Error(ALAES_OUT_OF_MEMORY);
		}
		if (ok)
		{
			allFrames.push_back(frame);
		}

		return ok;
	}
	int alaAnimation::BitmapHeight()
	{
		int height;

		if (allFrames.size() > 0)
		{
			height = allFrames[currentFrame]->BitmapHeight();
		}
		else
		{
			height = 0;
		}

		return (height);
	}
	int alaAnimation::BitmapWidth()
	{
		int width;

		if (allFrames.size() > 0)
		{
			width = allFrames[currentFrame]->BitmapWidth();
		}
		else
		{
			width = 0;
		}

		return (width);
	}
	void alaAnimation::Loop_Animation(bool loopAnimation, alaAnimation::alaLoopStyle loopDirection)
	{
		loop = loopAnimation;
		loopStyle = loopDirection;

		if (loop == true)
		{
			if ((loopStyle == alaAnimation::alaLoopStyle::AN_FORWARD) ||
				(loopStyle == alaAnimation::alaLoopStyle::AN_FORWARD_THEN_REVERSE))
			{
				currentFrame = 0;
				currentLoopDirection = alaAnimation::alaLoopStyle::AN_FORWARD;
			}
			else if (loopStyle ==alaAnimation::alaLoopStyle::AN_REVERSE)
			{
				currentFrame = allFrames.size() - 1;
				currentLoopDirection = alaAnimation::alaLoopStyle::AN_REVERSE;
			}
		}
	}
	bool alaAnimation::Loop_Animation()
	{
		return loop;
	}
	void alaAnimation::Bitmap_Transparent_Color(alaColorRGB color)
	{
		transparentColor = color;
	}
	alaColorRGB alaAnimation::Bitmap_Transparent_Color()
	{
		return transparentColor;
	}
	void alaAnimation::Current_Frame(int index)
	{
		if (index < allFrames.size())
		{
			currentFrame = index;
		}
		else
		{
			currentFrame = -1;
			theApp.App_Error(ALAES_INDEX_OUT_OF_RANGE);
		}
	}

	int alaAnimation::Current_Frame()
	{
		return currentFrame;
	}
	int alaAnimation::Total_Frames()
	{
		return allFrames.size();
	}
	void alaAnimation::Reset()
	{
		if (loop == false)
		{
			currentFrame = 0;
			currentStatus = alaAnimation::AN_NOT_STARTED;

		}
		else if ((loopStyle == alaAnimation::AN_FORWARD) || (loopStyle == alaAnimation::AN_FORWARD_THEN_REVERSE))
		{
			currentFrame = 0;
			currentLoopDirection = alaAnimation::AN_FORWARD;
			currentStatus = alaAnimation::AN_NOT_STARTED;
		}
		else if (loopStyle == alaAnimation::AN_REVERSE)
		{
			currentFrame = allFrames.size() - 1;
			currentLoopDirection = alaAnimation::AN_REVERSE;
			currentStatus = alaAnimationStatus::AN_NOT_STARTED;
		}
	}
	bool alaAnimation::Play()
	{
		assert(allFrames.size() > 1);
		currentStatus = alaAnimation::AN_PLAYING;

		bool ok = true;

		if (currentFrame != ALAMO_ANIMATION_NOT_PLAYING)
		{
			ok = allFrames[currentFrame]->Render();
		}
		if (ok)
		{
			if (loop == false)
			{
				currentFrame++;

				if (currentFrame >= allFrames.size())
				{
					currentStatus = alaAnimation::alaAnimationStatus::AN_DONE;
					currentFrame = ALAMO_ANIMATION_NOT_PLAYING;
				}
			}
			else
			{
				if (loopStyle == alaAnimation::AN_FORWARD)
				{
					currentFrame++;
					if (currentFrame >= allFrames.size())
					{
						Reset();
						currentStatus = alaAnimation::AN_AT_END_OF_LOOP;
					}
				}
				else if (loopStyle == alaAnimation::AN_FORWARD_THEN_REVERSE)
				{
					if (currentLoopDirection == alaAnimation::AN_FORWARD)
					{
						currentFrame++;
					}
					else
					{
						currentFrame--;
					}

					if ((currentLoopDirection == alaAnimation::AN_FORWARD) && 
						(currentFrame >= allFrames.size()))
					{
						currentFrame = allFrames.size() - 2;
						currentLoopDirection = alaAnimation::AN_REVERSE;
					}
					else if ((currentLoopDirection == alaAnimation::AN_REVERSE) &&
						(currentFrame<0))
					{
						currentFrame = 1;
						currentLoopDirection = alaAnimation::AN_FORWARD;
						currentStatus = alaAnimation::AN_AT_END_OF_LOOP;
					}
				}
				else if (loopStyle == alaAnimation::AN_REVERSE)
				{
					currentFrame--;
					if (currentFrame < 0)
					{
						Reset();
						currentStatus = alaAnimation::AN_AT_END_OF_LOOP;
					}
				}
			}
		}
		else
		{
			ok = false;
			currentStatus = alaAnimation::AN_ANIMATION_ERROR;
			theApp.App_Error(ALAES_FATAL_RENDERING_ERROR);
			currentFrame = ALAMO_ANIMATION_NOT_PLAYING;
		}

		return ok;
	}
	alaAnimation::alaAnimationStatus alaAnimation::Status()
	{
		return currentStatus;
	}
}//Namespace