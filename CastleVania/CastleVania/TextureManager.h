#ifndef _TEXTUREMANAGER_H__
#define _TEXTUREMANAGER_H__

#include <unordered_map>
#include "define.h"
#include "GameTexture.h"
class TextureManager
{
	// Thuộc tính ... 
	unordered_map<eType, GameTexture*> _ArrTextures;
public:
	// Tạo một đối tượng để quản lý các thuộc tính và phương thức của Texture Manager
	static TextureManager* __Instance;
	// Phương thức để tạo một đối tượng instance
	static TextureManager* GetInstance();
	
	void AddTexture(eType type, GameTexture* Texture);
	GameTexture* GetTexture(eType trype);

	void LoadResource();	

	TextureManager();
	~TextureManager();
};
#endif