#pragma once
#ifndef  __HOLLYWATER_H__
#define __HOLLYWATER_H__



#define HOLLYWATER_SPEED_X 0.22f
#define HOLLYWATER_SPEED_Y 0.18f
#define HOLYWATER_GRAVITY 0.001f//5f
#include "Weapon.h"

class HolyWater : public Weapon
{
private:
	GameSprite* _spriteIcon;
	bool isCollisionBrick;
	int CountLoop; // Số lần lặp lại việc vẽ lúc nổ Holywater.
	Camera* camera;

public:
	HolyWater(Camera* camera);
	virtual ~HolyWater();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void getBoundingBox(float& left, float& top, float& right, float& bottom);
	void updatePositionWithSimon();
	void attack(float X, float Y, int Direction);
	void renderIcon(float X, float Y);
	void Render(Camera* camera);

};



#endif  
