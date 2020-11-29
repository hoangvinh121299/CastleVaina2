#include "Dagger.h"


Dagger::Dagger(Camera* camera)
{
	ObjectType = objectType::DAGGER;
	objectTexture = TextureManager::GetInstance()->GetTexture(ObjectType);
	objectSprite = new GameSprite(objectTexture, 0);
	this->camera = camera;
}

Dagger::~Dagger()
{

}

void Dagger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	//Chỉ di chuyển theo phương ngang
	x += dx;
}

void Dagger::attack(float x, float y, int direction)
{
	Weapon::attack(x, y + 10, direction);
	vx = DAGGER_SPEED * this->direction;
}

void Dagger::renderIcon(float x, float y)
{
	objectSprite->DrawFrameFlipX(0, x, y);
}