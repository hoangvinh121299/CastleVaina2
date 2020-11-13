#include "Simon.h"
//Khởi tạo đối tuọng simon
Simon::Simon(Camera *camera)
{
	objectTexture = TextureManager::GetInstance()->GetTexture(objectType::SIMON);
	objectSprite = new GameSprite(objectTexture, 250);
	ObjectType = objectType::SIMON;
	mapWeapon[objectType::MORNINGSTAR] = new MorningStar();
	this->camera = camera;
	Init();
}
//Khi Simon chết
Simon::~Simon()
{
	/*SAFE_DELETE(_sprite_death);*/
}
void Simon::getBoundingBox(float &left, float &top, float &right, float &bottom)
{
	//Bounding Box lúc Simon ngồi
	if (isSitting == true)
	{
		left = x + 15;
		top = y - 1;
		right = x + SIMON__BBOX_WIDTH - 15;
		bottom = y + SIMON_BBOX_SITTING_HEIGHT;
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
		x = (float)(camera->getBoundaryRight() + SCREEN_WIDTH - SIMON__BBOX_WIDTH);

#pragma region Update về Sprite
	int index = objectSprite->getCurrentFrame();

	//Bị thương
		if (isHurting==true)
		{
			objectSprite->SelectFrame(SIMON_ANI_HURTING);
			DebugOut(L"Simon at hurting");
		}

		//Không bị thương
		else
		{
			//Ngồi
			if (isSitting==true)
			{
				//Ngồi đánh 
				if (isAttacking==true)
				{
					if (index < SIMON_ANI_SITTING_ATTACKING_BEGIN)//Sai ani
					{
						objectSprite->SelectFrame(SIMON_ANI_SITTING_ATTACKING_BEGIN);
						objectSprite->timeAccumulated = dt;
						DebugOut(L"Simon is sitting attacking/n ");
					}
					
					else
					{
						/* Update ani bình thường */
						objectSprite->timeAccumulated += dt;
						if (objectSprite->timeAccumulated >= SIMON_TIME_ATTACK_COMPLETE)
						{
							objectSprite->timeAccumulated -= SIMON_TIME_ATTACK_COMPLETE;
							objectSprite->SelectFrame(objectSprite->getCurrentFrame() + 1);
							DebugOut(L"Simon is cooldown/n");
						}

						/* Update ani bình thường */
						if (objectSprite->getCurrentFrame() > SIMON_ANI_SITTING_ATTACKING_END) // đã đi vượt qua frame cuối
						{
							
							isAttacking = false;
							objectSprite->SelectFrame(SIMON_ANI_SITTING);
								DebugOut(L"Simon at sitting\n");
						}
					}

				}
				//Không đánh chỉ ngồi 
				else
				{
					
					objectSprite->SelectFrame(SIMON_ANI_SITTING);
					DebugOut(L"Simon at sitting\n");
				}

			}
			//Không ngồi 
			else 
				//Đứng đánh 
				if (isAttacking==true )
				{

					if (index < SIMON_ANI_STANDING_ATTACKING_BEGIN)
					{
						objectSprite->SelectFrame(SIMON_ANI_STANDING_ATTACKING_BEGIN);
						objectSprite->timeAccumulated = dt;
						DebugOut(L"Simon begin ani attacking standing\n");
					}
					else
					{
						objectSprite->timeAccumulated += dt;
						if (objectSprite->timeAccumulated >= SIMON_TIME_ATTACK_COMPLETE)
						{
							objectSprite->timeAccumulated -= SIMON_TIME_ATTACK_COMPLETE;
							objectSprite->SelectFrame(objectSprite->getCurrentFrame() + 1);
							DebugOut(L"Simon at cooldown\n");
						}

						if (objectSprite->getCurrentFrame() > SIMON_ANI_STANDING_ATTACKING_END)
						{
							isAttacking = false;
							objectSprite->SelectFrame(SIMON_ANI_IDLE);
							DebugOut(L"Simon at SIMON_ANI_IDLE\n");
						}
					}

				}
			//Không đứng đánh 
				else
					//Đi bộ
					if (isWalking==true)
					{
						//Không nhảy đi bộ
						if (isJumping == false)
						{
							if (index < SIMON_ANI_WALKING_BEGIN || index >= SIMON_ANI_WALKING_END)
								objectSprite->SelectFrame(SIMON_ANI_WALKING_BEGIN);

							objectSprite->Update(dt);
						}
						else
						{
							objectSprite->SelectFrame(SIMON_ANI_JUMPING);
						}
					}
						//Các trường hợp khác 
					else
							//Nhảy
						if (isJumping==true )
							{
								objectSprite->SelectFrame(SIMON_ANI_JUMPING);
								DebugOut(L"Simon at SIMON_ANI_JUMPING\n");
							}
							//Các trường hợp không làm gì cả 
						else
							{
							objectSprite->SelectFrame(SIMON_ANI_IDLE);
								DebugOut(L"Simon at SIMON_ANI_IDLE\n");
							}
					
			DebugOut(L"Simon đã được update về Sprite\n");
		}
		
		//Update về vũ khí cho Simon
		GameObject::Update(dt);
		for (auto& objWeapon : mapWeapon)
		{
			if (objWeapon.second->getFinish() == false) // vũ khi này chưa kết thúc thì update
			{
				if (objWeapon.second->getType() == objectType::MORNINGSTAR)
				{
					objWeapon.second->setPostion(this->x, this->y);
					objWeapon.second->setSpeed(vx, vy); // set vận tốc để kt va chạm
					objWeapon.second->updatePositionWithSimon();
				}
				objWeapon.second->Update(dt, coObjects);
			}
		}
//update trạng thái riêng của Simon
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

	//Trong trạng thái tấn công
	if (this->isAttacking)
	{
		float vx, vy;
		this->getSpeed(vx, vy);
		this->setSpeed(0, vy);
		return;
	}
}
void Simon::Render(Camera*camera)
{
	if (IS_DEBUG_RENDER_BBOX)
		renderBoundingBox(camera);

	D3DXVECTOR2 pos = camera->TransForm(x, y);

	int alpha = 255;

	if (untouchable)
		alpha = 128;

	if (direction == -1)
	{
		objectSprite->Draw(pos.x, pos.y, alpha);
		
		
	}
	else
	{
		objectSprite->DrawFlipX(pos.x, pos.y, alpha);
		
	}
	for (auto& objWeapon : mapWeapon)
	{
		if (objWeapon.second->getFinish() == false) // vũ khi này chưa kết thúc thì render
		{
			objWeapon.second->Render(camera);
		}
	}
}
void Simon::left()
{
	if (isOnStair == true)
		return;
	if (isAttacking == true)
		return;
	if (isJumping)
		return;
	direction = -1;
}
void Simon::walking()
{
	if (isAttacking == true)
		return;
	if (isSitting == true)
		return;
	isWalking = true;
	vx = SIMON_WALKING_SPEED * direction;
	
}
void Simon::sit()
{
	if (isAttacking)
		return;
	if (isJumping)
		return;
	vx = 0;
	isWalking=0;
	if (isSitting == false)
		y = y + PULL_UP_SIMON_AFTER_SITTING;
	isSitting = true;
}
void Simon::resetSit()
{
	if (isSitting == true)
	{
		isSitting = false;
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
	isWalking = false;
	if (isSitting == true)
	{
		isSitting = false;
		y = y - PULL_UP_SIMON_AFTER_SITTING;
	}
}
void Simon::Init()
{
	/*
	health = SIMON_DEFAULT_HEALTH;
	lives = SIMON_DEFAULT_LIVES;
	*/
	Reset();
}
void Simon::Reset()
{
	direction = 1;
	isSitting = false;
	isProccessingOnStair = false;
	isOnStair = false;
	isJumping = false;
	isWalking = false;
	isAttacking = false;
	isHurting = false;
	vx = 0;
	vy = 0;
	isDead = false;
	
	
}
void Simon::right()
{
	if (isJumping)
		return;
	if (isOnStair == true)
		return;
	if (isAttacking == true)
		return;
	direction = 1;
}

// Đứng trên nền gạch
void Simon::colissionWithBrick(const vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCollisionEvent> coEvents;
	vector<LPCollisionEvent> coEventResult;
	coEvents.clear();

	vector<LPGAMEOBJECT> listBrick;
	listBrick.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if(coObjects->at(i)->getType()==objectType::BRICK)
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
void Simon::attack(objectType typeWeapon)
{
	if (mapWeapon[typeWeapon]->getFinish()) //Chờ đến khi render hết tất cả frame của vũ khí thì mới được tấn công tiếp 
	{
		isAttacking = true;
		objectSprite->SelectFrame(SIMON_ANI_IDLE);
		objectSprite->ResetTime();

		mapWeapon[typeWeapon]->attack(this->x, this->y, this->direction);
	}
}
bool Simon::isUsingWeapon(objectType typeWeapon)
{
	if (this->mapWeapon.find(typeWeapon) != this->mapWeapon.end())
	{
		if (this->mapWeapon[typeWeapon]->getFinish() == false)
			return true;
	}
	return false;
}
