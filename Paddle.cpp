#include "Paddle.h"
#include "AlamoType.h"
bool paddle::Move()
{
	bool ok = true;
	
	Alamo::alaVector2D vel = Movement();
	Y(Y() + vel.Y());
	vel.Y(0);
	Movement(vel);

	return ok;
}
void paddle::Movement(Alamo::alaVector2D direction) {
	assert(direction.X() == 0);
	alaSprite::Movement(direction);
}