#pragma once
#ifndef __UPGRADEMORNINGSTAR__
#define __UPGRADEMORNINGSTAR__

#define UPGRADEMORNINGSTAR_GRAVITY 0.25f
#define UPGRADEMORNINGSTAR_TIMEDISPLAYMAX 3000
#define UPGRADEMORNINGSTAR_TIMEWAITMAX 300

#include "Item.h"
#include "TextureManager.h"
class UpgradeMorningStar:public Item
{
public:
	UpgradeMorningStar(float x = 0, float y = 0);
	~UpgradeMorningStar();
};

#endif