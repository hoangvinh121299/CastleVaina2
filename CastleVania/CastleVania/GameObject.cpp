#include "GameObject.h"
#include "debug.h"
#include "Game.h"

GameObject::GameObject()
{
	x = y = 0;
	vx = vy = 0;
	direction = 1;
	health = 1;
	lastTimeAttacked = 0;
}
void GameObject::getBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + objectTexture->GetFrameWidth();
	bottom = top + objectTexture->GetFrameHeight();
}
void GameObject::Update(DWORD dt,vector<LPGAMEOBJECT> *coObjects)
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
}
int GameObject::getHealth()
{
	return health;
}
void GameObject::setHealth(int health)
{
	this->health = health;
}
void GameObject::subHealth(int subhealth)
{
	health -= subhealth;
	if (health < 0)
	{
		health = 0;
	}
}
void GameObject::setDirection(int direction)
{
	this->direction = direction;
}
int GameObject::getDirection()
{
	return this->direction;
}
void GameObject::setID(int id)
{
	this->id = id;
}
int GameObject::getID()
{
	return this->id;
}
void GameObject::setPostion(float x, float y)
{
	this->x = x;
	this->y = y;
}
void GameObject::setSpeed(float vx, float vy)
{
	this->vx = vx;
	this->vy = vy;
}
void GameObject::getPosiotion(float &x, float &y)
{
	x = this->x;
	y = this->y;
}
void GameObject::getSpeed(float &vx, float &vy)
{
	vx = this->vx;
	vy = this->vy;
}
float GameObject::getX()
{
	return x;
}
float GameObject::getY()
{
	return y;
}
float GameObject::getVx()
{
	return vx;
}
float GameObject::getVy()
{
	return vy;
}
void GameObject::setX(float X)
{
	x = X;
}
void GameObject::setY(float Y)
{
	y = Y;
}
void GameObject::setVx(float VX)
{
	vx = VX;
}
void GameObject::setVy(float VY)
{
	vy = VY;
}
int GameObject::getHeight()
{
	return objectTexture->GetFrameHeight();
}
int GameObject::getWidth()
{
	return objectTexture->GetFrameWidth();
}
objectType GameObject::getType()
{
	return this->ObjectType;
}

void GameObject::renderBoundingBox(Camera *camera)
{
	float l, t, r, b;
	getBoundingBox(l, t, r, b);
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = (LONG)r - (LONG)l;
	rect.bottom = (LONG)b - (LONG)t;
	D3DXVECTOR2 pos = camera->TransForm(l, t);
	//Vẽ Bounding Box màu đỏ
	Game::GetInstance()->Draw(
		pos.x,
		pos.y,
		TextureManager::GetInstance()->GetTexture(objectType::RENDERBBOX)->Texture,
		rect.left,
		rect.top,
		rect.right,
		rect.bottom,
		100
	);
	//DebugOut(L"Render thành công boundingbox\n");
}
//AABB nâng cao
LPCollisionEvent GameObject::sweptAABBEx(GameObject *coO)
{
	float sl, st, sr, sb; //Object tĩnh
	float ml, mt, mr, mb; //Object động
	float t, nx, ny;
	
	coO->getBoundingBox(sl, st, sr, sb);

	float svx, svy;
	coO->getSpeed(svx, svy);

	float sdx = svx * dt;
	float sdy = svy * dt;

	float dx = this->dx - sdx;
	float dy = this->dy - sdy;

	getBoundingBox(ml, mt, mr, mb);

	Game::SweptAABB(
		ml, mt, mr, mb,
		dx, dy,
		sl, st, sr, sb,
		t, nx, ny
	);
	CollisionEvent *e = new CollisionEvent(t, nx, ny, coO);
	return e;
}
void GameObject::calcPotentialCollisions(vector<GameObject*>*coObjects, vector<LPCollisionEvent>& coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCollisionEvent e = sweptAABBEx(coObjects->at(i));
		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}
	std::sort(coEvents.begin(), coEvents.end(), CollisionEvent::compare);
}
void GameObject::filterCollisionEvents(vector<LPCollisionEvent>& coEvents,
	vector<LPCollisionEvent>&coEventsResult,
	float &min_tx,
	float &min_ty,
	float &nx,
	float &ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;
	coEventsResult.clear();
	
	//Chạy vòng lặp lọc các object có va chạm
	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCollisionEvent c = coEvents[i];
		if (c->t <= min_tx && c->nx != 0)
		{
			min_tx = c->t;
			nx = c->nx;
			min_ix = i;
		}
		if (c->t <= min_ty && c->ny != 0)
		{
			min_ty = c->t;
			ny = c->ny;
			min_iy = i;
		}
	}
	if (min_ix >= 0)
		coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0)
		coEventsResult.push_back(coEvents[min_iy]);
}
bool GameObject::isColisionObjectwithObject(GameObject *obj)
{
	if(checkAABB(obj))// Kiểm tra có va chạm bằng AABB trước
		return true;
	LPCollisionEvent e = sweptAABBEx(obj); //KIểm tra va chạm bằng AABBEX
	bool res = e->t > 0 && e->t <= 1.0f; // Điều kiện có va chạm
	SAFE_DELETE(e);
	return res;

}
bool GameObject::checkAABB(GameObject *obj)
{
	float left, top, right, bottom;
	float left1, top1, right1, bottom1;
	this->getBoundingBox(left, top, right, bottom);
	obj->getBoundingBox(left1, top1, right1, bottom1);
	if (Game::GetInstance()->checkAABB(left, top, right, bottom, left1, top1, right1, bottom1))
		return true;

	return false;
}
//Trả về thời gian tấn công cuối cùng
DWORD GameObject::getLastTimeAttacked()
{
	return lastTimeAttacked;
}
//Phương thức set thời gian tấn công cuối
void GameObject::setTexture(GameTexture *texture)
{
	objectTexture = texture;
	objectSprite->texture = texture;
}
GameSprite * GameObject::getSprite()
{
	return objectSprite;
}
GameObject::~GameObject()
{
	SAFE_DELETE(objectSprite);
}
void GameObject::setLastTimeAttacked(DWORD dt)
{
	lastTimeAttacked = dt;
}