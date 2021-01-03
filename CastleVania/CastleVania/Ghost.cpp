#include "Ghost.h"


Ghost::Ghost(float x, float y, int direction)
{
	this->x = x;
	this->y = y;
	this->direction = direction;

	objectTexture = TextureManager::GetInstance()->GetTexture(objectType::GHOST);
	objectSprite = new GameSprite(objectTexture, 100);

	ObjectType = objectType::GHOST;
	this->health = 1;
	vx = GHOST_SPEED_X * this->direction;
}

Ghost::~Ghost()
{

}
void Ghost::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	vy += GHOST_GRAVITY * dt;

	vector<LPGAMEOBJECT> listObject_brick;
	listObject_brick.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i)->getType() == objectType::BRICK)
		{
			listObject_brick.push_back(coObjects->at(i));
		}
	}

	vector<LPCollisionEvent> coEvents;
	vector<LPCollisionEvent> coEventResults;

	coEvents.clear();

	calcPotentialCollisions(&listObject_brick, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		/*if (vx < 0 && x < 0)
		{
			this->direction = 1;
			x = 0;
			vx = GHOST_SPEED_X;
		}
		if (vx > 0 && x > 500)
		{
			this->direction = -1;
			x = 500;
			vx = -GHOST_SPEED_X;
		}*/
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		filterCollisionEvents(coEvents, coEventResults, min_tx, min_ty, nx, ny);
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
		if (nx != 0)
		{
			vx *= -1;
			direction *= -1;
		}

		if (ny != 0)
		{
			vy = 0;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
	{
		delete coEvents[i];
	}
	objectSprite->Update(dt);
}

void Ghost::Render(Camera* camera)
{
	if (health <= 0)
		return;
	D3DXVECTOR2 pos = camera->TransForm(x, y);

	if (direction == -1)
		objectSprite->Draw(pos.x, pos.y);
	else
		objectSprite->DrawFlipX(pos.x, pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		renderBoundingBox(camera);
}
