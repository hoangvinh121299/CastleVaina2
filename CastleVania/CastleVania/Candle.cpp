#include "Candle.h"


Candle::~Candle()
{
}


Candle::Candle(float X, float Y)
{
	objectTexture = TextureManager::GetInstance()->GetTexture(objectType::CANDLE);
	objectSprite = new GameSprite(objectTexture, 100);
	this->x = X;
	this->y = Y;
	ObjectType = objectType::CANDLE;
	health= 1;
}



void Candle::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - 5;
	top = y - 5;
	right = x + objectTexture->GetFrameWidth() + 5;
	bottom = y + objectTexture->GetFrameHeight() + 5; //Mở rộng BBOX cho dễ đánh trúng

}

void Candle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	objectSprite->Update(dt); // update animation
}

void Candle::Render(Camera* camera)
{
	if (IS_DEBUG_RENDER_BBOX)
		renderBoundingBox(camera);

	D3DXVECTOR2 pos = camera->TransForm(x, y);
	objectSprite->Draw(pos.x, pos.y);
}
