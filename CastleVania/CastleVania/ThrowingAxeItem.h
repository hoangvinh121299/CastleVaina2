#pragma once
#ifndef __ITEMTHROWINGAXE_H__
#define __ITEMTHROWINGAXE_H__

#include "Item.h"
#include "TextureManager.h"


#define ITEMTHROWINGAXE_TIMEDISPLAYMAX 3000
#define ITEMTHROWINGAXE_GRAVITY 0.25f
#define ITEMTHROWINGAXE_TIMEWAITMAX 300

class ThrowingAxeItem :
	public Item
{
public:
	ThrowingAxeItem(float X = 0, float Y = 0);
	virtual ~ThrowingAxeItem();
};



#endif