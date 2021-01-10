#include "InvisibilityPotionItem.h"


InvisibilityPotionItem::InvisibilityPotionItem(float X, float Y)
{
	ObjectType = objectType::INVINSIBILTYPOTION;
	objectTexture = TextureManager::GetInstance()->GetTexture(ObjectType);
	objectSprite = new GameSprite(objectTexture, 0);

	this->x = X;
	this->y = Y;

	vy = INVISIBILITYPOTION_GRAVITY;
	timeDisplayMax = INVISIBILITYPOTION_TIMEDISPLAYMAX;
	timeDisplayed = 0;
	timeWaited = 0;
	timeWaitMax = INVISIBILITYPOTION_TIMEWAITMAX;
}

InvisibilityPotionItem::~InvisibilityPotionItem()
{
}
