#pragma once
#ifndef __MONEY_BAG_EXTRA__
#define __MONEY_BAG_EXTRA__

#include "Item.h"

#define MONEY_EXTRA_TIMEDISPLAYMAX 5000
#define MONEY_EXTRA_TIMEWAITMAX 300
#define	MONEY_EXTRA_GRAVITY 0.25f

class MoneyBagExtra:public Item
{
public:
	MoneyBagExtra(float x = 0, float y = 0);
	~MoneyBagExtra();
	void Render(Camera* camera);
};

#endif