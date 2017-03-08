#pragma once
#ifndef _BALL_H_
#define _BALL_H_
#include "AlamoSprite.h"
class ball :public Alamo::alaSprite
{
public:
	enum BounceDirection {
		X_DIRECTION,
		Y_DIRECTION
	};

public:
	void Bounce(BounceDirection direction);
};
#endif