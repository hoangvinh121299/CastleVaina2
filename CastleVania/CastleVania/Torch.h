#pragma once
#ifndef __TORCH_H__
#define __TORCH_H__

#include "GameObject.h"
#include "TextureManager.h"
class Torch:public GameObject
{
public:
	Torch(float x = 0, float y = 0);
	~Torch();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render(Camera* camera);
};
#endif
