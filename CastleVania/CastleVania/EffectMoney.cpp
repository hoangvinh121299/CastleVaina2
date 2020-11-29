#include "EffectMoney.h"

EffectMoney::EffectMoney(float x, float y, objectType typeOfEffect)
{
	effectTexture = TextureManager::GetInstance()->GetTexture(typeOfEffect);
	effectSprite = new GameSprite(effectTexture, 2000);

	this->x = x;
	this->y = y;
}

void EffectMoney::Update(DWORD dt)
{
	Effect::Update(dt);
	if (effectSprite->getCurrentFrame() == 1) //Nếu là frame cuối cùng là blank thì kết thúc 
	{
		isFinish = true;
	}
}
EffectMoney::~EffectMoney()
{

}