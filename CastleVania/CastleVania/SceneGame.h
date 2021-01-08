﻿#pragma once
#ifndef __SCENEGAME_H__
#define __SCENGAME_H__
#include "Scence.h"
#include "Camera.h"
#include"GameSprite.h"
#include "Grid.h"
#include"Brick.h"
#include "Simon.h"
#include "debug.h"
#include "Ghost.h"
#include "Panther.h"
#include "Bat.h"
#include "Fishmen.h"
#include "Map.h"
#include "HiddenObject.h"
#include "Effect.h"
#include "EffectHit.h"
#include "EffectFire.h"
#include "Item.h"
#include "LargeHeart.h"
#include "ItemDagger.h"
#include "UpgradeMorningStar.h"
#include "MoneyBag.h"
#include "Dagger.h"
#include "EffectMoney.h"
#include "MoneyBagExtra.h"
#include "Candle.h"
#include "Gate.h"
#include "SmallHeart.h"
#include "Board.h"
#include "brokenBrick.h"
#include "PotRoast.h"
#include "Gametime.h"
#include "Sound.h"
#include "BoomerangItem.h"
#include "Boomerang.h"
#include "StopWatchItem.h"
#include "StopWatch.h"
#include "ThrowingAxeItem.h"
#include "ThrowingAxe.h"
#include "HolyWaterItem.h"
#include "HolyWater.h"
#define GAME_TIME_MAX 300
#include "PhantomBat.h"

#define GAME_TIME_MAX 3000
#define CAMERA_POSITION_Y_LAKE 400.0f

#define CAMERA_BOUNDARY_LAKE_LEFT 3075.0f
#define CAMERA_BOUNDARY_LAKE_RIGHT (4111.0f-SCREEN_WIDTH)
#define GRID_INSERT_OBJECT__GETOUTFROMLAKE_LEFT   78, objectType::OBJECT_HIDDEN, -1, 3140, 440, 20, 20, 0 //Đi ra khỏi hồ bên trái
#define GRID_INSERT_OBJECT__GETINTOLAKE_LEFT      77, objectType::OBJECT_HIDDEN, -1, 3190, 423, 40, 10, 0 //Đi xuống hồ bên trái
#define GRID_INSERT_OBJECT__GETINTOLAKE_RIGHT     79, objectType::OBJECT_HIDDEN, -1, 3850, 423, 25, 10, 0 //Đi xuống hồ bên phải 
#define GRID_INSERT_OBJECT__GETOUTFROMLAKE_RIGHT  80, objectType::OBJECT_HIDDEN, -1, 3780, 435, 30, 20, 0 //Đi ra khỏi hồ bên phải

#define GATE1_POSTION_CAM_BEFORE_GO 2809.0f
#define GATE1_POSITION_CAM_AFTER_GO 3073.0f

#define GATE2_POSTION_CAM_BEFORE_GO 3840.0f
#define GATE2_POSITION_CAM_AFTER_GO 4095.0f

#define CAMERA_BOUNDARY_BOSS_RIGHT (5648.0f - SCREEN_WIDTH)
#define DISTANCE_AUTOGO_SIMON_GATE 80.0f //Simon auto 80 sau khi đụng vào gate
#define CAMERA_BOUNDARY_BEFORE_GO_GATE1_RIGHT (2555.0f) // Biên phải camera trước khi qua cửa 1
class SceneGame:public Scene
{
private:
	Camera *camera;
	Grid *gridGame;
	objectType mapCurrent;
	vector<GameObject*>listObject;
	Simon *simon;
	PhantomBat* phantomBat;
	Brick* birck;
	Sound* sound;
	Map* tileMap;
	vector<GameObject*> listEnemy;
	vector<Weapon*> listWeaponOfEnemy;
	vector<Effect*> listEffect;
	vector<Item*> listItem;
	Board *board1;
	Gametime* gametime;
	int currentStage;
	//Xử lý đi qua cổng 1 của map 2 
	bool isWalkingThroughGate1;
	bool doneWalkingThroughGate1;
	//Xử lý đi qua cổng 2 map 2
	bool isWalkingThroughGate2;
	bool doneWalkingThroughGate2;
	int directionPanther = -1;
	/* xử lí chờ vẽ màn đen khi bắt đầu lại game*/
	bool isWaitResetGame;
	DWORD TimeWaitedResetGame;

	/* Xử lí gameover*/
	bool isGameOver;
	Font Text;

	GameSprite* _spriteLagerHeart;
	int GameOverSelect;
public:
	SceneGame();
	~SceneGame();

	void KeyState(BYTE * state);
	void OnKeyDown(int keycode);
	void OnKeyUp(int keycode);
	void LoadResources();

	void InitGame(); //Khởi tại trạng thái ban đầu của game
	void resetResources(); // reset lại các resource khi Simon mất 1 mạng
	
	void Update(DWORD dt);
	void Render();
	void loadMap(objectType mapCurrent);
	//Kiểm tra va chạm 
	void checkCollision();
	void checkCollisionSimonWithHiddenObject();
	void checkCollisionWeaponWithObject(vector<GameObject*> listObj);
	void checkCollionsionSimonWithItem();
	void checkCollsionWithEnemy();
	void checkCollisionSimonWithEnemy();
	void checkCollisionSimonWithGate();
	void checkCollisionSimonWithBoss();
	Item* getNewItem(int id, objectType ObjectType, float x, float y);
	void replayMusic();
};

#endif