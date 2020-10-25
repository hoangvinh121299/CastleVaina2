#include "TextureManager.h"
TextureManager*  TextureManager::__Instance = NULL;

TextureManager* TextureManager::GetInstance()
{
	if (__Instance == NULL)
		__Instance = new TextureManager();
	return __Instance;
}
//Phương thức nạp textures
void TextureManager::AddTexture(eType type, GameTexture *texture)
{
	_ArrTextures[type] = texture;
}

GameTexture* TextureManager::GetTexture(eType type)
{
	return _ArrTextures[type];
}
//Phương thức nạp tất cả các textures
void TextureManager::LoadResource()
{
	//// Intro
	//AddTexture(eType::MAINMENU, new GameTexture("Resources/mainmenu.png"));
	//AddTexture(eType::INTRO_BAT, new GameTexture("Resources/intro_bat.png", 2, 1, 2));
	//AddTexture(eType::INTRO_BAT_MENU, new GameTexture("Resources/IntroBatMenu.png", 5, 3, 15));
	//AddTexture(eType::INTRO_GO_SCENE1, new GameTexture("Resources/intro_go_scene_1.png"));
	//AddTexture(eType::HELICOPTER, new GameTexture("Resourc	es/helicopter.png"));

	//board
	//AddTexture(eType::FONT, new GameTexture("Resources/font/1.png", 13, 3, 37));

	//AddTexture(eType::BOARD, new GameTexture("Resources/blackboard.png", 1, 1, 1));
	//AddTexture(eType::BOARD_TRANS, new GameTexture("Resources/blackboard.png", 1, 1, 1, 0, 0, 0));

	//AddTexture(eType::BOARDHEALTH, new GameTexture("Resources/heal.png", 3, 1, 3));
	AddTexture(eType::RENDERBBOX, new GameTexture("Resources/bbox.png")); // dùng để vẽ BBOX

	//MAP
	AddTexture(eType::MAP1, new GameTexture("Resources/map/tileset_map1.png", 8, 4, 32));
	AddTexture(eType::MAP2, new GameTexture("Resources/map/tileset_map2.png", 22, 4, 88));


	//gameobject ground
	AddTexture(eType::TEX_BRICK_MODEL_1, new GameTexture("Resources/ground/2.png")); // loại dành cho state 1
	AddTexture(eType::TEX_BRICK_MODEL_2, new GameTexture("Resources/ground/2-2.png")); // dành cho state 2
	AddTexture(eType::TEX_BRICK_MODEL_3, new GameTexture("Resources/ground/8.png")); // loại nhỏ
	AddTexture(eType::TEX_BRICK_TRANSPARENT, new GameTexture("Resources/ground/brick_transparent.png")); // loại trong suốt

	AddTexture(eType::TEX_BRICK_MODEL_3_3_32, new GameTexture("Resources/ground/8-2.png")); // loại nhỏ 4 ô
	AddTexture(eType::TEX_BRICK_MODEL_3_4_32, new GameTexture("Resources/ground/8-1.png")); // loại nhỏ 4 ô





	AddTexture(eType::GATE, new GameTexture("Resources/ground/Gate1.png", 4, 1, 4));

	AddTexture(eType::TORCH, new GameTexture("Resources/ground/0.png", 2, 1, 2));
	AddTexture(eType::CANDLE, new GameTexture("Resources/ground/1.png", 2, 1, 2));

	//item
	AddTexture(eType::ITEMDAGGER, new GameTexture("Resources/item/4.png"));
	AddTexture(eType::LARGEHEART, new GameTexture("Resources/item/1.png"));
	AddTexture(eType::UPGRADEMORNINGSTAR, new GameTexture("Resources/item/3.png"));
	AddTexture(eType::BONUS, new GameTexture("Resources/item/2.png", 3, 1, 3));
	AddTexture(eType::SMALLHEART, new GameTexture("Resources/item/0.png"));
	AddTexture(eType::ITEMHOLYWATER, new GameTexture("Resources/item/9.png"));
	AddTexture(eType::POTROAST, new GameTexture("Resources/item/10.png"));
	AddTexture(eType::CRYSTALBALL, new GameTexture("Resources/item/13.png", 2, 1, 2));
	AddTexture(eType::ITEMTHROWINGAXE, new GameTexture("Resources/item/7.png"));
	AddTexture(eType::INVINSIBILTYPOTION, new GameTexture("Resources/item/14.png"));
	AddTexture(eType::CROSS, new GameTexture("Resources/item/6.png"));
	AddTexture(eType::ITEMBOOMERANG, new GameTexture("Resources/item/8.png"));
	AddTexture(eType::ITEMDOUBESHOT, new GameTexture("Resources/item/11.png"));

	// Weapon
	AddTexture(eType::DAGGER, new GameTexture("Resources/weapon/1.png"));
	AddTexture(eType::MORNINGSTAR, new GameTexture("Resources/weapon/morningstar.png", 4, 3, 12));
	AddTexture(eType::HOLYWATER, new GameTexture("Resources/weapon/2.png", 4, 1, 4));
	AddTexture(eType::STOPWATCH, new GameTexture("Resources/item/5.png"));
	AddTexture(eType::FIREBALL, new GameTexture("Resources/weapon/fireball.png"));
	AddTexture(eType::THROWINGAXE, new GameTexture("Resources/weapon/3.png", 4, 1, 4));
	AddTexture(eType::BOOMERANG, new GameTexture("Resources/weapon/4.png", 3, 1, 3));

	//SIMON
	AddTexture(eType::SIMON, new GameTexture("Resources/simon.png", 8, 3, 24));
	AddTexture(eType::SIMON_TRANS, new GameTexture("Resources/simon_trans.png", 8, 3, 24));
	AddTexture(eType::SIMON_DEATH, new GameTexture("Resources/simondeath.png"));

	//effect
	AddTexture(eType::FIRE, new GameTexture("Resources/other/1.png", 4, 1, 4));
	AddTexture(eType::HIT, new GameTexture("Resources/other/0.png", 2, 1, 2));
	AddTexture(eType::BROKENBRICK, new GameTexture("Resources/other/BrokenBrick.png", 2, 1, 2));//, 4,4,16));
	AddTexture(eType::STEAM, new GameTexture("Resources/other/2.png"));
	AddTexture(eType::EFFECT_MONEY_700, new GameTexture("Resources/other/effect700.png", 2, 1, 2));
	AddTexture(eType::EFFECT_MONEY_100, new GameTexture("Resources/other/effect100.png", 2, 1, 2));
	AddTexture(eType::EFFECT_MONEY_1000, new GameTexture("Resources/other/effect1000.png", 2, 1, 2));
	AddTexture(eType::EFFECT_MONEY_400, new GameTexture("Resources/other/effect400.png", 2, 1, 2));

	//enemy
	AddTexture(eType::GHOST, new GameTexture("Resources/enemy/1.png", 2, 1, 2));
	AddTexture(eType::PANTHER, new GameTexture("Resources/enemy/2.png", 4, 1, 4));

	AddTexture(eType::BAT, new GameTexture("Resources/enemy/0.png", 4, 1, 4));
	AddTexture(eType::FISHMEN, new GameTexture("Resources/enemy/3.png", 3, 1, 3));

	//boss
	AddTexture(eType::PHANTOMBAT, new GameTexture("Resources/boss/0.png", 3, 1, 3));

}
TextureManager::TextureManager()
{
	LoadResource();
}
TextureManager::~TextureManager()
{
	SAFE_DELETE(__Instance);
}