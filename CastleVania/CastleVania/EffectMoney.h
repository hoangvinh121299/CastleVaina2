#pragma once
#ifndef __EFFECT_MONEY__
#define __EFFECT_MONEY__

#include "Effect.h"
class EffectMoney:public Effect 
{
public:
	EffectMoney(float x, float y, objectType typeEffectOfMoney);
	void Update(DWORD dt);
	virtual ~EffectMoney();
};

#endif