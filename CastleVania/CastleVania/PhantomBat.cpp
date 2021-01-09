#include "PhantomBat.h"




PhantomBat::PhantomBat(Simon * simon, Camera * camera, vector<Weapon*> * listWeaponOfEnemy)
{
	ObjectType = objectType::PHANTOMBAT;
	objectTexture = TextureManager::GetInstance()->GetTexture(ObjectType);
	objectSprite = new GameSprite(objectTexture, 70);

	this->simon = simon;
	this->camera = camera;
	this->listWeaponOfEnemy = listWeaponOfEnemy;

	weapon = new FireBall(camera);
	listWeaponOfEnemy->push_back(weapon);

	ResetResource();
}

void PhantomBat::getBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x + 5;
	top = y;
	right = x + objectTexture->GetFrameWidth() - 5;
	bottom = y + objectTexture->GetFrameHeight() - 10;
}

void PhantomBat::Render(Camera * camera) {
	if (getHealth() <= 0)
		return;

	if (StatusProcessing == PHANTOMBAT_PROCESS_SLEEP)
		objectSprite->SelectFrame(0);
	else
	{
		objectSprite->Update(dt);
if (objectSprite->getCurrentFrame() == 0)
objectSprite->SelectFrame(1);
	}
	D3DXVECTOR2 pos = camera->TransForm(x, y);
	if (direction == -1)
		objectSprite->Draw(pos.x, pos.y);
	else
		objectSprite->DrawFlipX(pos.x, pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		renderBoundingBox(camera);

	if (IS_DEBUG_RENDER_BBOX) {
		renderBoundingBox(camera);
		if (isUseBezierCurves == true) {
			for (float i = 0; i < 1; i += 0.01f) {
				//Line mau xanh
				float xa = getPt(x1, x2, i);
				float ya = getPt(y1, y2, i);

				float xb = getPt(x2, x3, i);
				float yb = getPt(y2, y3, i);

				//Diem mau do
				float xx = getPt(xa, xb, i);
				float yy = getPt(ya, yb, i);

				RECT rect;
				rect.left = 0;
				rect.top = 0;
				rect.right = 5;
				rect.bottom = 5;
				D3DXVECTOR2 pos = camera->TransForm(xx, yy);
				Game::GetInstance()->Draw(
					pos.x,
					pos.y,
					TextureManager::GetInstance()->GetTexture(
						objectType::RENDERBBOX)->Texture,
					rect.left,
					rect.top,
					rect.right,
					rect.bottom, 100);
			}
		}
		RECT rect;
		rect.left = 0;
		rect.top = 0;
		rect.right = 15;
		rect.bottom = 15;
		D3DXVECTOR2 pos1 = camera->TransForm(xTarget, yTarget);
		Game::GetInstance()->Draw(
			pos.x,
			pos.y,
			TextureManager::GetInstance()->GetTexture(
				objectType::RENDERBBOX)->Texture,
			rect.left,
			rect.top,
			rect.right,
			rect.bottom, 100);
	}
}

void PhantomBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (getHealth() < 0) return;
	switch (StatusProcessing)
	{
	case PHANTOMBAT_PROCESS_SLEEP:
		break;
	case PHANTOMBAT_PROCESS_START_1: //start 1 đi qua cửa sổ
		if (y >= yTarget) {
			vy = 0;
			StatusProcessing = PHANTOMBAT_PROCESS_START_2;
			xBefore = x;
			yBefore = y;
			xTarget = 5000;
			yTarget = 200;
			vx = ((xTarget - xBefore) / (1500.0f));
			vy = 0.5f;
		}
		break;
	case PHANTOMBAT_PROCESS_START_2: //
		if (isWaiting == false) {
			vy = -0.001f * dt;
			if (vy < 0) vy = 0;
			if (x >= xTarget) {
				vx = 0;
				vy = 0;
				isWaiting = true;
				timeWaited = 0;
			}
		}
		else {
			timeWaited += dt;
			if (timeWaited >= (UINT)(2000 + rand() % 1500)) {
				isWaiting = false;
				StartCurves();
			}
		}
		break;
	case PHANTOMBAT_PROCESS_STRAIGHT_1: //Di chuyển thẳng
		if (abs(x - xBefore) >= abs(xTarget - xBefore) 
			|| abs(y - yBefore)>=abs(yTarget - yBefore)){
			//Sau khi di chuyển xong thì đi thẳng theo hướng ngẫu nhiên
			vx = vy = 0;
			StartStraight();
		}
		break;
	case PHANTOMBAT_PROCESS_STRAIGHT_2:
		if (isWaiting == false) {
			if (abs(x - xBefore) >= abs(xTarget - xBefore)
				|| abs(y - yBefore) >= abs(yTarget - yBefore)) {
				vx = vy = 0;
				isWaiting = true; //chuyển sang trạng thái chờ
				timeWaited = 0; //reset thời gian đã chờ
			}
		}
		else {
			timeWaited += dt;
			if (timeWaited >= 3000) {
				isWaiting = false; //ngừng chờ
				int random = rand() % 3;
				switch (random)
				{
				case 0: // =33%
					StartAttack();
					break;
				default: // =66%
					StartCurves();
					break;
				}
			}
			else {
				ProcessSmart();
			}
			break;
		}
	case PHANTOMBAT_PROCESS_ATTACK:
		if (isWaiting == true) {
			timeWaited += dt;
			if (timeWaited >= 1500) {
				isWaiting = false;
				StartStraight();
			}
		}
		break;
	default:
		DebugOut(L"\n Trang thai ", StatusProcessing);
		break;
	}
	
	GameObject::Update(dt);
	x += dx;
	y += dy;

	yLastFrame = y;
}

void PhantomBat::Start() {
	StatusProcessing = PHANTOMBAT_PROCESS_START_1;
	yBefore = y;
	vy = 0.05f;
	vx = 0.0f;
	yTarget += 40; //di chuyển xuống 40

}
void PhantomBat::ProcessSmart() {
	if (simon->isJumping && sqrt((simon->getX() - x)
		* (simon->getX() - x) 
		+ (simon->getY() - y) 
		* (simon->getY() - y)) <= 150.0f) {

	}
}
void PhantomBat::StartCurves() {
	DebugOut(L"Start going curve\n");
	xBefore = x;
	yBefore = y;
	y1 = x;
	y1 = y;
	x2 = simon->getX();
	y2 = simon->getY() + simon->getHeight();

	if (simon->getX() < x) {
		xTarget = camera->GetXCam() - 100;
	}
	else {
		xTarget = camera->GetXCam();
	}
	yTarget = simon->getY(); +simon->getHeight();
	x3 = xTarget;
	y3 = yTarget;
	vx = 10;
	vy = 10;

	isUseBezierCurves = true;
	StatusProcessing = PHANTOMBAT_PROCESS_CURVES;
}

void PhantomBat::StartStraight() {
	DebugOut(L"Start going straight\n");
	switch (StatusProcessing)
	{
	case PHANTOMBAT_PROCESS_STRAIGHT_1:
		StatusProcessing = PHANTOMBAT_PROCESS_STRAIGHT_2;
		break;
	default:
		StatusProcessing = PHANTOMBAT_PROCESS_STRAIGHT_2;
		break;
	}
	xBefore = x;
	yBefore = y;
	xTarget = (float)PHANTOMBAT_BOUNDARY_START_STRAIGHT_LEFT
		+ rand() % (PHANTOMBAT_BOUNDARY_START_STRAIGHT_RIGHT - PHANTOMBAT_BOUNDARY_START_STRAIGHT_RIGHT);
	yTarget = 80.0f + rand() % (190 - 80);

	vx = (xTarget - xBefore) / 1000;
	vy = (xTarget - xBefore) / 1000;
}

void PhantomBat::StartAttack() {

}

void PhantomBat::Stop()
{
	vx = vy = 0;
}
float PhantomBat::getPt(float n1, float n2, float perc) {
	float different = n2 - n1;
	return n1 + (different * perc);
}
void PhantomBat::ResetResource() {
	x = PHANTOMBAT_DEFAULT_X;
	y = PHANTOMBAT_DEFAULT_Y;
	xBefore = x;
	yBefore = y;

	isWaiting = false;
	yLastFrame = y;
	vx = vy = 0;
	isUseBezierCurves = false;
}
PhantomBat::~PhantomBat() {};