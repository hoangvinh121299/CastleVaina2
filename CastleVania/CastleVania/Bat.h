#ifndef __BAT_H__
#define __BAT__H

#include "GameObject.h"
#include "debug.h"
#define BAT_SPEED_X 0.1f
#define BAT_SPEED_Y 0.05f
#define LIMITY 20
class Bat:public GameObject
{

private:

	float yBackup; //Vị trí khởi tạo của Y

public:

	Bat(float x, float y , int direction = -1);
	virtual ~Bat();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* listObject = NULL);
	void Render(Camera* camera);
};

#endif