#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "define.h"
#include "Camera.h"
#include "GameTexture.h"
#include "GameSprite.h"
#include "GameObject.h"
#include "Sound.h"
class Weapon: public GameObject
{
protected:
	bool isFinish; 
	DWORD lastTimeAttack;
public:
	Weapon();
	~Weapon();

	int getDirection();
	void setDirection(int direction);

	virtual void attack(float x, float y, int direction);

	virtual void Render(Camera* camera);
	virtual void updatePositionWithSimon();
	virtual bool isColission(GameObject* obj); //Kiểm tra vũ khi có va chạm với object ?
	virtual void renderIcon(float x, float y) = 0;
	bool getFinish();

	void setFinish(bool temp);

	DWORD getLastTimeAttack();

};

#endif