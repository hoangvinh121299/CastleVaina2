#include "Panther.h"

Panther::Panther(float x, float y, int direction, float autoGoX_Distance,Simon *simon)
{
	ObjectType = objectType::PANTHER;

	vx = vy = 0;
	this->direction = direction;

	this->x = x;
	this->y = y;
	autoGoXBackup = x;
	autoGoXDistance = autoGoX_Distance;
	objectTexture = TextureManager::GetInstance()->GetTexture(objectType::PANTHER);
	objectSprite = new GameSprite(objectTexture,120);
	isSitting = 1;
	isRunning = 0;
	isJumping = 0;
	isStart = 0;
	isAutoGoX = 0;
	this->simon = simon;
}
Panther::~Panther()
{

}

void Panther::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	/*if (vx < 0 && x < 0)
	{
		
		this->direction = 1;
		x = 0;
		vx = PANTHER_SPEED_RUNNING;
		jump();
	}
	if (vx > 0 && x > 500)
	{
		this->direction = -1;
		x = 500;
		vx = -PANTHER_SPEED_RUNNING;
		jump();
	}*/
	if (isJumping)
	{
		dx = vx * dt;
		dy = vy * dt;
		vy += PANTHER_GRAVITY_JUMPING * dt;
	}
	else
		vy += PANTHER_GRAVITY;
	float distanceLimit; //Khoảng cách để panther bắt đầu tấn công simon
	if (direction == 1)
		distanceLimit = 85;
	else
		distanceLimit = 177;

	//Kích hoạt Panther khi Simon đi ngang qua
	if (isStart == 0 && abs(simon->getX() - (this->x + objectTexture->GetFrameWidth())) <= distanceLimit)
	{
		isSitting = false;
		isRunning = true;
		run();
		isAutoGoX = 1;
		isStart = 1;
		
	}

	if (isSitting)
	{
		objectSprite->SelectFrame(PANTHER_ANI_SITTING);
	}
	else
	{
		if(isRunning)
		{
			if (!isJumping)
			{
				if (PANTHER_ANI_RUNNIGN_BEGIN <= objectSprite->getCurrentFrame() && objectSprite->getCurrentFrame() < PANTHER_ANI_RUNNING_END)
				{
					objectSprite->Update(dt);
				}
				else
				{
					objectSprite->SelectFrame(PANTHER_ANI_RUNNIGN_BEGIN);
				}
			}
		}
	}
	//Xét va chạm với nền
	vector<LPCollisionEvent> coEvents;
	vector<LPCollisionEvent> coEventsResult;
	coEvents.clear();
	vector<LPGAMEOBJECT> list_Brick;
	list_Brick.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i)->getType() == objectType::BRICK)
			list_Brick.push_back(coObjects->at(i));
	}

	calcPotentialCollisions(&list_Brick, coEvents);
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		filterCollisionEvents(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += dx;
		if (ny == -1)
			y += min_ty * dy + ny * 0.4f;
		else
			y += dy;

		if (ny == -1)
		{
			vy = 0;
			if (isJumping)
			{
				isJumping = false; // kết thúc nhảy
				if (x < simon->getX()) // simon ở bên phải
				{
					direction = 1; // đổi hướng panther qua phải 
				}
				else
				{
					direction = -1; // đổi hướng panther qua trái
				}
				run();
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
#pragma endregion
	if (isAutoGoX)
	{
		if (abs(x - autoGoXBackup) >= autoGoXDistance)
		{
			x = x - (abs(x - autoGoXBackup) - autoGoXDistance);
			isAutoGoX = false;
			vx = 0;

			jump(); // Sau khi chạy xong thì nhảy

			DebugOut(L"[PANTHER] end auto go X\n");
		}
	}

}
void Panther::Render(Camera* camera)
{
	if (health <= 0)
		return;
	D3DXVECTOR2 pos = camera->TransForm(x, y);
	if (direction == -1)
		objectSprite->Draw(pos.x, pos.y);
	else
		objectSprite->DrawFlipX(pos.x, pos.y);
	if (IS_DEBUG_RENDER_BBOX)
		renderBoundingBox(camera);
}
void Panther::jump()
{
	if (isJumping == true)
		return;
	vy = -PANTHER_VYJUMP;
	vx = PANTHER_VXJUMP * direction;
	isJumping = true;
}

void Panther::run()
{
	vx = PANTHER_SPEED_RUNNING * direction;
	isRunning = true;
}

bool Panther::getStart()
{
	return isStart;
}