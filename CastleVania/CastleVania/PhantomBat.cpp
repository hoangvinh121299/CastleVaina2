#include "PhantomBat.h"




PhantomBat::PhantomBat(Simon* simon, Camera* camera, vector<Weapon*>* listWeaponOfEnemy)
{
	ObjectType = objectType::PHANTOMBAT;
	objectTexture = TextureManager::GetInstance()->GetTexture(ObjectType);
	objectSprite = new GameSprite(objectTexture, 70);

}
void PhantomBat::getBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x + 5;
	top = y;
	right = x + objectTexture->GetFrameWidth() - 5;
	bottom = y + objectTexture->GetFrameHeight() - 10;
}
void PhantomBat::Render(Camera * camera) {
	D3DXVECTOR2 pos = camera->TransForm(x, y);
	if (direction == -1)
		objectSprite->Draw(pos.x, pos.y);
	else
		objectSprite->DrawFlipX(pos.x, pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		renderBoundingBox(camera);
}
void PhantomBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (getHealth() < 0) return;
	switch (StatusProcessing)
	{
	case PHANTOMBAT_PROCESS_SLEEP:
		break;
	case PHANTOMBAT_PROCESS_START_1:
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
	case PHANTOMBAT_PROCESS_START_2:
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
}
void PhantomBat::Start() {
	StatusProcessing = PHANTOMBAT_PROCESS_START_1;
	yBefore = y;
	vy = 0.05f;
	vx = 0.0f;
	yTarget += 40; //di chuyển xuống 40

}
void PhantomBat::StartCurves() {
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

}
void PhantomBat::StartAttack() {

}
void PhantomBat::Stop()
{
	vx = vy = 0;
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