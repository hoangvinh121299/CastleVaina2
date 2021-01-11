#ifndef __FISHMEN_H__
#define __FISHMEN_H__

#include "GameObject.h"
#include "Simon.h"
#include "Brick.h"
#include "FireBall.h"

#define FISHMEN_SPEED_Y_UP 0.4f
#define FISHMEN_SPEED_Y_DOWN 0.3f

#define FISHMEN_Y_JUMP 350

#define FISHMEN_ANI_JUMP 2 
#define FISHMEN_ANI_WALK_BEGIN 1
#define FISHMEN_ANI_WALK_END 2
#define FISHMEN_ANI_ATTACK 0

#define FISHMEN_GRAVITY 0.01f
#define FISHMEN_SPEED_X 0.07f

#define FISHMEN_X_LIMIT 140 //Đi được 140 thì đổi hướng 
#define FISHMEN_X_ATTACK_LIMIT 130 // ĐẠN ĐI ĐƯỢC 130 THÌ BIẾN MẤT 

#define FISHMEN_TIME_DELAY_AFTER_ATTACK 700 //THỜI GIAN DELAY SAU KHI TẤN CÔNG
class Fishmen : public GameObject
{
private:
	float y_start;
	float x_start;

	float x_before;
	float x_after;

	float xAccumulationtoAttack; // Khoảng cách đi để tấn công
	DWORD timeAttack;

	bool isRunning;
	FireBall* fireball;
	bool isAttacking;

	Simon* simon;
	vector<Weapon*> *listWeaponOfEnemy;
	Camera* camera;

public:
	Fishmen(float x, float y, int direction, Simon* simon, vector<Weapon*> *listWeap, Camera *camera);
	virtual ~Fishmen();

	void getBoundingBox(float& left, float& top, float& right, float& bottom);

	void Update(DWORD dt, vector<LPGAMEOBJECT>* listObject = NULL);
	void Render(Camera* camera);
	void attack();
};

#endif