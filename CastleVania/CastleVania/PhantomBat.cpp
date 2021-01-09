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
	int res = rand();
	
	InitResource();
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
	else{
		objectSprite->Update(dt);
		if (objectSprite->getCurrentFrame() == 0) 
			objectSprite->SelectFrame(1);
	}

	D3DXVECTOR2 pos = camera->TransForm(x, y);
	objectSprite->Draw(pos.x, pos.y);

	if (IS_DEBUG_RENDER_BBOX) {
		renderBoundingBox(camera);

		if (isUseBezierCurves == true) {
			for (float i = 0; i < 1; i += 0.01f) {
				//Đường xanh
				float xa = getPt(x1, x2, i);
				float ya = getPt(y1, y2, i);

				float xb = getPt(x2, x3, i);
				float yb = getPt(y2, y3, i);

				//Điểm đen
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
		else {
			RECT rect;
			rect.left = 0;
			rect.top = 0;
			rect.right = 15;
			rect.bottom = 15;
			D3DXVECTOR2 pos1 = camera->TransForm(xDestination, yDestination);
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
}

void PhantomBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (getHealth() < 0) return;
	switch (StatusProcessing)
	{
	case PHANTOMBAT_PROCESS_SLEEP:
		break;
	case PHANTOMBAT_PROCESS_START_1: //start 1 đi qua cửa sổ
		if (y >= yDestination) {
			vy = 0;
			StatusProcessing = PHANTOMBAT_PROCESS_START_2;
			xBefore = x;
			yBefore = y;
			//Vị trí ô cửa sổ boss cần đi tới
			xDestination = 5480;
			yDestination = 191;
			vx = ((xDestination - xBefore) / (1500.0f));
			vy = 0.12f; //độ cong khi đi xuống
		}
		break;
	case PHANTOMBAT_PROCESS_START_2: //
		if (isWaiting == false) {
			vy = -0.001f * dt;
			if (vy < 0) vy = 0;
			//Boss đã di chuyển đến điểm 2
			if (x >= xDestination) {
				vx = 0;
				vy = 0;
				isWaiting = true;
				timeWaited = 0; //Đặt lại thời gian chờ
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
		if (abs(x - xBefore) >= abs(xDestination - xBefore) 
			|| abs(y - yBefore)>=abs(yDestination - yBefore)){
			//Sau khi di chuyển xong thì đi thẳng theo hướng ngẫu nhiên
			vx = vy = 0;
			StartStraight();
		}
		break;
	case PHANTOMBAT_PROCESS_STRAIGHT_2:
		if (isWaiting == false) {
			if (abs(x - xBefore) >= abs(xDestination - xBefore)
				|| abs(y - yBefore) >= abs(yDestination - yBefore)) {
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
		break;
	case PHANTOMBAT_PROCESS_CURVES:
	{
		if (abs(x - xBefore) >= abs(xDestination - xBefore)) {
		vx = vy = 0;
		isUseBezierCurves = false;
		StartStraight();
		break;
	}
	float perc = (x - xBefore) / (xDestination - xBefore);
	float ya = getPt(y1, y2, perc);
	float yb = getPt(y2, y3, perc);
	float yy = getPt(ya, yb, perc);
	vy = (yy - yLastFrame) / dt;
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
		DebugOut(L"\n Trang thai %d", StatusProcessing);
		break;
	}
	//DebugOut(L"BOSS vs SIMON = %f\n", sqrt((simon->getX() - x)*(simon->getX() - x) + (simon->getY() - y)*(simon->getY() - y)));
	GameObject::Update(dt);
	x += dx;
	y += dy;
	/*if (x < camera->GetXCam()) DebugOut(L"x < xCam\n");
	if (camera->GetXCam() + camera->GetWidth() < x + getWidth()) DebugOut(L"x > xCam\n");
	if (y < camera->GetYCam()) DebugOut(L"y < yCam\n");
	if (camera->GetYCam() + camera->GetHeight() < y + getHeight()) DebugOut(L"y > yCam\n");*/
	if (x < camera->GetXCam()
		|| camera->GetXCam() + camera->GetWidth() < x + getWidth()
		|| y < camera->GetYCam()
		|| camera->GetYCam() + camera->GetHeight() < y + getHeight()
		) {
		//DebugOut(L"Boss ra ngoai pham vi camera");
		switch (StatusProcessing)
		{
		case PHANTOMBAT_PROCESS_CURVES:
			isUseBezierCurves = false;
			StartStraight();
			break;
		case PHANTOMBAT_PROCESS_STRAIGHT_1:
			StartStraight();
			break;
		case PHANTOMBAT_PROCESS_STRAIGHT_2:
			int temp = rand() % 3;
			switch (temp)
			{
			case 0: 
				StartAttack();
				break;
			default:
				StartCurves();
				break;
			}
			break;
		}
	}
	
	yLastFrame = y; //Lưu giá trị y của frame hiện tại
}

void PhantomBat::Start() {
	StatusProcessing = PHANTOMBAT_PROCESS_START_1;
	yBefore = y;
	vy = 0.05f;
	vx = 0.0f;
	yDestination += 40; //di chuyển xuống 40

}
void PhantomBat::ProcessSmart() {
	//Simon đang nhảy && simon-boss <= 150
	if (simon->isJumping && sqrt((simon->getX() - x)
		* (simon->getX() - x) 
		+ (simon->getY() - y) 
		* (simon->getY() - y)) <= 150.0f) {
		int random = rand() % 6;
		switch (random)
		{
		case 0:
			StartStraight();
			return;
		case 1:
			StartCurves();
			return;
		case 2:
			StartAttack();
			return;

		default:
			break;
		}
	}
	//20%
	if (rand() % 5 == 0){
		if (health <= 10 && simon->isAttacking)
		{
			StartCurves();
		}
	}
}
void PhantomBat::StartCurves() {
	DebugOut(L"CURVES\n");
	xBefore = x;
	yBefore = y;
	x1 = x;
	y1 = y;
	x2 = simon->getX();
	y2 = simon->getY() + simon->getHeight();
	//Nếu simon đang ở bên trái của boss
	if (simon->getX() < x) {
		xDestination = camera->GetXCam()
			- 100 + rand() % ( (int)(simon->getX()
				- camera->GetXCam() + 100) );
	}
	//Nêu simon đang ở bên phải của boss
	else {
		xDestination = simon->getX() + simon->getWidth()
			+ rand() % ( (int)
				(camera->GetXCam() + camera->GetWidth()
				- (simon->getX() + simon->getWidth() + 100)) );
	}
	yDestination = simon->getY() + simon->getHeight();
	x3 = xDestination;
	y3 = yDestination;
	vx = -(x - xDestination) / (abs(xDestination - xBefore) * 1000.0f / 50);
	vy = 0;

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
		StatusProcessing = PHANTOMBAT_PROCESS_STRAIGHT_1;
		break;
	}
	xBefore = x;
	yBefore = y;
	xDestination = (float)PHANTOMBAT_BOUNDARY_START_STRAIGHT_LEFT
		+ rand() % (PHANTOMBAT_BOUNDARY_START_STRAIGHT_RIGHT 
		- PHANTOMBAT_BOUNDARY_START_STRAIGHT_LEFT);
	yDestination = 80.0f + rand() % (190 - 80);
		DebugOut(L"StatusProcessing = %d, Target (%f, %f) \n", StatusProcessing, xDestination, yDestination);
	vx = (xDestination - xBefore) / 1000;
	vy = (xDestination - xBefore) / 1000;
}

void PhantomBat::StartAttack() {
	DebugOut(L"Boss is attacking\n");
	int fireBallDirection = 0;
	float xAttack = x + getWidth() / 2;
	float yAttack = y + getHeight() / 2;
	if (xAttack < simon->getX())
		fireBallDirection = 1;
	else fireBallDirection = -1;
	//Khoảng cách đạn bay từ boss đến Simon
	float distance = sqrt(
		((xAttack - simon->getX()) * (xAttack - simon->getX()))
		+
		((yAttack - simon->getY()) * (yAttack - simon->getY())));
	//Thời gian đạn bay từ boss đến simon
	float time = distance / FIREBALL_SPEED;
	weapon->setSpeed(fireBallDirection * abs(xAttack - simon->getX()) / time,
		abs(yAttack - simon->getY()) / time);
	Sound::GetInstance()->Play(eSound::soundHit);
	timeWaited = 0;
	isWaiting = true;
}

void PhantomBat::Stop()
{
	vx = vy = 0;
}
float PhantomBat::getPt(float n1, float n2, float perc) {
	float different = n2 - n1;
	return n1 + (different * perc);
}
void PhantomBat::InitResource() {
	x = PHANTOMBAT_DEFAULT_X;
	y = PHANTOMBAT_DEFAULT_Y;
	xBefore = x;
	yBefore = y;

	isWaiting = false; //Khởi tạo với giá trị false
	yLastFrame = y;
	vx = vy = 0;
	isUseBezierCurves = false;
}
PhantomBat::~PhantomBat() {};