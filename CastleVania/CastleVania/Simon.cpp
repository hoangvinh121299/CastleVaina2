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
					if (objectSprite->getCurrentFrame() > SIMON_ANI_ATTACKING_END)// ĐÃ đi vượt qua frame cuối của ani đánh cầu thang
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
					if (objectSprite->getCurrentFrame() > SIMON_ANI_ATTACKING_END)// ĐÃ đi vượt qua frame cuối của ani đánh cầu thang
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
#pragma endregion
			}
		}
	}
#pragma endregion 
#pragma endregion
}