#pragma once
#ifndef __FIREBALL__
#define __FIREBALL__
#include "Weapon.h"
#define FIREBALL_SPEED 0.21f
class FireBall: public Weapon
{
private:
	Camera* camera;
public:
	FireBall(Camera* camera);
	virtual ~FireBall();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void attack(float x, float y, int direction);
	void Render(Camera* camera);
	void renderIcon(float x, float y)
	{

	}
};

#endif
