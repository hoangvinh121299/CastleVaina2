#pragma once
#ifndef __EFFECT_H__
#define __EFFECT_H__

#include "GameSprite.h"
#include"GameTexture.h"
#include "TextureManager.h"
#include "Camera.h"
class Effect
{
protected:
	GameTexture* effectTexture;
	GameSprite* effectSprite;
	float x;
	float y;
	float isFinish;
public:
	Effect();
	virtual ~Effect();
	virtual void Render(Camera* camera);
	virtual void Update(DWORD dt);

	bool getFinish();
	void setFinish(int temp);
};
#endif
