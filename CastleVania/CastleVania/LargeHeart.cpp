#include "LargeHeart.h"

LargeHeart::LargeHeart(float x, float y)
{
	ObjectType = objectType::LARGEHEART;
	objectTexture = TextureManager::GetInstance()->GetTexture(ObjectType);
	objectSprite = new GameSprite(objectTexture, 100);

	this->x = x;
	this->y = y;

	vy = LARGEHEART_GRAVITY;
	timeDisplayMax = LARGEHEART_TIMEDISPLAYMAX;
	timeWaitMax = LARGEHEART_TIMEWAITMAX;
	timeDisplayed = 0;
	timeWaited = 0;
}

LargeHeart::~LargeHeart()
{

}