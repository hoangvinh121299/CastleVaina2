#pragma once

#ifndef __CROSS_H__
#define __CROSS_H__

#include "Item.h"

#define CROSS_TIMEDISPLAYMAX 3000
#define CROSS_GRAVITY 0.25f
#define CROSS_TIMEWAITMAX 300

#define CROSS_COLOR_BACKGROUND D3DCOLOR_XRGB(188, 188, 188) // M�u x�m 188, 188, 188


class CrossItem :
	public Item
{
public:
	CrossItem(float X = 0, float Y = 0);

	virtual ~CrossItem();
};


#endif 