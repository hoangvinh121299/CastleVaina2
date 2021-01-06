#include "StopWatchItem.h"

StopWatchItem::StopWatchItem(float X, float Y)
{
	ObjectType = objectType::STOPWATCH;
	objectTexture = TextureManager::GetInstance()->GetTexture(ObjectType);
	objectSprite = new GameSprite(objectTexture, 100);

	this->x = X;
	this->y = Y;
	vy = STOPWATCH_GRAVITY;
	timeDisplayMax = STOPWATCH_TIMEDISPLAYMAX; // set time hiển thị tối đa
	timeDisplayed = 0;
	timeWaited = 0;
	timeWaitMax = STOPWATCH_TIMEWAITMAX;
}

StopWatchItem::~StopWatchItem()
{
}
