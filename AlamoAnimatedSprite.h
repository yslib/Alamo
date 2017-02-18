
#ifndef _ALAMO_ANIMATED_SPRITE_H_
#define _ALAMO_ANIMATED_SPRITE_H_

#include "AlamoAnimation.h"
#include "AlamoSpriteBase.h"

namespace Alamo
{
	class alaAnimatedSprite :public alaSpriteBase
	{
	public:
		alaAnimatedSprite();
		~alaAnimatedSprite();

		int Animation(alaAnimation *animation);

		alaAnimation * Animation(int index);

		bool Render();

		int Bitmap_Height();
		int Bitmap_Width();

		void Current_Animation(int index);
		int Current_Animation();

		alaAnimation::alaAnimationStatus Animation_Status();

		void Reset_Animation();

		virtual alaString Type();

	private:
		std::vector<alaAnimation *> allAnimations;
		int currentAnimation;
	};
}

#endif