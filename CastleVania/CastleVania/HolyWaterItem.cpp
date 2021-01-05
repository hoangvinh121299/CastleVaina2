#include "HolyWaterItem.h"

HolyWaterItem::HolyWaterItem(float X, float Y)
{
	objectTexture = TextureManager::GetInstance()->GetTexture(objectType::ITEMHOLYWATER);
	objectSprite = new GameSprite(objectTexture, 0);
	ObjectType = objectType::ITEMHOLYWATER;

	this->x = X;
	this->y = Y;
	vy = ITEMHOLYWATER_GRAVITY;
	timeDisplayMax = ITEMHOLYWATER_TIMEDISPLAYMAX;
	timeDisplayed = 0;
	timeWaited = 0;
	timeWaitMax = ITEMHOLYWATER_TIMEWAITMAX;
}

HolyWaterItem::~HolyWaterItem()
{
}
