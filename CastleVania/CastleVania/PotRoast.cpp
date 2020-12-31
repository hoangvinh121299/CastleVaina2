#include "PotRoast.h"



PotRoast::PotRoast(float X, float Y)
{
	ObjectType = objectType::POTROAST;
	objectTexture = TextureManager::GetInstance()->GetTexture(ObjectType);
	objectSprite = new GameSprite(objectTexture, 100);

	x = X;
	y = Y;
	health = 1;

	vy = POTROAST_GRAVITY;
	timeDisplayMax = POTROAST_TIMEDISPLAYMAX; // set time hiển thị tối đa
	timeDisplayed = 0;
	timeWaited = 0;
	timeWaitMax = POTROAST_TIMEWAITMAX;

}

PotRoast::~PotRoast()
{
}
