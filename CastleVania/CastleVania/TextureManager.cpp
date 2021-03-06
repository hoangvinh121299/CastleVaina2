﻿#include "TextureManager.h"
TextureManager*  TextureManager::__Instance = NULL;

TextureManager* TextureManager::GetInstance()
{
	if (__Instance == NULL)
		__Instance = new TextureManager();
	return __Instance;
}
//Phương thức nạp textures
void TextureManager::AddTexture(objectType type, GameTexture *texture)
{
	_ArrTextures[type] = texture;
}

GameTexture* TextureManager::GetTexture(objectType type)
{
	return _ArrTextures[type];
}
//Phương thức nạp tất cả các textures
void TextureManager::LoadResource()
{
	// Intro
	AddTexture(objectType::MAINMENU, new GameTexture("Resources/Intro/mainmenu.png"));
	AddTexture(objectType::INTRO_BAT, new GameTexture("Resources/Intro/intro_bat.png", 2, 1, 2));
	AddTexture(objectType::INTRO_BAT_MENU, new GameTexture("Resources/Intro/IntroBatMenu.png", 5, 3, 15));
	AddTexture(objectType::INTRO_GO_SCENE1, new GameTexture("Resources/Intro/intro_go_scene_1.png"));
	AddTexture(objectType::HELICOPTER, new GameTexture("Resources/Intro/helicopter.png"));

	//board
	AddTexture(objectType::FONT, new GameTexture("Resources/Font/1.png", 13, 3, 37));

	AddTexture(objectType::BOARD, new GameTexture("Resources/Board/blackboard.png", 1, 1, 1));
	AddTexture(objectType::BOARD_TRANS, new GameTexture("Resources/Board/blackboard.png", 1, 1, 1, 0, 0, 0));

	AddTexture(objectType::BOARDHEALTH, new GameTexture("Resources/Board/heal.png", 3, 1, 3));
	AddTexture(objectType::RENDERBBOX, new GameTexture("Resources/bbox.png")); // dùng để vẽ BBOX

	//MAP
	AddTexture(objectType::MAP1, new GameTexture("Resources/Map/Map_1/tileset_map1.png", 8, 4, 32));
	AddTexture(objectType::MAP2, new GameTexture("Resources/Map/Map_2/tileset_map2.png", 22, 4, 88));


	//gameobject ground
	AddTexture(objectType::TEX_BRICK_MODEL_1, new GameTexture("Resources/ground/2.png")); // loại dành cho state 1
	AddTexture(objectType::TEX_BRICK_MODEL_2, new GameTexture("Resources/ground/2-2.png")); // dành cho state 2
	AddTexture(objectType::TEX_BRICK_MODEL_3, new GameTexture("Resources/ground/8.png")); // loại nhỏ
	AddTexture(objectType::TEX_BRICK_TRANSPARENT, new GameTexture("Resources/ground/brick_transparent.png")); // loại trong suốt

	AddTexture(objectType::TEX_BRICK_MODEL_3_3_32, new GameTexture("Resources/ground/8-2.png")); // loại nhỏ 4 ô
	AddTexture(objectType::TEX_BRICK_MODEL_3_4_32, new GameTexture("Resources/ground/8-1.png")); // loại nhỏ 4 ô





	AddTexture(objectType::GATE, new GameTexture("Resources/ground/Gate1.png", 4, 1, 4));

	AddTexture(objectType::TORCH, new GameTexture("Resources/ground/0.png", 2, 1, 2));
	AddTexture(objectType::CANDLE, new GameTexture("Resources/ground/1.png", 2, 1, 2));

	//item
	AddTexture(objectType::ITEMDAGGER, new GameTexture("Resources/Item/4.png"));
	AddTexture(objectType::LARGEHEART, new GameTexture("Resources/Item/1.png"));
	AddTexture(objectType::UPGRADEMORNINGSTAR, new GameTexture("Resources/Item/3.png"));
	AddTexture(objectType::BONUS, new GameTexture("Resources/Item/2.png", 3, 1, 3));
	AddTexture(objectType::SMALLHEART, new GameTexture("Resources/Item/0.png"));
	AddTexture(objectType::ITEMHOLYWATER, new GameTexture("Resources/Item/9.png"));
	AddTexture(objectType::POTROAST, new GameTexture("Resources/Item/10.png"));
	AddTexture(objectType::CRYSTALBALL, new GameTexture("Resources/Item/13.png", 2, 1, 2));
	AddTexture(objectType::ITEMTHROWINGAXE, new GameTexture("Resources/Item/7.png"));
	AddTexture(objectType::INVINSIBILTYPOTION, new GameTexture("Resources/Item/14.png"));
	AddTexture(objectType::CROSS, new GameTexture("Resources/Item/6.png"));
	AddTexture(objectType::ITEMBOOMERANG, new GameTexture("Resources/Item/8.png"));
	AddTexture(objectType::ITEMDOUBESHOT, new GameTexture("Resources/Item/11.png"));

	// Weapon
	AddTexture(objectType::DAGGER, new GameTexture("Resources/weapon/1.png"));
	AddTexture(objectType::MORNINGSTAR, new GameTexture("Resources/Weapon/morningstar.png", 4, 3, 12));
	AddTexture(objectType::HOLYWATER, new GameTexture("Resources/weapon/2.png", 4, 1, 4));
	AddTexture(objectType::STOPWATCH, new GameTexture("Resources/item/5.png"));
	AddTexture(objectType::FIREBALL, new GameTexture("Resources/Weapon/fireball.png",1,1,1));
	AddTexture(objectType::THROWINGAXE, new GameTexture("Resources/weapon/3.png", 4, 1, 4));
	AddTexture(objectType::BOOMERANG, new GameTexture("Resources/weapon/4.png", 3, 1, 3));

	//SIMON
	AddTexture(objectType::SIMON, new GameTexture("Resources/Simon/simon.png", 8, 3, 24));
	AddTexture(objectType::SIMON_TRANS, new GameTexture("Resources/Simon/simon_trans.png", 8, 3, 24));
	AddTexture(objectType::SIMON_DEATH, new GameTexture("Resources/Simon/simondeath.png"));

	//effect
	AddTexture(objectType::FIRE, new GameTexture("Resources/Effect/1.png", 4, 1, 4));
	AddTexture(objectType::HIT, new GameTexture("Resources/Effect/0.png", 2, 1, 2));
	AddTexture(objectType::BROKENBRICK, new GameTexture("Resources/Effect/BrokenBrick.png", 2, 1, 2));
	AddTexture(objectType::STEAM, new GameTexture("Resources/Effect/2.png"));
	AddTexture(objectType::EFFECT_MONEY_700, new GameTexture("Resources/Effect/effect700.png", 2, 1, 2));
	AddTexture(objectType::EFFECT_MONEY_100, new GameTexture("Resources/Effect/effect100.png", 2, 1, 2));
	AddTexture(objectType::EFFECT_MONEY_1000, new GameTexture("Resources/Effect/effect1000.png", 2, 1, 2));
	AddTexture(objectType::EFFECT_MONEY_400, new GameTexture("Resources/Effect/effect400.png", 2, 1, 2));

	//Enemy
	AddTexture(objectType::GHOST, new GameTexture("Resources/Enemy/1.png", 2, 1, 2));
	AddTexture(objectType::PANTHER, new GameTexture("Resources/Enemy/2.png", 4, 1, 4));
	AddTexture(objectType::BAT, new GameTexture("Resources/Enemy/0.png", 4, 1, 4));
	AddTexture(objectType::FISHMEN, new GameTexture("Resources/Enemy/3.png", 3, 1, 3));

	//boss
	AddTexture(objectType::PHANTOMBAT, new GameTexture("Resources/Boss/0.png", 3, 1, 3));

}
TextureManager::TextureManager()
{
	LoadResource();
}
TextureManager::~TextureManager()
{
	SAFE_DELETE(__Instance);
}