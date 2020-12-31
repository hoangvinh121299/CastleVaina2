#include "IntroBat.h" 

IntroBat::IntroBat(float X, float Y, float VX, float VY)
{
	ObjectType = objectType::INTRO_BAT;
	objectTexture = TextureManager::GetInstance()->GetTexture(ObjectType);
	objectSprite = new GameSprite(objectTexture, 70);

	this->x = X;
	this->y = Y;
	this->direction = -1;
	this->health = 1;

	vy = VY;
	vx = VX;
}

IntroBat::~IntroBat()
{
}

void IntroBat::Update(DWORD dt, vector<LPGAMEOBJECT>* listObject)
{
	GameObject::Update(dt); // Update dt, dx, dy
	y += dy;
	x += dx;

	objectSprite->Update(dt);
}

void IntroBat::Render(Camera * camera)
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

