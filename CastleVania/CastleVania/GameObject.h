#ifndef __GAMEOBJECT_H__
#define		__GAMEOBJECT_H__

#include "define.h"
#include "GameSprite.h"
#include "GameTexture.h"
#include"Camera.h"
#include "define.h"
#include "TextureManager.h"

using namespace std;
class GameObject; //Quản lý các object trong game
typedef GameObject * LPGAMEOBJECT; //Định nghĩa con trỏ cho mảng GameObject

struct CollisionEvent; //Quản lý sự kiện va chạm
typedef CollisionEvent * LPCollisionEvent; //Định nghĩa con trỏ cho mảng sự kiện va chạm

struct CollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->obj = obj;
	}
	static bool compare(const LPCollisionEvent &temp1, const LPCollisionEvent &temp2)
	{
		return temp1->t < temp2->t;
	}
};
class GameObject
{
protected:
	DWORD lastTimeAttacked; //Thời điểm bị tấn công cuối cùng
	int health;
	int id;

	int direction; //Hướng của Object -1: trái, 1: phải
	objectType ObjectType; // Loại object

	float x;
	float y;

	float dx;
	float dy;

	float vx;
	float vy;

	DWORD dt;

	GameTexture * objectTexture;
	GameSprite *objectSprite;
public:
	GameObject();
	virtual ~GameObject();
	// Phương thức lấy khung va chạm
	virtual void getBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *CoObject=NULL);
	virtual void Render(Camera *camera)=0;
	
	//Phương thức thao tác trên tình trạng object
	int getHealth();
	void setHealth(int health);
	void subHealth(int subhealth);
	void setDirection(int direction);
	int getDirection();
	void setID(int id);
	int getID();

	void setPostion(float x, float y);
    void getPosiotion(float &x, float &y);
	void setSpeed(float vx, float vy);
	void getSpeed(float &vx, float &vy);

	float getX();
	void setX(float x);
	float getY();
	void setY(float y);
	float getVx();
	void setVx(float vx);
	float getVy();
	void setVy(float vy);
	int getWidth();
	int getHeight();

	objectType getType();

	//Render khung va chạm ra game
	void renderBoundingBox(Camera *camera);
	LPCollisionEvent sweptAABBEx(GameObject * coO);
	//Dự báo va chạm có thể diễn ra 
	void calcPotentialCollisions(vector<GameObject*> *coOObject, vector<LPCollisionEvent> &coEvents);
	//Lọc sự kiện va chạm sẽ diễn ra
	void filterCollisionEvents(
		vector<LPCollisionEvent> &coEvents,
		vector<LPCollisionEvent> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float&nx,
		float&ny);
	//Kiểm tra xem có va chạm hay không bằng AABB va SwpeptAABB
	bool isColisionObjectwithObject(GameObject *obj);
	bool checkAABB(GameObject *obj);

	//Lấy ra thời điểm bị tấn công cuối
	DWORD getLastTimeAttacked();
	/*void setLastTimeAttacked(DWORD dt);*/

	void setTexture(GameTexture *texture);
	GameSprite *getSprite();
};

#endif