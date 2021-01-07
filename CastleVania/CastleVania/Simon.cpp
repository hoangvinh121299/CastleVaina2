#include "Simon.h"
//Khởi tạo đối tuọng simon
Simon::Simon(Camera *camera)
{
	objectTexture = TextureManager::GetInstance()->GetTexture(objectType::SIMON);
	objectSprite = new GameSprite(objectTexture, 250);
	spriteDead = new GameSprite(TextureManager::GetInstance()->GetTexture(objectType::SIMON_DEATH), 250);
	ObjectType = objectType::SIMON;
	mapWeapon[objectType::MORNINGSTAR] = new MorningStar();
	this->camera = camera;
	this->sound = Sound::GetInstance();
	Init();
}
//Khi Simon chết
Simon::~Simon()
{
	SAFE_DELETE(spriteDead);
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

	//Trên thang
	if (isOnStair)
	{
		if (isAttacking) //Đang đánh 
		{
			if (directionY == -1)//Đang đi lên
			{
				//Xử lý đánh khi đang đi lên cầu thang
				if (index < SIMON_ANI_UPSTAIR_ATTACKING_BEGIN)//Nếu Ani chưa đúng 
				{
					objectSprite->SelectFrame(SIMON_ANI_UPSTAIR_ATTACKING_BEGIN);
					objectSprite->timeAccumulated = dt; //Cập nhật thời gian
				}
				else //Cập nhật sprite bình thường 
				{
					objectSprite->timeAccumulated += dt;
					if(objectSprite->timeAccumulated>=SIMON_TIME_ATTACK_COMPLETE)
					{
						objectSprite->timeAccumulated -= SIMON_TIME_ATTACK_COMPLETE;
						objectSprite->SelectFrame(objectSprite->getCurrentFrame() + 1);
					}

					if (objectSprite->getCurrentFrame() > SIMON_ANI_UPSTAIR_ATTACKING_END)//Vượt qua frame đánh
					{
						isAttacking = false;
						objectSprite->SelectFrame(SIMON_STAIR_STANDING_UP);
					}
				}
			}
			else
				//Xử lý đánh khi đang đi xuống cầu thang
			{
				if (index < SIMON_ANI_DOWNSTAIR_ATTACKING_BEGIN) //Nếu Ani chưa đúng
				{
					objectSprite->SelectFrame(SIMON_ANI_DOWNSTAIR_ATTACKING_BEGIN);
					objectSprite->timeAccumulated = dt;
				}
				else
				{
					//Update ani bình thường
					objectSprite->timeAccumulated += dt;
					if (objectSprite->timeAccumulated >= SIMON_TIME_ATTACK_COMPLETE)
					{
						objectSprite->timeAccumulated -= SIMON_TIME_ATTACK_COMPLETE;
						objectSprite->SelectFrame(objectSprite->getCurrentFrame() + 1);
					}
					if (objectSprite->getCurrentFrame() > SIMON_ANI_DOWNSTAIR_ATTACKING_END)
					{
						isAttacking = false;
						objectSprite->SelectFrame(SIMON_STAIR_STANDING_DOWN);
					}
				}
			}
		}
		else //Các trạng thái khác
		{
			if (isWalking) //Đi
			{
				if (isProccessingOnStair == 1) //Sprite đầu của Animation bước trên cầu thang
				{
					if (vy < 0) //Đi lên
						objectSprite->SelectFrame(SIMON_ANI_STAIR_GO_UP_BEGIN);
					else
						objectSprite->SelectFrame(SIMON_ANI_STAIR_GO_DOWN_BEGIN);
				}
				if (isProccessingOnStair == 2) //Sprite cuối của Animation bước trên cầu thang
				{
					if (vy < 0) //Đi lên
						objectSprite->SelectFrame(SIMON_ANI_STAIR_GO_UP_END);
					else
						objectSprite->SelectFrame(SIMON_ANI_STAIR_GO_DOWN_END);
				}

				distancePassOnStair = distancePassOnStair + abs(vy) * 16.0f; //Đi theo góc nghiêng

				if (distancePassOnStair >= 8.0f && isProccessingOnStair == 1) //Đi được 8 pixel và đang ở trạng thái 1
				{
					isProccessingOnStair++; //Chuyển trạng thái
				}

				if (distancePassOnStair >= 16.0f)
				{
					isProccessingOnStair++;
					/* fix lỗi mỗi lần đi quá 16 pixel*/
					if (direction == 1 && directionY == -1) //Đi lên bên phải 
					{
						x -= (distancePassOnStair - 16.0f);
						y += (distancePassOnStair - 16.0f);
					}
					if (direction == -1 && directionY == -1) //Đi lên bên trái  
					{
						x += (distancePassOnStair - 16.0f);
						y += (distancePassOnStair - 16.0f);
					}
					if (direction == 1 && directionY == 1) //Đi xuống bên phải  
					{
						x -= (distancePassOnStair - 16.0f);
						y -= (distancePassOnStair - 16.0f);
					}
					if (direction == 1 && directionY == -1) //Đi xuống bên trái 
					{
						x += (distancePassOnStair - 16.0f);
						y -= (distancePassOnStair - 16.0f);
					}
					distancePassOnStair = 0;
				}
			}
			else //Đứng yên trên cầu thang
			{
				if (this->directionY == -1) // ddang di len
					objectSprite->SelectFrame(SIMON_STAIR_STANDING_UP);
				else
					objectSprite->SelectFrame(SIMON_STAIR_STANDING_DOWN);
			}
		}
	}
	else //Các trường hợp không ở trên thang
	{
		if (isHurting == true)
		{
			objectSprite->SelectFrame(SIMON_ANI_HURTING);
			DebugOut(L"Simon at hurting");
		}
		//Không bị thương
		else
		{
			//Ngồi
			if (isSitting == true)
			{
				//Ngồi đánh 
				if (isAttacking == true)
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
				if (isAttacking == true)
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
					if (isWalking == true)
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
						if (isJumping == true)
						{                                                                                                                                                                                                                                   
							objectSprite->SelectFrame(SIMON_ANI_JUMPING);
							DebugOut(L"Simon at SIMON_ANI_JUMPING\n");
						}
			//Các trường hợp không làm gì cả 
						else
						{
							objectSprite->SelectFrame(SIMON_ANI_IDLE);

						}


		}
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
	if (isOnStair == false) //Không trên cầu thang thì mới có trọng lực
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
		if (!isAutoGoX)
			colissionWithBrick(coObjects);
		else
			x += dx;
	}

	if (isOnStair == true)
		CollisionIsOnStair(coObjects);
	//Trong trạng thái tấn công
	/*if (this->isAttacking)
	{
		float vx, vy;
		this->getSpeed(vx, vy);
		this->setSpeed(0, vy);
		return;
	}*/
	//Tự động reset isProcessing về bằng 0 khi isProcessing ++ =3
	if (isProccessingOnStair == 3)
	{
		isProccessingOnStair = 0;
		vx = 0;
		vy = 0;
		isWalking = false;
	}
	if (isAutoGoX == true)
	{
		if (abs(x - autoGoXBackupX) >= autoGoXDistance)
		{
			x = x - (abs(x - autoGoXBackupX) - autoGoXDistance);
			restoreBackupAutoGoX();
			isAutoGoX = false;

			DebugOut(L"[SIMON] end auto go X\n");
		}
	}
}
void Simon::Render(Camera*camera)
{
	if (IS_DEBUG_RENDER_BBOX)
		renderBoundingBox(camera);

	D3DXVECTOR2 pos = camera->TransForm(x, y);

	int alpha = 255;

	//Trong trạng thái bất tử thì màu nhạt hơn
	if (untouchable)
		alpha = 128;

	if (isDead && isCollisionWithGround) //Chết và đang va chạm với nền 
	{
		if (direction == -1)
			spriteDead->Draw(pos.x, pos.y, 255);
		else
			spriteDead->DrawFlipX(pos.x, pos.y, 255);
	}
	else //Các trường hợp khác ngoài chết 
	{
		if (this->getFreeze() == true) //Đang trong trạng thái nhấp nháy 
		{
			if (direction == -1)
				objectSprite->Draw(pos.x, pos.y, alpha, rand() % 256, rand() % 256, rand() % 256);
			else
				objectSprite->DrawFlipX(pos.x, pos.y, alpha, rand() % 256, rand() % 256, rand() % 256);

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
	/*if (isAttacking == true)
		return;*/
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
	
	health = SIMON_DEFAULT_HEALTH;
	lives = SIMON_DEFAULT_LIVES;
	heartCollect = SIMON_HEART_DEFAULT;
	score = SIMON_DEFAULT_SCORE;
	Reset();
}
void Simon::Reset()
{
	direction = 1;
	isSitting = false;
	isProccessingOnStair = 0;
	isOnStair = false;
	isJumping = false;
	isWalking = false;
	isAttacking = false;
	isHurting = false;
	vx = 0;
	vy = 0;
	isDead = false;
	isFreeze = false;
	timeFreeze = 0;
	typeWeaponCollect = objectType::NON_WEAPON_COLLECT;
	isAutoGoX = 0;
	distancePassOnStair = 0;
}
void Simon::right()
{
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
	if (typeWeapon == objectType::NON_WEAPON_COLLECT) //Đang không có vũ khí phụ
	{
		return;
	}
	//Kiểm tra còn đủ tim để đánh hay không
	switch (typeWeapon)
	{
		case MORNINGSTAR:
		{
			if (isAttacking)
			{
				return;
			}
			break;
		}
		default: // các vũ khí còn lại
		{
			if (heartCollect >= 1)
			{
			//Cho qua tiếp
			}
			else
				//Nếu không đủ thì bắt return lại
			return;// ko đủ HeartCollect thì ko attack
			break;
		}
	}
	bool subHeart = false;
	if (mapWeapon[typeWeapon]->getFinish()) //Chờ đến khi render hết tất cả frame của vũ khí thì mới được tấn công tiếp 
	{
		isAttacking = true;
		objectSprite->SelectFrame(SIMON_ANI_IDLE);
		objectSprite->ResetTime();
		mapWeapon[typeWeapon]->attack(this->x, this->y, this->direction);
		subHeart = true;
	}
	//Trừ tim 
	if (subHeart)
	{
		switch (typeWeapon)
		{
			case MORNINGSTAR:
			{
			// ko trừ
			break;
			}

			case STOPWATCH:
			{
			heartCollect -= 5;
			break;
			}

			default: // các vũ khí còn lại
			{
			heartCollect -= 1;
			break;
			}
		}
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
bool Simon::isColissionWithItem(Item* objectItem)
{
	if (objectItem->getFinish())
		return false;
	float l, t, r, b;
	float l2, t2, r2, b2;

	this->getBoundingBox(l, t, r, b); //Lấy ra boundingBox của Simon

	objectItem->getBoundingBox(l2, t2, r2, b2); //Lấy bounding box của Item

	if (Game::GetInstance()->checkAABB(l, t, r, b, l2, t2, r2, b2))
	{
		return true;
	}
}

void Simon::setFreeze(int temp)
{
	isFreeze = temp;
	timeFreeze = 0; //Thời gian đã đóng băng
}
bool Simon::getFreeze()
{
	return isFreeze;
}
void Simon::updateFreeze(DWORD dt)
{
	if (timeFreeze + dt >= SIMON_TIME_FREEZE_MAX)
	{
		setFreeze(false); //Kết thúc quá trình đóng băng
	}
	else
		timeFreeze += dt;
}
objectType Simon::getTypeWeaponCollect()
{
	return typeWeaponCollect;
}

void Simon::setTypeWeaponCollect(objectType temp)
{
	typeWeaponCollect = temp;
}
void Simon::getNewWeapon(objectType temp)
{
	switch (temp)
	{
		case DAGGER:
			if (mapWeapon[temp] == NULL)
			{
				mapWeapon[temp] = new Dagger(camera);
			}
			break;
	default:
		break;
	}
	sound->Play(eSound::soundCollectWeapon);
	setTypeWeaponCollect(temp);
}

bool Simon::getIsUseDoubleShot()
{
	return isUseDoubleShot;
}

void Simon::setIsUseDoubleShot(bool temp)
{
	isUseDoubleShot = temp;
}
void Simon::setHurt(LPCollisionEvent e)
{
	if (isHurting == true)
		return;
	if (e->nx == 0 && e->ny == 0) //Không có va chạm
		return;

	isWalking = 0;
	isAttacking = 0;
	isJumping = 0;

	resetSit();

	//Bị thương thì không render MORNINGSTAR nữa 
	mapWeapon[objectType::MORNINGSTAR]->setFinish(true);
	//Không đang trên thang và tự đi thì tự động bật ra khi bị thương
	if (!isOnStair && !isAutoGoX)
	{
		if (e->nx != 0)
		{
			vx = SIMON_WALKING_SPEED * e->nx;
			vy = -SIMON_VJUMP_HURT;
			isHurting = 1;
		}

		if (e->ny != 0)
		{
			vy = -SIMON_VJUMP_HURT;
			isHurting = 1;
		}
	}
	subHealth(2);
	sound->Play(eSound::soundHurting);
	StartUntouchable();
}
void Simon::StartUntouchable()
{
	untouchable = true;
	untouchable_Start = GetTickCount();
}
void Simon::setAutoGoX(int directionBeforeGo, int directionAfterGo, float distance, float speed)
{
	if (isAutoGoX)
		return;
	isAutoGoX = true;
	autoGoXBackupX = x;

	//Backup trạng thái
	isWalking_Backup = isWalking;
	isJumping_Backup = isJumping;
	isSitting_Backup = isSitting;
	isAttacking_Backup = isAttacking;
	isOnStair_Backup = isOnStair;
	isProccessing_OnStair_Backup = isProccessingOnStair;
	directionStair_Backup = directionStair;
	directionY_Backup = directionY;
	//Thiết lập thông số Auto
	autoGoXDistance = distance;
	autoGoXSpeed = speed;
	autoGoXDirection = (float)directionBeforeGo;
	this->directionAfterGo = directionAfterGo;
	//Thiết lập trạng thái trong khi đang Auto
	this->direction = directionBeforeGo;
	vx = speed * directionBeforeGo;
	isWalking = 1;
	isJumping = 0;
	isSitting = 0;
	isAttacking = 0;
	isOnStair = 0;
	isProccessingOnStair = 0;
}

bool Simon::getIsAutoGoX()
{
	return isAutoGoX;
}

void Simon::restoreBackupAutoGoX() //Trả lại trạng thái sau khi AutoGoX
{
	isWalking = isWalking_Backup;
	isJumping = isJumping_Backup;
	isSitting = isSitting_Backup;
	isAttacking = isAttacking_Backup;
	isOnStair = isOnStair_Backup;
	isProccessingOnStair = isProccessing_OnStair_Backup;
	directionStair = directionStair_Backup;
	directionY = directionY_Backup;

	direction = directionAfterGo; // set hướng sau khi đi

	isWalking = 0; // tắt trạng thái đang đi
	isAutoGoX = 0; // tắt trạng thái auto

	vx = 0;
	vy = 0;
	// đi xong thì cho simon đứng yên
}

//Lúc đang đi trên cầu thang
void Simon::CollisionIsOnStair(const vector<LPGAMEOBJECT>* coObjects)
{
	if (directionY == 1) //Đang đi xuống
	{
		int countCollisionBottom = 0;
		vector <LPGAMEOBJECT> listObj;
		listObj.clear();
		for (UINT i = 0; i < (*coObjects).size(); i++)
		{
			if ((*coObjects)[i]->getType() == objectType::STAIR_BOTTOM)
			{
				if (this->isColisionObjectwithObject((*coObjects)[i]))
				{
					countCollisionBottom++;
					break;
				}
			}
		}
		//Kiểm tra xem có va chạm với gạch lúc đi xuống không để kết thúc quá trình đi cầu thang
		if (countCollisionBottom > 0) // Có va chạm với bottom
		{
			vector<LPCollisionEvent> coEvents;
			vector <LPCollisionEvent> coEventResults;
			coEvents.clear();
			vector<LPGAMEOBJECT> listBrick;
			listBrick.clear();

			for (UINT i = 0; i < coObjects->size(); i++)
			{
				if (coObjects->at(i)->getType() == objectType::BRICK)
				{
					listBrick.push_back(coObjects->at(i));
				}
			}
			calcPotentialCollisions(&listBrick, coEvents);
			if (coEvents.size() == 0)
			{
				x += dx;
				y += dy;
			}
			else
			{
				float min_tx, min_ty, nx = 0, ny;
				filterCollisionEvents(coEvents, coEventResults, min_tx, min_ty, nx, ny);
				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;
				if (nx != 0 || ny != 0)
				{
					vx = 0;
					vy = 0;
					isOnStair = false;
					isWalking = false;
					isProccessingOnStair = 0;
				}
			}

			for (UINT i = 0; i < coEvents.size(); i++)
			{
				delete coEvents[i];
			}
			return;
		}
	}

	if (directionY == -1) //Đang lên
	{
		vector<LPGAMEOBJECT> listObj;
		int countCollisionTop = 0;
		listObj.clear();
		for (UINT i = 0; i < (*coObjects).size(); i++)
		{
			if ((*coObjects)[i]->getType() == objectType::STAIR_TOP)
			{
				if (this->isColisionObjectwithObject((*coObjects)[i]))
				{
					countCollisionTop++;
						break;
				}
			}
		}
		if (countCollisionTop > 0) //Có va chạm với top và đang đi lên
		{
			float backupVy = vy;
			y = y - 50;//Kéo simon lên cao để tạo va chạm giả với mặt đất
			vy = 999999999.0f; //Trọng lực kéo xuống để Simon đặt chân ngay trên sàn
			dy = vy * dt; //Cập nhật lại dy với vy mới 

			vector<LPCollisionEvent> coEvents;
			vector<LPCollisionEvent> coEventsResult;
			coEvents.clear();
			vector<LPGAMEOBJECT> listBrick;
			listBrick.clear();
			for (UINT i = 0; i < coObjects->size(); i++)
			{
				if (coObjects->at(i)->getType() == objectType::BRICK)
				{
					listBrick.push_back(coObjects->at(i));
				}
			}
			calcPotentialCollisions(&listBrick, coEvents);
			if (coEvents.size() == 0)
			{
				x += dx;
				y += dy;
			}
			else
			{
				float min_tx, min_ty, nx = 0, ny;

				filterCollisionEvents(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4;

				if (nx != 0 || ny != 0)
				{
					vx = 0;
					vy = 0;
					isOnStair = false;
					isWalking = false;
					isProccessingOnStair = 0;
				}
			}
			for (UINT i = 0; i < coEvents.size(); i++)
				delete coEvents[i];
			vy = backupVy;
			dy = vy * dt; //Cập nhật lại vy bình thường 
			return;
		}
	}
	//Nếu không đụng TOP và BOT thì di chuyển bình thường
	x += dx;
	y += dy;
}
void Simon::setLives(int l)
{
	lives = 1;
}
int Simon::getLives()
{
	return lives;
}
int Simon::getScore()
{
	return score;
}
void Simon::setScore(int s)
{
	score = s;
}
void Simon::setHeartCollect(int h)
{
	heartCollect = h;
}
int Simon::getHeartCollect()
{
	return heartCollect;
}


int Simon::getHealth()
{
	return this->health;
}

void Simon::setDead()
{
	setIsDead(true);
	timeWaitAfterDeath = 0;

	resetSit();
	vx = 0;
	isWalking = 0;
	isOnStair = 0;

	sound->Play(eSound::musicLifeLost);

	stop();
}
bool Simon::getIsDead()
{
	return isDead;
}
void Simon::setIsDead(bool dead)
{
	isDead = dead;
}

bool Simon::loseLife()
{
	if (lives - 1 < 0)
		return false;

	health = SIMON_DEFAULT_HEALTH;
	lives = lives - 1;

	heartCollect = SIMON_DEFAULT_HERTCOLLECT;

	Reset();

	x = positionBackup.x;
	y = positionBackup.y;

	return true;
}