#pragma once
#ifndef __SCENEGAME_H__
#define __SCENGAME_H__
#include "Scence.h"
#include "Camera.h"
#include"GameSprite.h"
#include "Grid.h"
#include"Brick.h"
class SceneGame:public Scene
{
private:
	Camera *camera;
	Grid *gridGame;
	eType mapCurrent;
	vector<GameObject*>listObject;
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

};

#endif