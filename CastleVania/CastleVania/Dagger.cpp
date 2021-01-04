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
	
	if (!camera->checkObjectInCamera(x, y, (float)getWidth(), (float)getHeight())) // xử lí ra khỏi cam thì kết thúc 
	{
		isFinish = true;
		return;
	}
	/*if (abs(this->x - this->xBackup) >= 100)
	{
		isFinish = true;
		return;
	}*/
	GameObject::Update(dt);
	//Chỉ di chuyển theo phương ngang
	x += dx;
	
}

void Dagger::attack(float x, float y, int direction)
{
	Weapon::attack(x, y + 10, direction);
	this->xBackup = x;
	this->isFinish = false;
	vx = DAGGER_SPEED * this->direction;
	Sound::GetInstance()->Play(eSound::soundDagger);
}

void Dagger::renderIcon(float x, float y)
{
	objectSprite->DrawFrameFlipX(0, x, y);
}