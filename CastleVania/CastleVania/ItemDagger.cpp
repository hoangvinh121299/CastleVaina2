#include "ItemDagger.h"



ItemDagger::ItemDagger(float X, float Y)
{
	ObjectType = objectType::ITEMDAGGER;
	objectTexture = TextureManager::GetInstance()->GetTexture(ObjectType);
	objectSprite = new GameSprite(objectTexture, 0);

	this->x = X;
	this->y = Y;
	vy = ITEMDAGGER_GRAVITY;
	timeDisplayMax = ITEMDAGGER_TIMEDISPLAYDMAX;
	timeDisplayed = 0;
	timeWaited = 0;
	timeWaitMax = ITEMDAGGER_TIMEWAITMAX;
}

ItemDagger::~ItemDagger()
{
}
