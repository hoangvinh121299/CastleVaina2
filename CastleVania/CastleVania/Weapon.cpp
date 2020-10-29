#include "Weapon.h"
Weapon::Weapon()
{
	isFinish = 1;
}
Weapon::~Weapon()
{

}
int Weapon::getDirection()
{
	return this->direction;
}
void Weapon::setDirection(int Direction)
{
	this->direction = Direction;
}
void Weapon::attack(float x, float y, int Direction)
{
	this->x = x;
	this->y = y;

	this->direction = Direction;
	isFinish = false;
	lastTimeAttack = GetTickCount(); // Lưu lại thời gian bắt đầu attack với vũ khí 
}

void Weapon::Render(Camera* camera)
{
	if (isFinish)
		return;
	D3DXVECTOR2 pos = camera->TransForm(x, y);

	if (direction == -1)
		objectSprite->Draw(pos.x, pos.y);
	else
		objectSprite->DrawFlipX(pos.x, pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		renderBoundingBox(camera);
}

void Weapon::updatePositionWithSimon()
{

}

bool Weapon::isColission(GameObject* obj)
{
	if (isFinish == true)
		return false;


	if (obj->getHealth() <= 0)
		return false;

	//Trả về kết quả của hàm kiểm tra va chạm giữa hai object
	return isColisionObjectwithObject(obj);
}

bool Weapon::getFinish()
{
	return isFinish;
}

void Weapon::setFinish(bool temp)
{
	this->isFinish = temp;
}

DWORD Weapon::getLastTimeAttack()
{
	return this->lastTimeAttack;
}