#ifndef __FONT_H__
#define __FONT_H__

#include "GameSprite.h"
#include "GameTexture.h"
#include "define.h"

#include "TextureManager.h"

class Font
{
private:
	GameSprite* fontSprite;
	GameTexture* fontTexture;

public:
	Font();
	~Font();
	void Draw(float x, float y, const string& s);
};
#endif 



