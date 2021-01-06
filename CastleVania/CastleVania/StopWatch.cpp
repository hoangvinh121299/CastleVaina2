﻿#include "StopWatch.h"



StopWatch::StopWatch()
{
	ObjectType = objectType::STOPWATCH;

	objectTexture = TextureManager::GetInstance()->GetTexture(objectType::STOPWATCH);
	objectSprite = new GameSprite(objectTexture, 100);

	isFinish = true;
}



StopWatch::~StopWatch()
{
	/*if (Sound::GetInstance()->isPlaying(eSound::soundStopWatch))
		Sound::GetInstance()->Stop(eSound::soundStopWatch);*/
}

void StopWatch::Attack(float X, float Y, int Direction)
{
	TimeSpent = 0;
	isFinish = false;
	/*Sound::GetInstance()->Play(eSound::soundStopWatch, true, 100);*/
}

void StopWatch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isFinish)
		return;
	TimeSpent += dt;
	if (TimeSpent >= 4000) // hoạt động trong 5s
	{
		TimeSpent = 0;
		/*if (Sound::GetInstance()->isPlaying(eSound::soundStopWatch))
			Sound::GetInstance()->Stop(eSound::soundStopWatch);*/
		isFinish = true;
	}
}

void StopWatch::Render(Camera* camera)
{
}

bool StopWatch::isCollision(GameObject* obj)
{
	return false; // StopWatch ko xét va chạm
}

void StopWatch::RenderIcon(float X, float Y)
{
	objectSprite->Draw(X, Y);
}
