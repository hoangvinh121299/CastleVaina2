#include "CrossItem.h"

CrossItem::CrossItem(float X, float Y)
{
	ObjectType = objectType::CROSS;
	objectTexture = TextureManager::GetInstance()->GetTexture(ObjectType);
	objectSprite = new GameSprite(objectTexture, 0);

	this->x = X;
	this->y = Y;
	vy = CROSS_GRAVITY;
	timeDisplayMax = CROSS_TIMEDISPLAYMAX;
	timeDisplayed = 0;
	timeWaited = 0;
	timeWaitMax = CROSS_TIMEWAITMAX;
}

CrossItem::~CrossItem()
{
}
