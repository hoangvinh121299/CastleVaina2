#pragma once
#ifndef __ITEMDOUBLESHOT_H__
#define __ITEMDOUBLESHOT_H__

#define ITEMDOUBLESHOT_GRAVITY 0.25f
#define ITEMDOUBLESHOT_TIMEDISPLAYMAX 5000
#define ITEMDOUBLESHOT_TIMEWAITMAX 300

#include "Item.h"
class DoubleShotItem :
	public Item
{
public:
	DoubleShotItem(float X, float Y);
	virtual ~DoubleShotItem();
};

#endif