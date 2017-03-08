#pragma once
#ifndef _PADDLE_H_
#define _PADDLE_H_
#include "AlamoSprite.h"
#include "AlamoType.h"
class paddle : public::Alamo::alaSprite
{
public:
	bool Move();
	void Movement(Alamo::alaVector2D direction);
	Alamo::alaVector2D Movement();
};

inline Alamo::alaVector2D paddle::Movement() {
	return alaSprite::Movement();
}
#endif
