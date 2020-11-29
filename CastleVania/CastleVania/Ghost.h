#ifndef _GHOST_
#define _GHOST_

#define GHOST_SPEED_X 0.09f
#define GHOST_GRAVITY 0.25f
#include "GameObject.h"
class Ghost:public GameObject
{
public: 
	Ghost(float x, float y, int direction);

	virtual ~Ghost();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render(Camera* camera);
};
#endif