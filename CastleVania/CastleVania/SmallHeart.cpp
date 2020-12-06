#include "SmallHeart.h"




SmallHeart::SmallHeart(float X, float Y)
{
	objectTexture = TextureManager::GetInstance()->GetTexture(objectType::SMALLHEART);

	objectSprite = new GameSprite(objectTexture, 100);
	ObjectType = objectType::SMALLHEART;

	this->x = X;
	this->y = Y;
	this->xStart = X;

	timeDisplayMax = SMALLHEART_TIMEDISPLAYMAX; // set time hiển thị tối đa
	timeDisplayed = 0;
	timeWaited = 0;
	timeWaitMax = SMALLHEART_TIMEWAITMAX;


	vy = SMALLHEART_GRAVITY;
	vx = SMALLHEART_SPEED_X;
}


void SmallHeart::Update(DWORD dt, vector<LPGAMEOBJECT>* listObject)
{
	//Khi thời gian chờ nhỏ hơn thời gian chờ max
	if (timeWaited < timeWaitMax)
	{
		timeWaited += dt;
		return;
	}

	timeDisplayed += dt;
	if (timeDisplayed >= timeDisplayMax)
	{
		isFinish = true;
		return;
	}

	//Cho item rơi theo hình xoáy ốc
	// vượt quá biên độ trục x cho phép thì đổi chiều vx
	if (x - xStart >= LIMIT_X)
	{
		vx = -SMALLHEART_SPEED_X;
	}
	else
		if (x - xStart <= -LIMIT_X)
		{
			vx = SMALLHEART_SPEED_X;
		}


	GameObject::Update(dt, listObject); // Update dt, dx, dy

	//Item va chạm với nền 
	vector<LPGAMEOBJECT> listObject_Brick;
	listObject_Brick.clear();
	for (UINT i = 0; i < listObject->size(); i++)
		if (listObject->at(i)->getType() == objectType::BRICK)
			listObject_Brick.push_back(listObject->at(i));

	vector<LPCollisionEvent> coEvents;
	vector<LPCollisionEvent> coEventsResult;

	coEvents.clear();

	calcPotentialCollisions(&listObject_Brick, coEvents); // Lấy danh sách các va chạm

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		y += dy;
		x += dx;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		filterCollisionEvents(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		y += min_ty * dy + ny * 0.4f;

		if (ny != 0)
		{
			vy = 0;
			vx = 0; // cho dừng di chuyển theo biên độ x
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];

}

SmallHeart::~SmallHeart()
{
}
