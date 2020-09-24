// Lớp quản lý Game Texture
#ifndef __CTEXTURE_H__
#define __CTEXTURE_H__

#include "define.h"
#include "Game.h"
#include "debug.h"
class GameTexture
{
private:
	int frameWidth, frameHeight, Column, Row;
public:
	int TotalFrame;
	LPDIRECT3DTEXTURE9 Texture;

	int GetFrameWidth();
	int GetFrameHeight();
	int GetColumn();
	int GetRow();

	GameTexture(const char* filePath,
				int column=1,
				int row =1,
				int totalFrames=1,
				int R= 255,
				int G=0,
				int B=255);
	~GameTexture();
};

#endif // !__CTEXTURE_H__