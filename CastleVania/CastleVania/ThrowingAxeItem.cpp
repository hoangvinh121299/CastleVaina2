#include "ThrowingAxeItem.h"

ThrowingAxeItem::ThrowingAxeItem(float X, float Y)
{
	ObjectType = objectType::ITEMTHROWINGAXE;
	objectTexture = TextureManager::GetInstance()->GetTexture(objectType::ITEMTHROWINGAXE);
	objectSprite = new GameSprite(objectTexture, 0);

	this->x = X;
	this->y = Y;
	vy = ITEMTHROWINGAXE_GRAVITY;
	timeDisplayMax = ITEMTHROWINGAXE_TIMEDISPLAYMAX;
	timeDisplayed = 0;
	timeWaited = 0;
	timeWaitMax = ITEMTHROWINGAXE_TIMEWAITMAX;
}

ThrowingAxeItem::~ThrowingAxeItem()
{
}
