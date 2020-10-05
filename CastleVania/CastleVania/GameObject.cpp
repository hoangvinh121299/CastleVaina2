#include "GameObject.h"
#include "debug.h"
#include "Game.h"

GameObject::GameObject()
{
	x = y = 0;
	vx = vy = 0;
	directtion = 1;
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
	this->directtion = direction;
}
int GameObject::getDirection()
{
	return this->directtion;
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
eType GameObject::getType()
{
	return this->objectType;
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
		TextureManager::GetInstance()->GetTexture(eType::RENDERBBOX)->Texture,
		rect.left,
		rect.top,
		rect.right,
		rect.bottom,
		100
	);
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
}