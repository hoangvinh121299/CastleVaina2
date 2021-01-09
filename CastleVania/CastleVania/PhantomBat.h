#ifndef __PHANTOMBAT_H__
#define __PHANTOMBAT_H__

#include "GameObject.h"
#include "Simon.h"
#include "FireBall.h"

#define PHANTOMBAT_PROCESS_SLEEP 0
#define PHANTOMBAT_PROCESS_START_1 1 //ban đầu boss di chuyển xuống
#define PHANTOMBAT_PROCESS_START_2 2
#define PHANTOMBAT_PROCESS_CURVES 3 //di chuyển theo vòng cung
#define PHANTOMBAT_PROCESS_STRAIGHT_1 4 //di chuyển thẳng 1
#define PHANTOMBAT_PROCESS_STRAIGHT_2 5 //di chuyển thẳng 2
#define PHANTOMBAT_PROCESS_ATTACK 6
#define PHANTOMBAT_DEFAULT_X 5295.0f
#define PHANTOMBAT_DEFAULT_Y 90.0f
#define PHANTOMBAT_DEFAULT_HEALTH 24 //
#define PHANTOMBAT_BOUNDARY_START_STRAIGHT_LEFT 5178
#define PHANTOMBAT_BOUNDARY_START_STRAIGHT_RIGHT 5492


class PhantomBat : public GameObject
{
public: 
	int StatusProcessing;
private:
	float xBefore, yBefore;
	//Toạ độ điểm boss sẽ đi tới
	float xDestination, yDestination;
	Simon* simon;
	/*BezierCurves*/
	bool isUseBezierCurves;
	float x1;
	float y1;

	float x2;
	float y2;

	float x3;
	float y3;

	float yLastFrame; // y của frame trước đó
	/*BezierCurves*/
	Camera *camera;
	DWORD timeWaited;
	bool isWaiting;
	vector <Weapon*>* listWeaponOfEnemy;
	FireBall* weapon;
public:
	PhantomBat(Simon * simon, Camera * camera, vector <Weapon*>* listWeaponOfEnemy); 
	~PhantomBat();
	void getBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render(Camera * camera);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);

	void Start();
	void StartCurves();
	void StartStraight();
	void StartAttack();
	
	float getPt(float n1, float n2, float perc);
	
	void Stop();
	
	void ProcessSmart();
	void InitResource();
};

#endif