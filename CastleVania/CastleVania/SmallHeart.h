﻿#ifndef __SMALLHEART_H__
#define __SMALLHEART_H__


#include "Item.h"

#define SMALLHEART_GRAVITY 0.04f
#define SMALLHEART_TIMEDISPLAYMAX 6000
#define SMALLHEART_TIMEWAITMAX 150

#define SMALLHEART_SPEED_X 0.05f

#define LIMIT_X 25 //x- xStart <=25


class SmallHeart : public Item
{
private:
	float xStart; // vị trí của x ban dầu

public:
	SmallHeart(float X = 0, float Y = 0);

	void Update(DWORD dt, vector<LPGAMEOBJECT>* listObject = NULL); // Update và xét va chạm đất


	virtual ~SmallHeart();
};



#endif 
