#include "Fishmen.h"

Fishmen::Fishmen(float x, float y, int direction, Simon* simon, vector<Weapon*>* listWeapon, Camera* camera)
{
	ObjectType = objectType::FISHMEN;
	objectTexture = TextureManager::GetInstance()->GetTexture(objectType::FISHMEN);
	objectSprite = new GameSprite(objectTexture, 200);

	this->x = x;
	this->y = y;
	this->direction = direction;
	vx = 0;
	vy = -FISHMEN_SPEED_Y_UP;

	y_start = this->y;
	x_start = this->x;
	xAccumulationtoAttack = 0;

	objectSprite->SelectFrame(FISHMEN_ANI_JUMP);

	isRunning = 1;
	isAttacking = 0;

	this->simon = simon;
	this->listWeaponOfEnemy = listWeapon;
	this->camera = camera;
}

Fishmen::~Fishmen()
{

}
void Fishmen::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x + 5;
	top = y + 15;
	right = x + objectTexture->GetFrameWidth() - 5;
	bottom = y + objectTexture->GetFrameHeight();
}
void Fishmen::Update(DWORD dt, vector<LPGAMEOBJECT>* listObject)
{
	if (y <= y_start - FISHMEN_Y_JUMP);
	{
		vy = FISHMEN_SPEED_Y_DOWN;
	}

	//Đi đủ khoảng cách tự động đổi hướng 
	if (abs(x - x_start) >= FISHMEN_X_LIMIT) 
	{
		if ((direction == -1) && !(simon->getX() < x) && (direction == 1) || !(x < simon->getX()))
		{
			direction *= -1; // Đổi hướng 
			x_start = x;
		}
	}

	//Đi đủ khoảng cách tự động tấn công
	if (xAccumulationtoAttack >= FISHMEN_X_ATTACK_LIMIT)
	{
		xAccumulationtoAttack = 0;
		attack();
	}

	x_before = x;
	
	if (isRunning)
	{
		vx = direction * FISHMEN_SPEED_X;
		vy += FISHMEN_GRAVITY;
	}
	GameObject::Update(dt);
	if (vx < 0 && x < 0)
	{

		this->direction = 1;
		x = 0;
		vx = FISHMEN_SPEED_X;
	}
	if (vx > 0 && x > 500)
	{
		this->direction = -1;
		x = 500;
		vx = -FISHMEN_SPEED_X;
	}
	if (!isAttacking)
	{
		x += dx;
	}
	/*y += dy;*/
	if(isAttacking)
	{
		DWORD now = GetTickCount();
		//Thời gian chờ chưa đủ thì chưa attack
		if (now - timeAttack >= FISHMEN_TIME_DELAY_AFTER_ATTACK)
		{
			isAttacking = false;
		}
	}

	x_after = x;
	xAccumulationtoAttack += abs(x_after - x_before);
	
	//Update ANIMATION
	if (isAttacking)
	{
		objectSprite->SelectFrame(FISHMEN_ANI_ATTACK);
	}
	else
	{
		if (isRunning)
		{
			int index = objectSprite->getCurrentFrame();
			if (FISHMEN_ANI_WALK_BEGIN <= index && index <= FISHMEN_ANI_WALK_END)
			{
				objectSprite->Update(dt);
			}
			if (objectSprite->getCurrentFrame() == FISHMEN_ANI_ATTACK)
			{
				objectSprite->SelectFrame(FISHMEN_ANI_WALK_BEGIN);
			}
		}
	}
	//Xử lý va chạm với gạch
	vector<LPCollisionEvent> coEvents;
	vector<LPCollisionEvent> coEventsResult;
	coEvents.clear();
	vector<LPGAMEOBJECT> list_Brick;
	list_Brick.clear();

	for (UINT i = 0; i <listObject ->size(); i++)
		if (listObject->at(i)->getType() == objectType::BRICK)
			list_Brick.push_back(listObject->at(i));

	calcPotentialCollisions(&list_Brick, coEvents);

	float min_tx, min_ty, nx = 0, ny;
	filterCollisionEvents(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	if (ny == -1)
	{
		vy = 0;
		y += min_ty * dy + ny * 0.4f;
		isRunning = true;
	}
	else
	{
		y += dy;
	}

}
void Fishmen::Render(Camera* camera)
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

void Fishmen::attack()
{
	if (health <= 0)
		return;
	if (isAttacking)
		return;

	if (fireball == NULL)
	{
		fireball = new FireBall(camera);
		listWeaponOfEnemy->push_back(fireball);
	}

	if (fireball->getFinish() == false)
	{
		return;
	}

	isAttacking = true;
	timeAttack = GetTickCount();

	fireball->setSpeed(FIREBALL_SPEED * direction, 0);
	fireball->attack(x + 10, y + 3, direction);
}