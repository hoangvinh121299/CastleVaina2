#pragma once
#ifndef __ITEM_H__
#define __ITEM_H__

#include "GameSprite.h"
#include "Camera.h"
#include "GameTexture.h"
#include "GameObject.h"
#include "define.h"
class Item:public GameObject
{
protected:
	DWORD timeDisplayMax; //Thời gian hiển thị tối đa
	DWORD timeDisplayed; //Thời gian đã hiển thị 
	
	DWORD timeWaitMax; //Thời gian chời tối đa trước khi hiển thị
	DWORD timeWaited; //Thời gian đã chờ 

	bool isFinish; //Đã kết thúc hay chưa

public:
	Item();
	virtual ~Item();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* listObject=NULL);
	virtual void Render(Camera *camera);
	virtual bool isWaitingToDisplay(); //Khoảng thời gian chờ để SIMON không ăn được

	bool getFinish();
	void setFinish(bool temp);
};
#endif
