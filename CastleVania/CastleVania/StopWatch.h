#pragma once
#ifndef __STOPWATCH_H__
#define __STOPWATCH_H__

#include "Weapon.h"
//#include "Sound.h"


class StopWatch :
	public Weapon
{
private:
	DWORD TimeSpent; // thời gian đã chờ

public:
	StopWatch();
	virtual ~StopWatch();

	virtual void attack(float X, float Y, int Direction);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render(Camera* camera);
	virtual bool isColission(GameObject* obj);
	virtual void renderIcon(float X, float Y);
};

#endif