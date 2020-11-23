#pragma once
#ifndef __EFFECT_HIT__
#define __EFFECT_HIT__

#include <d3dx9.h>
#include "GameSprite.h"
#include "Effect.h"
class EffectHit:public Effect
{
public:
	EffectHit(float x = 0, float y = 0);
	~EffectHit();
	void Update(DWORD dt);
};

#endif // !__EFFECT_HIT__

#ifndef HIT_ADD_EFFECT
#define HIT_ADD_EFFECT(listEffectm, gameObject)\
listEffect.push_back(new EffectHit(gameObject->getX() +14, gameObject->getY()+14));\

#endif