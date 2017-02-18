#include "AlamoSpriteBase.h"
#include "AlamoType.h"
namespace Alamo
{
	bool alaSpriteBase::Move()
	{
		bool ok = true;
		x += velocity.X();
		y += velocity.Y();
		return ok;
	}
	 void alaSpriteBase::X(int upLeftX)
	{
		x = upLeftX;
	}
	int alaSpriteBase::X()
	{
		return x;
	}
	void alaSpriteBase::Y(int upLeftY)
	{
		y = upLeftY;
	}
	int alaSpriteBase::Y()
	{
		return y;
	}
	void alaSpriteBase::Bounding_Rectangle(alaBitmapRegion rect)
	{
		boundingRectangle = rect;
	}

	alaBitmapRegion alaSpriteBase::Bounding_Rectangle()
	{
		return boundingRectangle;
	}

	void alaSpriteBase::Movement(alaVector2D direction)
	{
		velocity = direction;
	}

	alaVector2D alaSpriteBase::Movement()
	{
		return velocity;
	}

	bool alaSpriteBase::Render()
	{
		return false;
	}

	alaString alaSpriteBase::Type()
	{
		return ("alaSpriteBase");
	}

	alaSpriteBase::alaSpriteBase()
	{
		x = y = 0;
		boundingRectangle.top = boundingRectangle.bottom = 0;
		boundingRectangle.left = boundingRectangle.right = 0;
	}

	alaSpriteBase::~alaSpriteBase()
	{

	}

}

