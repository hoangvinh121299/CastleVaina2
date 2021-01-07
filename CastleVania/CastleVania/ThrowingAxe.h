#pragma once
#ifndef  __THROWINGAXE_H__
#define __THROWINGAXE_H__

#define THROWINGAXE_SPEED_X 0.2f
#define THROWINGAXE_SPEED_Y 0.55f
#define THROWINGAXE_GRAVITY 0.0015f


#include "Weapon.h"
//#include "Sound.h"
class ThrowingAxe :
	public Weapon
{
private:
	GameSprite* _spriteIcon;
	Camera* camera;

public:

	ThrowingAxe(Camera* camera);
	virtual ~ThrowingAxe();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void attack(float X, float Y, int Direction);
	virtual void renderIcon(float X, float Y);

};

#endif
