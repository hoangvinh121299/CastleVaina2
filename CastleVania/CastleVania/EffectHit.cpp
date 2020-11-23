#include "EffectHit.h"

EffectHit::EffectHit(float x, float y)
{
	this -> x = x;
	this->y = y;
	effectTexture = TextureManager::GetInstance()->GetTexture(objectType::HIT);
	effectSprite = new GameSprite(effectTexture, 250);
}
EffectHit::~EffectHit()
{

}
void EffectHit::Update(DWORD dt)
{
	Effect::Update(dt);
	if (effectSprite->getCurrentFrame() == 1)// Nếu là frame cuối cùng của Effect
		isFinish = true;
} 