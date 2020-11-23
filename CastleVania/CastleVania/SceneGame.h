#pragma once
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
class SceneGame:public Scene
{
private:
	Camera *camera;
	Grid *gridGame;
	objectType mapCurrent;
	vector<GameObject*>listObject;
	Simon *simon;
	Brick* birck;

	Map* tileMap;
	vector<GameObject*> listEnemy;
	vector<Weapon*> listWeaponOfEnemy;
	vector<Effect*> listEffect;
	vector<Item*> listItem;
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
	void checkCollision();
	void checkCollisionSimonWithHiddenObject();
	void checkCollisionWeaponWithObject(vector<GameObject*> listObj);

	Item* getNewItem(int id, objectType ObjectType, float x, float y);
};

#endif