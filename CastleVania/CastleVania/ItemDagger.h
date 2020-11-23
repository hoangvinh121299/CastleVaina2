#pragma once
#ifndef __ITEM_DAGGER__
#define __ITEM_DAGGER__

#define ITEMDAGGER_GRAVITY 0.25f
#define ITEMDAGGER_TIMEDISPLAYDMAX 3000
#define ITEMDAGGER_TIMEWAITMAX 300

#include "Item.h"
#include"TextureManager.h"
class ItemDagger :public Item
{
public:
	ItemDagger(float x = 0, float y = 0);
	~ItemDagger();
};

#endif