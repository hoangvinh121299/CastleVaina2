#include "Brick.h"

Brick::Brick(float X, float Y, int W, int H, int Model)
{
	model = Model;
	switch (Model)
	{
	case BRICK_MODEL_1:
		objectTexture = TextureManager::GetInstance()->GetTexture(eType::TEX_BRICK_MODEL_1);
		break;
	case BRICK_MODEL_2:
		objectTexture = TextureManager::GetInstance()->GetTexture(eType::TEX_BRICK_MODEL_2);
		break;
	case BRICK_MODEL_3:
		objectTexture = TextureManager::GetInstance()->GetTexture(eType::TEX_BRICK_MODEL_3);
		break;
	case BRICK_MODEL_TRANSPARENT:
		objectTexture = TextureManager::GetInstance()->GetTexture(eType::TEX_BRICK_TRANSPARENT);
		break;
	case BRICK_MODEL_3_3_32:
		objectTexture = TextureManager::GetInstance()->GetTexture(eType::TEX_BRICK_MODEL_3_3_32);
		break;
	case BRICK_MODEL_3_4_32:
		objectTexture = TextureManager::GetInstance()->GetTexture(eType::TEX_BRICK_MODEL_3_4_32);
		break;
	default:
		DebugOut(L"[BRICK]: Get Texture failed\n");
	}
	objectType = eType::BRICK;
	objectSprite = new GameSprite(objectTexture, 1000);
	this->x = X;
	this->y = Y;
	this->width = W;
	this->height = H;
}

void Brick::Render(Camera * camera)
{
	if (IS_DEBUG_RENDER_BBOX)
	{
		renderBoundingBox(camera);
	}
	if (model == BRICK_MODEL_TRANSPARENT)
		return;
	D3DXVECTOR2 pos = camera->TransForm(x, y);
	for (int i = 0; i < (int)ceil(width / objectTexture->GetFrameWidth()); i++)
	{
		for (int j = 0; j < (int)ceil(height / objectTexture->GetFrameHeight()); j++)
			objectSprite->Draw(pos.x + i * objectTexture->GetFrameWidth(), pos.y + j * objectTexture->GetFrameHeight());
	}
}

void Brick::getBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + (float)ceil(width / objectTexture->GetFrameWidth())*objectTexture->GetFrameWidth();
	b = y + (float)ceil(height / objectTexture->GetFrameHeight())*objectTexture->GetFrameHeight();
}

int Brick::getModel()
{
	return model;
}
Brick::~Brick()
{

}