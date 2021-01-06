#pragma once
#ifndef  __ITEMBOOMERANG_H__
#define __ITEMBOOMERANG_H__

#define ITEMBOOMERANG_GRAVITY 0.25f
#define ITEMBOOMERANG_TIMEDISPLAYMAX 3000
#define ITEMBOOMERANG_TIMEWAITMAX 300

#include "item.h" 
class BoomerangItem :
	public Item
{
public:
	BoomerangItem(float X, float Y);
	virtual ~BoomerangItem();
};

#endif