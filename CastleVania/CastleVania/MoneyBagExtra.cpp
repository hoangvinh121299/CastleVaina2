#include "MoneyBagExtra.h"

MoneyBagExtra::MoneyBagExtra(float x, float y)
{
	ObjectType = objectType::BONUS;
	objectTexture = TextureManager::GetInstance()->GetTexture(ObjectType);
	objectSprite = new GameSprite(objectTexture, 20);

	this->x = x;
	this->y = y;

	vx = 0;
	vy = 0;

	vy = MONEY_EXTRA_GRAVITY;

	timeDisplayMax = MONEY_EXTRA_TIMEDISPLAYMAX;
	timeDisplayed = 0;
	timeWaitMax = MONEY_EXTRA_TIMEWAITMAX;
	timeWaited = 0;
}
MoneyBagExtra::~MoneyBagExtra()
{

}

void MoneyBagExtra::Render(Camera* camera)
{
	Item::Render(camera);
	objectSprite->Update(dt);
}