#include "Bat.h"


Bat::Bat(float x, float y, int direction)
{
	
	objectTexture = TextureManager::GetInstance()->GetTexture(objectType::BAT);
	objectSprite = new GameSprite(objectTexture, 70);
	ObjectType = objectType::BAT;
	this->x = x;
	this->y = y;
	this->direction = direction;
	this->yBackup = y;

	vy = BAT_SPEED_Y;
	vx = BAT_SPEED_X * direction;
}

Bat::~Bat()
{

}

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* listObject)
{
	if (y - yBackup >= LIMITY)
	{
		vy = -BAT_SPEED_Y;
	}
	else
	{
		if (y - yBackup <= -LIMITY)
		{
			vy = BAT_SPEED_Y;
		}
	}
	GameObject::Update(dt);

	y += dy;
	x += dx;
	if (vx < 0 && x < 0)
	{
		this->direction = 1;
		x = 0;
		vx = BAT_SPEED_X;
	}
	if (vx > 0 && x > 500)
	{
		this->direction = -1;
		x = 500;
		vx = -BAT_SPEED_X;
	}
	objectSprite->Update(dt);
	if (objectSprite->getCurrentFrame() == 0)
	{
		objectSprite->Update(dt);
	}
}

void Bat::Render(Camera* camera)
{
	D3DXVECTOR2 pos = camera->TransForm(x, y);

	if (direction == -1)
		objectSprite->Draw(pos.x, pos.y);
	else
		objectSprite->DrawFlipX(pos.x, pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		renderBoundingBox(camera);
}
