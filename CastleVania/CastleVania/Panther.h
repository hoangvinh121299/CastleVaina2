#ifndef __PANTHER_H__
#define __PANTHER_H__

#define PANTHER_ANI_SITTING 0
#define PANTHER_ANI_RUNNIGN_BEGIN 1
#define PANTHER_ANI_RUNNING_END 3

#define PANTHER_SPEED_RUNNING 0.18f
#define PANTHER_VYJUMP 0.3f
#define PANTHER_VXJUMP 0.2f

#define PANTHER_GRAVITY 0.25f
#define PANTHER_GRAVITY_JUMPING 0.001f	


#include "GameObject.h"
#include "Simon.h"
class Panther : public GameObject
{
private:
	bool isSitting;
	bool isRunning;
	bool isJumping;
	bool isStart;
	Simon* simon;
public:
	Panther(float X, float Y, int Direction,Simon *simon);
	virtual ~Panther();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render(Camera* camera);

	void jump();
	void run();

};
#endif  


