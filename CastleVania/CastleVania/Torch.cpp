#include "Torch.h"

Torch::Torch(float x, float y)
{
	objectTexture = TextureManager::GetInstance()->GetTexture(objectType::TORCH);
	objectSprite = new GameSprite(objectTexture, 100);
	this->x = x;
	this->y = y;
	ObjectType = objectType::TORCH;
	health = 1;
}
Torch::~Torch()
{

}
void Torch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	objectSprite->Update(dt);
}
void Torch::Render(Camera* camera)
{
	if (IS_DEBUG_RENDER_BBOX)
		renderBoundingBox(camera);
	D3DXVECTOR2 pos = camera->TransForm(x, y);
	objectSprite->Draw(pos.x,pos.y);
}