#ifndef __MORNING_STAR__
#define __MORNING_STAR__

#define MORNINGSTAR_TIME_DELAY_ANI 120 // THỜI GIAN GIỮA CÁC LẦN CHUYỂN FRAME

//MORNINGSTAR LEVEL BẮT ĐẦU
#define MORNINGSTAR_ANI_LEVEL0_START 0
#define MORNINGSTAR_ANI_LEVEL0_END 3

//MORNINGSTAR LEVEL 1
#define MORNING_ANI_LEVEL1_START 4
#define MORNING_ANI_LEVEL1_END 7

//MORNINGSTAR MAX LEVEL
#define MORNINGSTAR_ANI_LEVEL2_START 8
#define MORNINGSTAR_ANI_LEVEL2_END 11

#include "Weapon.h"
#include "GameObject.h"
#include "TextureManager.h"

class MorningStar: public Weapon
{
protected:
	int level;

public:
	MorningStar();
	~MorningStar();


	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render(Camera* camera);
	void attack(float x, float y, int Direction);

	void updatePositionWithSimon();
	void getBoundingBox(float& left, float& top, float& right, float& bottom);
	void renderIcon(float x, float y);

	/*void upgradeLevel();*/

	int getLevel();

	bool isColission(GameObject* object);
};

#endif