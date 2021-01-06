#include "ThrowingAxe.h"



ThrowingAxe::ThrowingAxe(Camera* camera)
{
	ObjectType = objectType::THROWINGAXE;
	objectTexture = TextureManager::GetInstance()->GetTexture(ObjectType);
	objectSprite = new GameSprite(objectTexture, 70);


	_spriteIcon = new GameSprite(TextureManager::GetInstance()->GetTexture(objectType::ITEMTHROWINGAXE), 0);

	isFinish = true;
	this->camera = camera;
}


ThrowingAxe::~ThrowingAxe()
{
	/*if (Sound::GetInstance()->isPlaying(eSound::soundAxe))
		Sound::GetInstance()->Stop(eSound::soundAxe);*/
}

void ThrowingAxe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!camera->checkObjectInCamera(x, y, (float)getWidth(), (float)getHeight())) // xử lí ra khỏi cam thì kết thúc
	{
		isFinish = true;

		/*if (Sound::GetInstance()->isPlaying(eSound::soundAxe))
			Sound::GetInstance()->Stop(eSound::soundAxe);*/

		return;
	}

	GameObject::Update(dt); //update dt dx d 
	vy += THROWINGAXE_GRAVITY * dt;

	y += dy;
	x += dx;

	objectSprite->Update(dt);
}

void ThrowingAxe::Attack(float X, float Y, int Direction)
{
	if (isFinish == false)
		return;
	Weapon::attack(X, Y, Direction);
	updatePositionWithSimon();
	vx = THROWINGAXE_SPEED_X * Direction;
	vy = -THROWINGAXE_SPEED_Y;

	/*Sound::GetInstance()->Play(eSound::soundAxe, true);*/
}

void ThrowingAxe::RenderIcon(float X, float Y)
{
	_spriteIcon->Draw(X, Y);
}
