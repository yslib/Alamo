
#ifndef _ALAMO_SPRITE_BASE_H_
#define _ALAMO_SPRITE_BASE_H_

#include "AlamoScreenObject.h"
#include "AlamoType.h"

class alaBitmapRegion;

namespace Alamo
{
	class alaSpriteBase :public alaScreenObject
	{
	public:
		bool Move();

		void X(int upLeftX);

		int X();

		void Y(int upLeftY);

		int Y();

		void Bounding_Rectangle(alaBitmapRegion rect);

		alaBitmapRegion Bounding_Rectangle();

		virtual void Movement(alaVector2D direction);

		alaVector2D Movement();

		virtual bool Render();

		virtual alaString Type();

	protected:
		alaSpriteBase();

		~alaSpriteBase();

	protected:
		int x, y;

		alaBitmapRegion boundingRectangle;

		alaVector2D velocity;

	};

}//Namespace


#endif /*_ALAMO_SPRITE_BASE_H_*/
