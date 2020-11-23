#pragma once
#ifndef __LARGEHEART__
#define __LARGEHEART__
#include "Item.h"
#include "TextureManager.h"

#define LARGEHEART_GRAVITY 0.25f
#define LARGEHEART_TIMEDISPLAYMAX 3000
#define LARGEHEART_TIMEWAITMAX 300
class LargeHeart:public Item
{
public:
	LargeHeart(float x = 0,float y = 0);
	~LargeHeart();
};
#endif
