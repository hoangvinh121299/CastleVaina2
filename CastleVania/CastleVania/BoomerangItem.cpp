#include "BoomerangItem.h"

BoomerangItem::BoomerangItem(float X, float Y)
{
	ObjectType = objectType::ITEMBOOMERANG;
	objectTexture = TextureManager::GetInstance()->GetTexture(ObjectType);
	objectSprite = new GameSprite(objectTexture, 100);

	x = X;
	y = Y;
	health = 1;

	vy = ITEMBOOMERANG_GRAVITY;
	timeDisplayMax = ITEMBOOMERANG_TIMEDISPLAYMAX; // set time hiển thị tối đa
	timeDisplayed = 0;
	timeWaited = 0;
	timeWaitMax = ITEMBOOMERANG_TIMEWAITMAX;


}

BoomerangItem::~BoomerangItem()
{
}
