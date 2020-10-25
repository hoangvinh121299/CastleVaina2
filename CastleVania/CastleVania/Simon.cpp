#include "Simon.h"
//Khởi tạo đối tuọng simon
Simon::Simon(Camera *camera)
{
	objectTexture = TextureManager::GetInstance()->GetTexture(eType::SIMON);
	objectSprite = new GameSprite(objectTexture, 250);
	_sprite_death = new GameSprite(TextureManager::GetInstance()->GetTexture(eType::SIMON_DEATH),250);
	objectType = eType::SIMON;
	this->camera = camera;
	Init();
}
//Khi Simon chết
Simon::~Simon()
{
	SAFE_DELETE(_sprite_death);
}
void Simon::getBoundingBox(float &left, float &top, float &right, float &bottom)
{
	//Bounding Box lúc Simon ngồi
	if (isSitting == true)
	{
		left = x + 15;
		top = y - 1;
		right = x + SIMON__BBOX_WIDTH - 15;
		bottom = y + SIMON_BBOX_HEIGHT;
	}
	else
	{
		//Các trường hợp còn lại
		left = x + 15;
		top = y - 1;
		right = x + SIMON__BBOX_WIDTH - 15;
		bottom = y + SIMON_BBOX_HEIGHT;
	}
	//Lúc đang nhảy
	if (isJumping == true)
	{
		bottom = y + SIMON_BBOX_JUMPING_HEIGHT;
	}
}
//PHƯƠNG THỨC UPDATE CHO SIMON
void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	//Các phương thức giới hạn camera trong tầm nhân vật
	if (x < camera->getBoundaryLeft() - 16)
		x = camera->getBoundaryLeft() - 16;
	if (x + SIMON__BBOX_WIDTH > camera->getBoundaryRight() + SCREEN_WIDTH)
		x += (float)(camera->getBoundaryRight() + SCREEN_WIDTH - SIMON__BBOX_WIDTH);

#pragma region Update về Sprite
	int index = objectSprite->getCurrentFrame();
#pragma region Trên cầu thang
	if (isOnStair)
	{
#pragma region Tấn công
		if (isAttacking == true)
		{
#pragma region Xử lý ANI đánh trên cầu thang lúc đi lên
			if (directionY == -1)
			{
				if (index < SIMON_ANI_UPSTAIR_BEGIN) //Nếu ANI sai
				{
					objectSprite->SelectFrame(SIMON_ANI_UPSTAIR_ATTACKING_BEGIN);
					objectSprite->timeAccumulated = dt;
				}
				else
				{
					//ANI bình thường
					objectSprite->timeAccumulated += dt;
					if (objectSprite->timeAccumulated >= SIMON_TIME_COOLDOWN_ATTACKING)
					{
						objectSprite->timeAccumulated -= SIMON_TIME_COOLDOWN_ATTACKING;
						objectSprite->SelectFrame(objectSprite->getCurrentFrame() + 1);
					}
					if (objectSprite->getCurrentFrame() > SIMON_ANI_UPSTAIR_ATTACKING_END)// ĐÃ đi vượt qua frame cuối của ani đánh cầu thang
					{
						isAttacking = false;
						objectSprite->SelectFrame(SIMON_STAIR_STANDING_UP);
					}
				}

			}
#pragma endregion
#pragma region ANI lúc đi xướng cầu thang đánh
			else
			{
				if (index < SIMON_ANI_DOWNSTAIR_BEGIN) //Nếu ANI sai
				{
					objectSprite->SelectFrame(SIMON_ANI_DOWNSTAIR_ATTACKING_BEGIN);
					objectSprite->timeAccumulated = dt;
				}
				else
				{
					//ANI bình thường
					objectSprite->timeAccumulated += dt;
					if (objectSprite->timeAccumulated >= SIMON_TIME_COOLDOWN_ATTACKING)
					{
						objectSprite->timeAccumulated -= SIMON_TIME_COOLDOWN_ATTACKING;
						objectSprite->SelectFrame(objectSprite->getCurrentFrame() + 1);
					}
					if (objectSprite->getCurrentFrame() > SIMON_ANI_DOWNSTAIR_ATTACKING_END)// ĐÃ đi vượt qua frame cuối của ani đánh cầu thang
					{
						isAttacking = false;
						objectSprite->SelectFrame(SIMON_STAIR_STANDING_DOWN);
					}
				}
			}
#pragma endregion
		}

#pragma endregion
#pragma region Đi bình thường
		else
		{
			if (isWalking == true)
			{
				if (isProccessingOnStair == 1) // Bước chân lên cầu thang set frame =12
					if (vy < 0)//Đi lên
						objectSprite->SelectFrame(SIMON_ANI_STAIR_GO_UP_BEGIN);
					else
						objectSprite->SelectFrame(SIMON_ANI_STAIR_GO_DOWN_BEGIN);
			}
		}
	}
#pragma endregion
#pragma endregion
#pragma region Các trường hợp khác
	else
	{
#pragma region Bị tổn thương
		if (isHurting == true)
		{
			objectSprite->SelectFrame(SIMON_ANI_HURTING);
		}
#pragma endregion
		else
		{
#pragma region Ngồi
			if (isSitting == true)
			{
				//Ani ngồi đánh
				if (isAttacking == true)
				{
					if (index < SIMON_ANI_SITTING_ATTACKING_BEGIN)//Sai ani
					{
						objectSprite->SelectFrame(SIMON_ANI_SITTING_ATTACKING_BEGIN);
						objectSprite->timeAccumulated += dt;
					}
					else
					{
						/* Update ani bình thường */
						objectSprite->timeAccumulated += dt;
						if (objectSprite->timeAccumulated >= SIMON_TIME_COOLDOWN_ATTACKING)
						{
							objectSprite->timeAccumulated -= SIMON_TIME_COOLDOWN_ATTACKING;
							objectSprite->SelectFrame(objectSprite->getCurrentFrame() + 1);
						}
						/* Update ani bình thường */

						if (objectSprite->getCurrentFrame() > SIMON_ANI_SITTING_ATTACKING_END) // đã đi vượt qua frame cuối
						{
							isAttacking = false;
							objectSprite->SelectFrame(SIMON_ANI_SITTING);
						}
					}

				}
				else
					objectSprite->SelectFrame(SIMON_ANI_SITTING);
#pragma endregion
			}
			else 
				if (isAttacking == true)
				{
#pragma region Đứng đánh
					if (index < SIMON_ANI_STANDING_ATTACKING_BEGIN)
					{
						objectSprite->SelectFrame(SIMON_ANI_DOWNSTAIR_ATTACKING_BEGIN);
						objectSprite->timeAccumulated = dt;
					}
					else
					{
						objectSprite->timeAccumulated += dt;
						if (objectSprite->timeAccumulated >= SIMON_TIME_COOLDOWN_ATTACKING)
						{
							objectSprite->timeAccumulated = SIMON_TIME_COOLDOWN_ATTACKING;
							objectSprite->SelectFrame(objectSprite->getCurrentFrame() + 1);
						}

						if (objectSprite->getCurrentFrame() > SIMON_ANI_STANDING_ATTACKING_END)
						{
							isAttacking = false;
							objectSprite->SelectFrame(SIMON_ANI_IDLE);
						}
					}
#pragma endregion
				}
				else
					if (isWalking == true)
					{
						if (isJumping == false)
						{
							if (index < SIMON_ANI_WALKING_BEGIN || index >= SIMON_ANI_DOWNSTAIR_ATTACKING_END)
							{
								objectSprite->SelectFrame(SIMON_ANI_WALKING_BEGIN);
								objectSprite->Update(dt);
							}
							else
							{
								objectSprite->SelectFrame(SIMON_ANI_JUMPING);
							}
						}
						else
						{
							if (isJumping == true)
							{
								objectSprite->SelectFrame(SIMON_ANI_JUMPING);
							}
							else
							{
								objectSprite->SelectFrame(SIMON_ANI_IDLE);
							}
						}
					}
		}
	}
	DebugOut(L"Simon đã được update về Sprite\n");
#pragma endregion 
#pragma endregion
	GameObject::Update(dt);
	if (isOnStair == false)
	{
		if (isJumping == true)
		{
			dx = vx * dt;
			dy = vy * dt;
			vy += SIMON_GRAVITY_JUMPING * dt;
		}
		else
		{
			if (isHurting == true)
			{
				vy += SIMON_GRAVITY_HURTING * dt;
			}
			else
				vy += SIMON_GRAVITY * dt;
		}
	}

	if (isOnStair == false)
	{
		colissionWithBrick(coObjects);
	}
	else
	{
		x += dx;
	}
	if (isOnStair == true)
	{
		
	}
	if (isProccessingOnStair == 3)
	{
		isProccessingOnStair = 0;
		vx = 0;
		vy = 0;
		isWalking = false;
	}
}
void Simon::Render(Camera*camera)
{
	if (IS_DEBUG_RENDER_BBOX)
		renderBoundingBox(camera);
	D3DXVECTOR2 pos = camera->TransForm(x, y);
	int alpha = 255;
	if (untouchable == true)
	{
		alpha = 128;
	}
	if (isDead&&isCollisionWithGround)
	{
		if (direction == -1)
		{
			_sprite_death->Draw(pos.x, pos.y, 255);
			

		}
		else
		{
			_sprite_death->DrawFlipX(pos.x, pos.y, 255);
			
		}
	}
	else
	{
		if (direction == -1)
		{
			objectSprite->Draw(pos.x, pos.y, alpha);
			
		}
		else
		{
			objectSprite->DrawFlipX(pos.x, pos.y, alpha);
			
		}
	}
}
void Simon::left()
{
	if (isOnStair == true)
		return;
	direction = 1;
}
void Simon::walking()
{
	if (isOnStair == true)
	{
		return;
	}
	if (isAttacking == true)
		return;
	vx = SIMON_WALKING_SPEED * direction;
	isWalking = 1;
}
void Simon::sit()
{
	if (isOnStair == true)
		return;
	vx = 0;
	isWalking=0;
	if (isSitting == false)
		y = y + PULL_UP_SIMON_AFTER_SITTING;
	isSitting = 1;
}
void Simon::resetSit()
{
	if (isSitting == true)
	{
		isSitting = 0;
		y = y - PULL_UP_SIMON_AFTER_SITTING;
	}
}
void Simon::jump()
{
	if (isJumping == true) //Nếu đang nhảy rồi thì không nhảy nữa
		return;
	if (isOnStair == true)
		return;
	if (isSitting == true)
		return;
	if (isAttacking == true)
		return;
	if (isHurting == true)
		return;
	vy = -SIMON_VJUMP;
	isJumping = true;
}
void Simon::stop()
{
	if (isAttacking == true)
		return;
	if (isOnStair == true)
		return;
	if (isHurting == true)
		return;
	vx = 0;
	isWalking = 0;
	if (isSitting == true)
	{
		isSitting = 0;
		y = y - PULL_UP_SIMON_AFTER_SITTING;
	}
}
void Simon::Init()
{
	health = SIMON_DEFAULT_HEALTH;
	lives = SIMON_DEFAULT_LIVES;
	Reset();
}
void Simon::Reset()
{
	direction = 1;
	isSitting = 0;
	isProccessingOnStair = 0;
	isOnStair = 0;
	isJumping = 0;
	isWalking = 0;
	isAttacking = 0;
	isHurting = 0;
	vx = 0;
	vy = 0;
	isDead = false;

}
void Simon::right()
{
	if (isOnStair == true)
		return;
	direction = 1;
}
void Simon::colissionWithBrick(const vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCollisionEvent> coEvents;
	vector<LPCollisionEvent> coEventResult;
	coEvents.clear();

	vector<LPGAMEOBJECT> listBrick;
	listBrick.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		listBrick.push_back(coObjects->at(i));
	//Tính toán các va chạm có thể xảy ra
	calcPotentialCollisions(&listBrick, coEvents);
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		isCollisionWithGround = false;
	}
	else
	{
		float min_tx, min_ty, nx = 0 , ny;
		filterCollisionEvents(coEvents, coEventResult, min_tx, min_ty, nx, ny);
		x += min_tx * dx + nx * 0.4f;
		if (ny == -1)
			y += min_ty * dy + ny * 0.4f;
		else
			y += dy;
		if (ny == -1)
		{
			vy = 0.1f;
			dy = vy * dt;
			if (isJumping)
			{
				isJumping = false;
				y = y - PULL_UP_SIMON_AFTER_JUMPING;
			}
		}
		if (ny!= 0)
		{
			isCollisionWithGround = true;

		}
		else
		{
			isCollisionWithGround = false;
		}
		if (nx != 0 || ny != 0)
		{
			isHurting = 0;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}