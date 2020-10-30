#include "Panther.h"

Panther::Panther(float x, float y, int direction,Simon *simon)
{
	ObjectType = objectType::PANTHER;

	vx = vy = 0;
	this->direction = direction;

	this->x = x;
	this->y = y;

	objectTexture = TextureManager::GetInstance()->GetTexture(objectType::PANTHER);
	objectSprite = new GameSprite(objectTexture,120);
	isSitting = 1;
	isRunning = 0;
	isJumping = 0;
	isStart = 0;
	this->simon = simon;
}
Panther::~Panther()
{

}

void Panther::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	x += dx;
	y += dy;
	if (vx < 0 && x < 0)
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
	}
	if (isJumping)
	{
		dx = vx * dt;
		dy = vy * dt;
		vy += PANTHER_GRAVITY_JUMPING * dt;
	}
	else
		vy += PANTHER_GRAVITY;
	if (y>330)
	{
		y = 330;
		vy = 0;
		isJumping = false;
		run();

	}
	float distanceLimit; //Khoảng cách để panther bắt đầu tấn công simon
	if (direction == 1)
		distanceLimit = 85;
	else
		distanceLimit = 177;
	if (isStart == 0 && abs(simon->getX() - (this->x + objectTexture->GetFrameWidth())) <= distanceLimit)
	{
		isSitting = false;
		isRunning = true;
		run();

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
	
}
void Panther::Render(Camera* camera)
{
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
	vx = PANTHER_VXJUMP;
	isJumping = true;
}

void Panther::run()
{
	vx = PANTHER_SPEED_RUNNING * direction;
	isRunning = true;
}