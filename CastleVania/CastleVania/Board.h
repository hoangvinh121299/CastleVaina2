#ifndef __BOARD_H__
#define __BOARD_H__

#include "GameSprite.h"
#include "GameTexture.h"
#include "Camera.h"
#include "define.h"
#include "Font.h"
#include "Simon.h"
#include "TextureManager.h"
#include "Dagger.h"
#include "BoardHealth.h"
#define BOARD_DEFAULT_POSITION_X 0.0f
#define BOARD_DEFAULT_POSITION_Y 0.0f

class Board
{
private:
	Font _font;

	GameTexture *boardTexture;
	GameSprite *boardsprite;
	BoardHealth* _boardHealth;
	float x, y;

	string fillNumber(string s, UINT MaxNumber);


	GameSprite* spriteIconDoubleShot;

public:
	Board(float X, float Y);
	void Render(Simon* simon, int state, int RemainingTime, GameObject* boss);
	~Board();

	void SetTexture(GameTexture* texture);
};





#endif 


