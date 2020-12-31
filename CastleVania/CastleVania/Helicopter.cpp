#include "HeliCopter.h"

HeliCopter::HeliCopter(float X, float Y)
{
	ObjectType = objectType::HELICOPTER;
	objectTexture = TextureManager::GetInstance()->GetTexture(ObjectType);
	objectSprite = new GameSprite(objectTexture, 70);

	this->x = X;
	this->y = Y;
	this->direction = -1;
	this->health = 1;

	vy = -HELICOPTER_SPEED_Y;
	vx = HELICOPTER_SPEED_X * direction;
}

HeliCopter::~HeliCopter()
{
}

void HeliCopter::Update(DWORD dt, vector<LPGAMEOBJECT>* listObject)
{
	GameObject::Update(dt); // Update dt, dx, dy

	y += dy;
	x += dx;

}

void HeliCopter::Render(Camera* camera)
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

