#include "MoneyBag.h"


MoneyBag::MoneyBag(float X, float Y, objectType TypeMoneyBag)
{
	ObjectType = TypeMoneyBag;
	objectTexture = TextureManager::GetInstance()->GetTexture(objectType::BONUS);
	objectSprite = new GameSprite(objectTexture, 0);

	this->x = X;
	this->y = Y;

	vx = 0;

	vy = MONEYBAG_GRAVITY;
	timeDisplayMax = MONEYBAG_TIMEDISPLAYMAX; // set time hiển thị tối đa
	timeDisplayed = 0;
	timeWaited = 0;
	timeWaitMax = MONEYBAG_TIMEWAITMAX;

}

void MoneyBag::Render(Camera* camera)
{
	if (isWaitingToDisplay())
	{
		return;
	}

	switch (ObjectType)
	{
	case objectType::MONEY_BAG_RED:
		objectSprite->SelectFrame(MONEYBAG_ANI_RED);
		break;

	case objectType::MONEY_BAG_WHITE:
		objectSprite->SelectFrame(MONEYBAG_ANI_WHITE);
		break;

	case objectType::MONEY_BAG_PURPLE:
		objectSprite->SelectFrame(MONEYBAG_ANI_PURPLE);
		break;
	}

	D3DXVECTOR2 pos = camera->TransForm(x, y);
	objectSprite->Draw(pos.x, pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		renderBoundingBox(camera);
}

MoneyBag::~MoneyBag()
{
}
