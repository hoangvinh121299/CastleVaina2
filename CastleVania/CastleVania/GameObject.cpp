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