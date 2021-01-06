#include "HolyWater.h"



HolyWater::HolyWater(Camera* camera)
{
	objectTexture = TextureManager::GetInstance()->GetTexture(objectType::HOLYWATER);
	objectSprite = new GameSprite(objectTexture, 100);
	ObjectType = objectType::HOLYWATER;
	_spriteIcon = new GameSprite(TextureManager::GetInstance()->GetTexture(objectType::ITEMHOLYWATER), 200);

	isCollisionBrick = false;
	isFinish = true;
	this->camera = camera;
}

HolyWater::~HolyWater()
{

}

void HolyWater::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!camera->checkObjectInCamera(x, y, (float)objectTexture->GetFrameWidth(), (float)objectTexture->GetFrameHeight()))
		isFinish = true;

	if (isFinish)
		return;

	GameObject::Update(dt); //update dt dx d
	if (!isCollisionBrick)
		vy += HOLYWATER_GRAVITY * dt;

	if (!isCollisionBrick) // chưa chạm đất mới xét va chạm
	{
		vector<LPGAMEOBJECT> listObject_Brick;
		listObject_Brick.clear();
		for (UINT i = 0; i < coObjects->size(); i++)
			if (coObjects->at(i)->getType() == objectType::BRICK)
				listObject_Brick.push_back(coObjects->at(i));

		vector<LPCollisionEvent> coEvents;
		vector<LPCollisionEvent> coEventsResult;
		coEvents.clear();
		calcPotentialCollisions(&listObject_Brick, coEvents); // Lấy danh sách các va chạm 
		if (coEvents.size() == 0)
		{
			y += dy;
			x += dx;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			filterCollisionEvents(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.4f;
			if (nx != 0 || ny != 0)
			{
				vy = 0;
				vx = 0;
				isCollisionBrick = true;
				//Sound::GetInstance()->Play(eSound::soundHolyWater); // chạm đất thì mới playsound
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++)
			delete coEvents[i];
	}

}

void HolyWater::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - 5;
	top = y;
	right = x + objectTexture->GetFrameWidth() + 5;
	bottom = y + objectTexture->GetFrameHeight();
	if (objectSprite->getCurrentFrame() == 0) // frame đầu
	{
		left += 5;
		top += 5;
		right -= 5;
		bottom -= 0;
	}
}

void HolyWater::UpdatePositionFitSimon()
{
	y += 15;
	if (this->direction == -1)
		x += 30;

}

void HolyWater::Attack(float X, float Y, int Direction)
{
	if (isFinish == false)
		return;
	Weapon::attack(X, Y, Direction);
	UpdatePositionFitSimon();
	vx = HOLLYWATER_SPEED_X * Direction;
	vy = -HOLLYWATER_SPEED_Y;
	isCollisionBrick = false;
	objectSprite->SelectFrame(0);
	CountLoop = 0;
}

void HolyWater::RenderIcon(float X, float Y)
{
	_spriteIcon->Draw(X, Y);
}


void HolyWater::Render(Camera* camera)
{
	if (isFinish == true)
		return;

	if (isCollisionBrick) // chạm đất r thì mới update ani
		objectSprite->Update(dt);

	D3DXVECTOR2 pos = camera->TransForm(x, y);
	if (direction == -1)
		objectSprite->Draw(pos.x, pos.y);
	else
		objectSprite->DrawFlipX(pos.x, pos.y);

	if (IS_DEBUG_RENDER_BBOX)
	{
		renderBoundingBox(camera);
	}

	if (objectSprite->getCurrentFrame() == 3) // là frame cuối cùng thì kết thúc
	{
		CountLoop++;
		if (CountLoop >= 2) // lặp đúng 2 lần thì dừng
			isFinish = true;
		else
			objectSprite->SelectFrame(1);
	}
}
