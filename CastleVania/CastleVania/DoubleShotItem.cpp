#include "DoubleShotItem.h"

DoubleShotItem::DoubleShotItem(float X, float Y)
{
	ObjectType = objectType::ITEMDOUBESHOT;
	objectTexture = TextureManager::GetInstance()->GetTexture(ObjectType);
	objectSprite = new GameSprite(objectTexture, 100);

	x = X;
	y = Y;
	health = 1;

	vy = ITEMDOUBLESHOT_GRAVITY;
	timeDisplayMax = ITEMDOUBLESHOT_TIMEDISPLAYMAX; // set time hiển thị tối đa
	timeDisplayed = 0;
	timeWaited = 0;
	timeWaitMax = ITEMDOUBLESHOT_TIMEWAITMAX;
}


DoubleShotItem::~DoubleShotItem()
{
}
