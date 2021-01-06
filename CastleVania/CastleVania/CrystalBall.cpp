#include "CrystalBall.h"

CrystalBall::CrystalBall(float X, float Y)
{
	objectTexture = TextureManager::GetInstance()->GetTexture(objectType::CRYSTALBALL);
	objectSprite = new GameSprite(objectTexture, 50);

	x = X;
	y = Y;
	health = 1;
	ObjectType = objectType::CRYSTALBALL;

	vy = CRYSTALBALL_GRAVITY;
	timeWaited = 0;
	timeWaitMax = CRYSTALBALL_TIMEWAITMAX;

}

void CrystalBall::Update(DWORD dt, vector<LPGAMEOBJECT>* listObject)
{
	if (isWaitingToDisplay())
	{
		timeWaited += dt;
		return;
	}

	GameObject::Update(dt, listObject);

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
		delete coEvents[i];

}

void CrystalBall::Render(Camera* camera)
{
	if (isWaitingToDisplay())
	{
		return;
	}

	objectSprite->Update(dt);

	D3DXVECTOR2 pos = camera->TransForm(x, y);

	objectSprite->Draw(pos.x, pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		renderBoundingBox(camera);
}

CrystalBall::~CrystalBall()
{
}
