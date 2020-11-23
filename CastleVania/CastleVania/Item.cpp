#include "Item.h"

Item::Item()
{
	timeDisplayed = 0;
	timeWaitMax = 0;
	timeDisplayMax = 0;
	timeWaited = 0;
	isFinish = false;
}

Item::~Item()
{

}

void Item::Update(DWORD dt, vector<LPGAMEOBJECT>* listObject)
{
	if (isWaitingToDisplay())
	{
		timeWaited += dt;
		return;
	}
	timeDisplayed += dt;
	if (timeDisplayed >= timeDisplayMax)
	{
		isFinish = true; //Đã có thể ăn được
		return;
	}
	GameObject::Update(dt);

	vector<LPGAMEOBJECT> listObject_Brick;
	listObject_Brick.clear();
	for (UINT i= 0; i < listObject->size(); i++)
	{
		if (listObject->at(i)->getType() == objectType::BRICK)
		{
			listObject_Brick.push_back(listObject->at(i));
		}
	}
	vector<LPCollisionEvent> coEvents;
	vector<LPCollisionEvent> coEventsResult;
	coEvents.clear();
	calcPotentialCollisions(&listObject_Brick, coEvents); //Lấy danh các va chạm với gạch
	if (coEvents.size() == 0)
	{
		y += dy; //Không có va chạm. item icon tiếp tục rơi
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		filterCollisionEvents(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		y += min_ty * dy + ny * 0.4f;
		if (ny != 0)
		{
			vy = 0;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
	{
		delete coEvents[i];
	}
}

void Item::Render(Camera *camera)
{
	if (isWaitingToDisplay())
	{
		return;
	}
	D3DXVECTOR2 pos = camera->TransForm(x, y);
	objectSprite->Draw(pos.x, pos.y);
	if (IS_DEBUG_RENDER_BBOX)
		renderBoundingBox(camera);
}

bool Item::isWaitingToDisplay()
{
	return timeWaited < timeWaitMax;
}

bool Item::getFinish()
{
	return isFinish;
}

void Item::setFinish(bool temp)
{
	isFinish = temp;
}