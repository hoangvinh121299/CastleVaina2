// Lớp quản lý Game Sprite
#ifndef __GAMESPRITE_H__
#define __GAMESPRITE_H__

#include "GameTexture.h"
class GameSprite
{
private:
	LPD3DXSPRITE spriteHandler;
	int currentFrame;
	int totalFrames;

public:
	GameSprite(GameTexture * Texture, DWORD timeAnimation);
	virtual ~GameSprite(); //Phương thức thuần ảod
	GameTexture * texture;
	//Quản lý thời gian chuyển giữa các sprite
	DWORD timeAccumulated; // Thời gian chờ đã tích luỹ
	DWORD timeAnimation; // Thời gian phải chời giữa các frame
	RECT getRectFrame(int idFrame);
	void Next();
	void ResetTime();
	void SelectFrame(int idFrame);
	void Update(DWORD dt);
	void Draw(
		float x,
		float y,
		int alpha = 255,
		int R = 255,
		int G = 255,
		int B = 255
	);
	void DrawFrame(
		int idframe,
		float x,
		float y,
		int alpha = 255,
		int R = 255,
		int G = 255,
		int B = 255
	);
	void DrawFlipX(
		float X,
		float Y,
		int alpha = 255,
		int R = 255,
		int G = 255,
		int B = 255
		);
	void DrawFrameFlipX(
		int idFrame,
		float X,
		float Y,
		int alpha = 255,
		int R = 255,
		int G = 255,
		int B = 255
	);
	int getCurrentFrame();
	int getTotalFrames();
};

#endif
