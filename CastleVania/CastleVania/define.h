﻿#ifndef _DEFINE_H_
#define _DEFINE_H_
#include <fstream>
#include <string>
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <map>
#include "debug.h"
#include <algorithm>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdlib.h>
#include <iomanip>
#include <vector>
using namespace std;
#define COLOR_BLACK D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
#define COLOR_KEY D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f)

#define SCREEN_WIDTH 528
#define SCREEN_HEIGHT 480

#define IS_DEBUG_RENDER_BBOX isDebug_RenderBBox

#define COLOR_BACKGROUND_DEFAULT D3DCOLOR_XRGB(0, 0, 0) // Màu đen
#define TIME_LIMIT_WAIT_RESET_GAME 300 //Thời gian vẽ màn màu đen khi reset game

extern D3DXCOLOR D3DOLOR_BACKGROUND; // màu nền game

extern int isDebug_Untouchable;
extern int isDebug_RenderBBox;

enum eType
{
	// CÁC TRẠNG THÁI CỦA SIMON
	SIMON = 01,
	SIMON_TRANS = 02,
	SIMON_DEATH = 03,

	// object nền
	BRICK = 21,
	TEX_BRICK_MODEL_1 = 22,
	TEX_BRICK_MODEL_2 = 23,
	TEX_BRICK_MODEL_3 = 24,
	TEX_BRICK_TRANSPARENT = 25,
	GATE = 26,
	TEX_BRICK_MODEL_3_3_32 = 27,
	TEX_BRICK_MODEL_3_4_32 = 28,

	// object 
	TORCH = 41,
	OBJECT_HIDDEN = 42,
	CANDLE = 43,
	STAIR = 44,
	STAIR_BOTTOM = 47,
	STAIR_TOP = 48,

	// WEAPON
	MORNINGSTAR = 61,
	DAGGER = 62,
	HOLYWATER = 63,
	STOPWATCH = 64,
	FIREBALL = 65,
	THROWINGAXE = 66,
	NON_WEAPON_COLLECT = 67,
	BOOMERANG = 68,
	WEAPON_DOUBLE_SHOT = 69,

	//ITEM
	LARGEHEART = 81,
	UPGRADEMORNINGSTAR = 82,
	ITEMDAGGER = 83,
	BONUS = 84,
	SMALLHEART = 85,
	ITEMHOLYWATER = 86,
	CRYSTALBALL = 88,
	POTROAST = 87,
	ITEMTHROWINGAXE = 89,
	INVINSIBILTYPOTION = 90,
	CROSS = 91,
	ITEMBOOMERANG = 92,
	ITEMDOUBESHOT = 93,
	MONEY_BAG_RED = 94,
	MONEY_BAG_WHITE= 95,
	MONEY_BAG_PURPLE = 96,

	//OTHER
	FONT = 101,
	BOARD = 102,
	BOARDHEALTH = 103,
	MAP1= 104,
	RENDERBBOX = 105,
	MAP2= 106,
	BOARD_TRANS = 107,

	//EFFECT
	FIRE  =121,
	HIT = 122,
	BROKENBRICK = 123,
	STEAM =124,
	EFFECT_MONEY_700 = 125,
	EFFECT_MONEY_100 = 126,
	EFFECT_MONEY_400 = 127,
	EFFECT_MONEY_1000 = 128,
	
	//ENEMY
	GHOST = 141,
	PANTHER = 142,
	BAT = 143,
	FISHMEN= 144,
	
	//BOSS
	PHANTOMBAT = 161,
	
	//INTRO
	MAINMENU = 181,
	INTRO_GO_SCENE1 = 182,
	INTRO_BAT_MENU = 143, // CON DƠI LÚC Ở GAME
	INTRO_BAT = 185, //CON DƠI LÚC VÀO GAME
	HELICOPTER = 184 // MÁY BAT TRỰC THĂNG LÚC VÀO GAME
};
typedef D3DXVECTOR3 GVector3;
typedef D3DXVECTOR2 GVector2;
#define VECTOR2ZERO Gvector2(0.0f, 0.0f);

#define GAMEOVER_SELECT_CONTINUE 0
#define GAMEOVER_SELECT_END 1

//#ifndef CHECK_OBJECT_IN_CAMERA // Kiểm tra GameObject có nằm trong camera ko?
//#define CHECK_OBJECT_IN_CAMERA(obj) \
//checkObjectInCamera(obj->GetX(), obj->GetY(), (float)obj->GetWidth(),  (float)obj->GetHeight())
//#endif
//
//
//#ifndef SAFE_DEL	ETE
//#define SAFE_DELETE(ptr) \
//if(ptr) \
//{\
//	delete (ptr); \
//	ptr = nullptr; \
//} \
//
//#endif
#endif // !__DEFINE_H__