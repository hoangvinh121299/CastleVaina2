#include "UpgradeMorningStar.h"
UpgradeMorningStar::UpgradeMorningStar(float x, float y)
{
	objectTexture = TextureManager::GetInstance()->GetTexture(objectType::UPGRADEMORNINGSTAR);
	objectSprite = new GameSprite(objectTexture, 100);
	this->x = x;
	this->y = y;
	ObjectType = objectType::UPGRADEMORNINGSTAR;
	vy = UPGRADEMORNINGSTAR_GRAVITY;
	timeDisplayMax = UPGRADEMORNINGSTAR_TIMEDISPLAYMAX;
	timeWaitMax = UPGRADEMORNINGSTAR_TIMEWAITMAX;
	timeDisplayed = 0;
	timeWaited = 0;
}

UpgradeMorningStar::~UpgradeMorningStar()
{

}