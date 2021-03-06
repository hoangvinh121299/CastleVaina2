﻿#ifndef __SIMON_H__
#define __SIMON_H__

#include "GameObject.h"
#include "debug.h"
#include "Weapon.h"
#include "MorningStar.h"
#include "Item.h"
#include "Dagger.h"
#include "Sound.h"
#include "HolyWater.h"
#include "Boomerang.h"
#include "ThrowingAxe.h"
#include "StopWatch.h"
//CÁC THÔNG SỐ CƠ BẢN CỦA SIMON
#define SIMON_POSITION_DEFAULT 50.0f, 300.0f
#define SIMON__BBOX_WIDTH 60
#define SIMON_BBOX_HEIGHT 63
#define SIMON_BBOX_SITTING_HEIGHT 45
#define SIMON_BBOX_JUMPING_HEIGHT 45

#define PULL_UP_SIMON_AFTER_SITTING 18.0f // Thêm 18 pixel của BBOX sau khi SIMON đứng lên

#define SIMON_VJUMP 0.34f // Vận tốc khi SIMON nhảy lên
#define SIMON_VJUMP_HURT 0.2f // Vận tốc nhảy lên của SIMON nhảy lên khi chịu tổn thương
#define PULL_UP_SIMON_AFTER_JUMPING 18.0f // KÉO SIMON LÊN 18PX SAU KHI NHẢY

#define SIMON_GRAVITY 0.005f // Trọng lực kéo SIMON
#define SIMON_GRAVITY_JUMPING 0.001f // Trọng lực kéo SIMON lúc nhảy
#define SIMON_GRAVITY_HURTING 0.001f // Trọng lực kéo simon xuống khi nhảy lên lúc chịu tổn thương

#define SIMON_WALKING_SPEED 0.12f //Vận tốc SIMON lúc đi bộ
//CÁC TRẠNG THÁI CỦA SIMON
#define SIMON_STATE_IDLE 0
#define SIMON_STATE_WALKING 1

#define SIMON_ANI_WALKING_BEGIN 1
#define SIMON_ANI_WALKING_END 3

#define SIMON_ANI_IDLE 0

#define SIMON_ANI_JUMPING 4
#define SIMON_ANI_SITTING 4 // DO ANI LÚC NHẢY VÀ NGỒI NHƯ NHAU

//ANI SIMON NGỒI ĐÁNH
#define SIMON_ANI_SITTING_ATTACKING_BEGIN 15
#define SIMON_ANI_SITTING_ATTACKING_END 17

//ANI SIMON ĐỨNG ĐÁNH
#define SIMON_ANI_STANDING_ATTACKING_BEGIN 5
#define SIMON_ANI_STANDING_ATTACKING_END 7

//ANI SIMON ĐI XUỐNG CẦU THANG ĐÁNH
#define SIMON_ANI_DOWNSTAIR_ATTACKING_BEGIN 18
#define SIMON_ANI_DOWNSTAIR_ATTACKING_END 20

// ANI SIMON ĐI LÊN CẦU THANG ĐÁNH
#define SIMON_ANI_UPSTAIR_ATTACKING_BEGIN 21
#define SIMON_ANI_UPSTAIR_ATTACKING_END 23


//ANI TIME ATTACK
#define SIMON_TIME_ATTACK_COMPLETE 120 // THỜI GIAN CHẠY HẾT ANIMATION TẤN CÔNG CỦA SIMON

#define SIMON_ANI_HURTING 8 //ANI KHI BỊ ĐÁNH
#define SIMON_ANI_HIDE_FACE 9

//ANI LÚC XUỐNG CẦU THANG
#define SIMON_ANI_DOWNSTAIR_BEGIN 10
#define SIMON_ANI_DOWNSTAIR_END 11

//ANI LÚC LÊN CẦU THANG
#define SIMON_ANI_UPSTAIR_BEGIN 12
#define SIMON_ANI_UPSTAIR_END 13

//VẬN TỐC LÚC ĐI CẦU THANG
#define SIMON_SPEED_ONSTAIR 0.09f

#define SIMON_STAIR_STANDING_UP 12
#define SIMON_STAIR_STANDING_DOWN 10

#define SIMON_TIME_FREEZE_MAX 500

#define SIMON_ANI_STAIR_GO_UP_BEGIN 12 //BẮT ĐẦU ĐI LÊN TRÊN
#define SIMON_ANI_STAIR_GO_UP_END 13 // kẾT THỨC QUÁ TRÌNH ĐI LÊN

#define SIMON_ANI_STAIR_GO_DOWN_BEGIN 10// Bắt đầu đi xuống
#define SIMON_ANI_STAIR_GO_DOWN_END 11//Kết thúc quá trình đi xuống
//Thông số mặc định của SIMON
#define SIMON_DEFAULT_HEALTH 16
#define SIMON_DEFAULT_HERTCOLLECT 5 //SỐ MÁU BAN ĐẦU CỦA SIMON
#define SIMON_DEFAULT_SCORE 0
#define SIMON_DEFAULT_LIVES 5 //SỐ MẠNG BAN ĐẦU CỦA SIMON
#define SIMON_UNTOUCHABLE_TIME 2000
#define SIMON_HEART_DEFAULT 10
class Simon:public GameObject
{
private:
	GameSprite *spriteDead;
	int heartCollect; //Số lượng item heart nhặt được
	int lives; //Số mạng người chơi
	int score; //số điểm

	bool isFreeze; //Trạng thái nhấp nháy khi nhặt vật phẩm
	DWORD timeFreeze; //Thời gian trạng thái nhấp nháy

	D3DXVECTOR2 positionBackup;

	bool isWalking_Backup;
	bool isJumping_Backup;
	bool isSitting_Backup;
	bool isAttacking_Backup;
	bool isOnStair_Backup;
	int isProccessing_OnStair_Backup;
	int directionStair_Backup;
	int directionY_Backup;
	int directionAfterGo;
	objectType typeWeaponCollect;
	bool isDead;
	bool isUseDoubleShot;
	Camera *camera;

	float autoGoXDistance; //Khoảng cách Simon auto đi
	float autoGoXSpeed;
	float autoGoXDirection; //Hướng tự động đi
	float autoGoXBackupX; //Vị trí băt đầu đi tự động

	bool isAutoGoX = 0; //Có đang trong trạng thái auto hay không

	
public:
	bool isAttacking;
	bool isHurting;
	bool isWalking;
	bool isJumping;
	bool isSitting;

	int directionY; //Hướng đi theo trục y của Simon
	bool isOnStair; //Có đang ở trên cầu thang hay không
	int isProccessingOnStair; //Có 2 giai đoạn
	int directionStair; //Hướng của cầu thang đang đi -1 là qua trái, 1 là qua phải
	
	float distancePassOnStair = 0;
	bool untouchable; //Trạng thái bất tử
	DWORD untouchable_Start; // Thời điểm bất tử bắt đầu
	bool isCollisionWithGround= false; // Đang va chạm với đất theo trục Y 
	DWORD timeWaitAfterDeath; // Thời gian chờ hồi sinh sau khi chết
	
	unordered_map<objectType, Weapon*> mapWeapon;
	Sound* sound;
	Simon(Camera *camera);
	~Simon();

	virtual void getBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObject);
	virtual void Render(Camera *camera);

	void sit();

	void stop();

	void resetSit();

	void walking();

	void jump();
	void right();
	void left();

	void attack(objectType typeWeapon);
	void colissionWithBrick(const vector<LPGAMEOBJECT> *coObjects=NULL);
	bool isUsingWeapon(objectType typeWeapon);
	void Init(); // Khởi tạo lại các trạng thái, Heartcollect, health, lives, score
	void Reset();//Khởi tạo lại các trạng thái
	bool isColissionWithItem(Item* objectItem);
	void CollisionIsOnStair(const vector<LPGAMEOBJECT>* coObjects);
	//Trạng thái nhấp nháy
	void setFreeze(int temp);
	bool getFreeze();
	void updateFreeze(DWORD dt);
	//Vũ khí phụ
	objectType getTypeWeaponCollect();
	void setTypeWeaponCollect(objectType temp);
	void getNewWeapon(objectType temp);

	void setIsUseDoubleShot(bool temp);
	bool getIsUseDoubleShot();
	//Trạng thái bị thương
	void setHurt(LPCollisionEvent e);
	//Trạng thái bất tử
	void StartUntouchable();

	void setAutoGoX(int Direction,
		int DirectionBackup,
		float dx,
		float speed); //Set các thông số khi auto go và backup trạng thái trước khi auto
	bool getIsAutoGoX(); //Kiểm tra xem có đang trong trạng thái auto hay không
	void restoreBackupAutoGoX();//Khôi phục trạng thái trước khi vào trạng thái Auto
	int getLives();
	void setLives(int l );
	int getScore();
	void setScore(int s);
	void setHeartCollect(int h);
	int getHeartCollect();

	int getHealth();

	void setDead();
	bool getIsDead();
	void setIsDead(bool dead);

	bool loseLife(); //thiết lập các thuộc tính sau khi SIMON mất mạng
};

#endif