#pragma once
#ifndef __EFFECT_FIRE_
#define __EFFECT_FIRE_

#include "Effect.h"
#define FIRE_WIDTH 32
#define FIRE_HEIGHT 28
class EffectFire:public Effect
{
private:
	int countLoop; //Số lần lặp của ngọn lửa
public:
	EffectFire(float x = 0, float y = 0, int countLoop = 1);
	~EffectFire();
	void Update(DWORD dt);
};
#endif
