#pragma once
#ifndef __MONEYBAG_H__
#define __MONEYBAG_H__

#define MONEYBAG_TIMEDISPLAYMAX 3000
#define MONEYBAG_TIMEWAITMAX 300
#define MONEYBAG_GRAVITY 0.25f

#define MONEYBAG_ANI_RED 0
#define MONEYBAG_ANI_WHITE 1
#define MONEYBAG_ANI_PURPLE 2

#include "Item.h"
class MoneyBag: public Item
{
public:
	MoneyBag(float x, float y, objectType TypeofMoneyBag);
	virtual ~MoneyBag();
	virtual void Render(Camera* camera);

};
#endif
