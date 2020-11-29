#pragma once
#ifndef __DAGGER_H__
#define __DAGGER_H__

#include "Weapon.h"
#include "TextureManager.h"
#define DAGGER_SPEED 0.45f

class Dagger:public Weapon
{

private: 
	Camera* camera;
public:
	Dagger(Camera* camera);
	~Dagger();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void attack(float x, float y, int direction);
	void renderIcon(float x, float y);
};

#endif