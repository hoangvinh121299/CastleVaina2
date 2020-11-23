#include "EffectFire.h"

EffectFire::EffectFire(float x, float y, int countLoop)
{
	this->x = x;
	this->y = y;
	this->countLoop = countLoop;
	effectTexture = TextureManager::GetInstance()->GetTexture(objectType::FIRE);
	effectSprite = new GameSprite(effectTexture, 150);
}
void EffectFire::Update(DWORD dt)
{
	Effect::Update(dt);

	if (effectSprite->getCurrentFrame() == 3)// Nếu là frame cuối của Ani lửa
	{
		countLoop--;//Giảm số lần lặp
		if (countLoop == 0)
		{
			isFinish = true; //Lặp xong thì finish
		}
		else
		{
			effectSprite->timeAccumulated = effectSprite->timeAnimation;
		}
	}
}
EffectFire::~EffectFire()
{

}