#pragma once
#ifndef __INVISIBILITYPOTION_H__
#define __INVISIBILITYPOTION_H__

#define INVISIBILITYPOTION_TIMEDISPLAYMAX 3000
#define INVISIBILITYPOTION_GRAVITY 0.25f
#define INVISIBILITYPOTION_TIMEWAITMAX 300

#include "Item.h"
class InvisibilityPotionItem :
	public Item
{
public:
	InvisibilityPotionItem(float X = 0, float Y = 0);
	virtual ~InvisibilityPotionItem();
};

#endif

