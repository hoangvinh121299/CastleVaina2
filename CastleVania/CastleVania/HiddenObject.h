#pragma once
#include "GameObject.h"
class HiddenObject:public GameObject
{

private: 
	int width;
	int height;
public:
	HiddenObject(float x, float y, float w, float h);
	~HiddenObject();

	virtual void getBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects =NULL);
	virtual void Render(Camera* camera);

};

