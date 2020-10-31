#include "FireBall.h"

FireBall::FireBall(Camera* camera)
{
	objectTexture = TextureManager::GetInstance()->GetTexture(objectType::FIREBALL);
	objectSprite = new GameSprite(objectTexture, 0);
	isFinish = true;
	this->camera = camera;
}
FireBall::~FireBall()
{

}
void FireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isFinish == true)
		return;
	if(!camera->CHECK_OBJECT_IN_CAMERA(this))
	{
		//Ra khỏi ngoài cam thì biến mất 
		isFinish = true;
		return;
	}

	GameObject::Update(dt);
	x += dx;
	y += dy;
}

void FireBall::attack(float x, float y, int direction)
{
	Weapon::attack(x, y, direction);
}
void FireBall::Render(Camera* camera)
{
	if (isFinish)
		return;

	Weapon::Render(camera);
}