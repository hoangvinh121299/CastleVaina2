#include "Effect.h"

Effect::Effect()
{
	isFinish = 0;
}
Effect::~Effect()
{
	SAFE_DELETE(effectSprite);
}
void Effect::Render(Camera* camera)
{
	D3DXVECTOR2 pos = camera->TransForm(x, y);
	effectSprite->Draw(pos.x, pos.y);
}
void Effect::Update(DWORD dt)
{
	effectSprite->Update(dt);
}
bool Effect::getFinish()
{
	return isFinish;
}
void Effect::setFinish(int temp)
{
	isFinish = temp;
}