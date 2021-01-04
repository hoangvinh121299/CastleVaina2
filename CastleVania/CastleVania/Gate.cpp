#include "Gate.h"



Gate::Gate(float X, float Y)
{
	ObjectType = objectType::GATE;
	objectTexture = TextureManager::GetInstance()->GetTexture(ObjectType);
	objectSprite = new GameSprite(objectTexture, 200);
	health = 1;
	isStart = GATE_CLOSE;
	x = X;
	y = Y;
}


Gate::~Gate()
{
}

void Gate::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + objectTexture->GetFrameWidth() - 40;
	bottom = y + objectTexture->GetFrameHeight();

}

void Gate::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt); // update dt
}

void Gate::Render(Camera* camera)
{
	//Animation
	switch (isStart)
	{
	case GATE_CLOSE:
	{

		break;
	}
	case GATE_OPEN_1:
	{
		objectSprite->timeAccumulated += dt;
		if (objectSprite->timeAccumulated >= 1000)
		{
			objectSprite->timeAccumulated = 0;
			objectSprite->Next();
			Sound::GetInstance()->Play(eSound::soundOpenDoor);
			isStart++;
		}
		break;
	}
	case GATE_OPEN_2:
	{
		objectSprite->timeAccumulated += dt;
		if (objectSprite->timeAccumulated >= 100)
		{
			objectSprite->timeAccumulated = 0;
			objectSprite->Next();
			isStart++;
		}
		break;
	}
	case GATE_OPEN_3:
	{
		objectSprite->timeAccumulated += dt;
		if (objectSprite->timeAccumulated >= 100)
		{
			objectSprite->timeAccumulated = 0;
			objectSprite->Next();
			isStart++;
		}
		break;
	}
	case GATE_OPEN_4:
	{
		objectSprite->timeAccumulated += dt;
		if (objectSprite->timeAccumulated >= 500)
		{
			objectSprite->timeAccumulated = 0;
			objectSprite->Next();
			isStart++;
		}
		break;
	}
	default:
		break;
	}


	D3DXVECTOR2 pos = camera->TransForm(x, y);
	objectSprite->Draw(pos.x, pos.y);


	if (IS_DEBUG_RENDER_BBOX)
		renderBoundingBox(camera);

}

void Gate::Start()
{
	isStart = GATE_OPEN_1;
}

int Gate::GetStart()
{
	return isStart;
}
