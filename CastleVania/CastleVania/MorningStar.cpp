#include "MorningStar.h"

MorningStar::MorningStar()
{
	ObjectType = objectType::MORNINGSTAR;
	objectTexture = TextureManager::GetInstance()->GetTexture(ObjectType);
	objectSprite = new GameSprite(objectTexture, MORNINGSTAR_TIME_DELAY_ANI);
	this->level = 0;
}

MorningStar::~MorningStar()
{

}

void MorningStar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	//Update to check Collision
	isFinish = (objectSprite->getCurrentFrame() == 3 && level == 0);

	int starFrame = MORNINGSTAR_ANI_LEVEL0_START + 4 * level;
	int endFrame = MORNINGSTAR_ANI_LEVEL0_END + 4 * level;

	if (starFrame <= objectSprite->getCurrentFrame() && objectSprite->getCurrentFrame() < endFrame)
		objectSprite->Update(dt);
	else
	{
		objectSprite->SelectFrame(starFrame);
	}
}
void MorningStar::Render(Camera* camera)
{
	D3DXVECTOR2 pos = camera->TransForm(x, y);
	if (direction == -1)
		objectSprite->Draw(pos.x, pos.y);
	else
		objectSprite->DrawFlipX(pos.x, pos.y);

	if (IS_DEBUG_RENDER_BBOX)
	{
		if (/*level == 0 && objectSprite->getCurrentFrame() == MORNINGSTAR_ANI_LEVEL0_START || */objectSprite->getCurrentFrame() == MORNINGSTAR_ANI_LEVEL0_START+1)
			return;
		/*if (level == 0 && objectSprite->getCurrentFrame() != MORNINGSTAR_ANI_LEVEL0_START)
			return;*/

		renderBoundingBox(camera);
	}
}
void MorningStar::attack(float x, float y, int direction)
{
	Weapon::attack(x, y, direction);

	updatePositionWithSimon();

	//Xử lý ani của MorningStar
	objectSprite->SelectFrame(MORNINGSTAR_ANI_LEVEL0_START);
	objectSprite->ResetTime();
	
}

void MorningStar::updatePositionWithSimon()
{
	if (direction == -1)
	{
		this->x = x - 75;
		this->y =y- 2;
	}
	else
	{
		this->x = x - 25;
		this->y =y- 2;
	}
}

void MorningStar::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (objectSprite->getCurrentFrame() == MORNINGSTAR_ANI_LEVEL0_END) {
		if (direction == 1)
		{
			left = x + 78;
			top = y + 15;
			right = x + objectTexture->GetFrameWidth() - 30;
			bottom = y + objectTexture->GetFrameHeight() - 30;
		}
		else
		{
			left = x + 30;
			top = y + 15;
			right = x + objectTexture->GetFrameWidth() - 80;
			bottom = y + objectTexture->GetFrameHeight() - 30;
		}
	}
	else 
	{
		if (objectSprite->getCurrentFrame() == MORNINGSTAR_ANI_LEVEL0_START)
		{
			if (direction == 1)
			{
				left = x + 5;
				top = y + 15;
				right = x + objectTexture->GetFrameWidth() - 135;
				bottom = y + objectTexture->GetFrameHeight() - 5;
			}
			else
			{
				left = x + 160;
				top = y + 15;
				right = x + objectTexture->GetFrameWidth() - 25;
				bottom = y + objectTexture->GetFrameHeight() - 5;
			}
		}
	}
}

void MorningStar::renderIcon(float x, float y)
{

}
int MorningStar::getLevel()
{
	return this->level;
}

bool MorningStar::isColission(GameObject* obj)
{
	/*if (objectSprite->getCurrentFrame() == MORNINGSTAR_ANI_LEVEL0_START + 1)
		return false; */// frame đầu và frame chuẩn bị đánh thì ko xét va chạm
	return Weapon::isColission(obj);
}