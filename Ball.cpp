#include "Ball.h"
#include "AlamoType.h"

void ball::Bounce(ball::BounceDirection direction) {
	Alamo::alaVector2D vel = Movement();
	switch (direction)
	{
	case ball::X_DIRECTION:
		vel.X(vel.X()*-1);
		break;
	case ball::Y_DIRECTION:
		vel.Y(vel.Y()*-1);
		break;
	default:
		break;
	}
	Movement(vel);
}