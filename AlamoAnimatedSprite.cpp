#include "Alamo.h"
#include "AlamoAnimatedSprite.h"

namespace Alamo
{
	alaAnimatedSprite::alaAnimatedSprite()
	{
		x = y = 0;
		currentAnimation = -1;
	}
	alaAnimatedSprite::~alaAnimatedSprite()
	{
		for (int i = 0; i < allAnimations.size(); i++) {
			if (allAnimations[i] != NULL)
			{
				delete allAnimations[i];
			}
		}
	}

	//I dont know why there need to return value
	int alaAnimatedSprite::Animation(alaAnimation * animation)
	{
		assert(animation != NULL);
		allAnimations.push_back(animation);
		currentAnimation = allAnimations.size() - 1;
		return 1;
	}
	alaAnimation * alaAnimatedSprite::Animation(int index)
	{
		assert((index >= 0) && (index < allAnimations.size()));
		alaAnimation * animation;

		if (allAnimations.empty() == true)
		{
			animation = nullptr;
		}
		else
		{
			animation = allAnimations[index];
		}
		return animation;
	}
	bool alaAnimatedSprite::Render()
	{
		bool ok = true;

		assert(allAnimations.size() > 0);
		assert(currentAnimation >= 0);
		assert(currentAnimation < allAnimations.size());

		alaAnimation::alaAnimationStatus animationStatus =
			allAnimations[currentAnimation]->Status();

		if ((animationStatus == alaAnimation::AN_NOT_STARTED) ||
			(animationStatus == alaAnimation::AN_PLAYING) ||
			(animationStatus == alaAnimation::AN_AT_END_OF_LOOP))
		{
			glPushMatrix();
			glTranslatef((float)x, (float)y, 0.0f);

			ok = allAnimations[currentAnimation]->Play();
			glPushMatrix();
		}
		return ok;
	}
	int alaAnimatedSprite::Bitmap_Height()
	{
		assert(allAnimations.size() > 0);
		return (allAnimations[currentAnimation]->BitmapHeight());
	}
	int alaAnimatedSprite::Bitmap_Width()
	{
		assert(allAnimations.size() > 0);
		return (allAnimations[currentAnimation]->BitmapWidth());
		return 0;
	}
	void alaAnimatedSprite::Current_Animation(int index)
	{
		assert(allAnimations.size() > 0);
		assert((index >= 0) && (index < allAnimations.size()));
		currentAnimation = index;
	}
	int alaAnimatedSprite::Current_Animation()
	{
		return currentAnimation;
	}
	alaAnimation::alaAnimationStatus alaAnimatedSprite::Animation_Status()
	{
		assert(allAnimations.size() > 0);
		assert(currentAnimation >= 0);
		assert(currentAnimation < allAnimations.size());

		return allAnimations[currentAnimation]->Status();
	}
	void alaAnimatedSprite::Reset_Animation()
	{
		assert(allAnimations.size() > 0);
		assert(currentAnimation >= 0);
		assert(currentAnimation < allAnimations.size());

		allAnimations[currentAnimation]->Reset();
	}
	alaString alaAnimatedSprite::Type()
	{
		return ("alaAnimatedSpirite");
	}
}