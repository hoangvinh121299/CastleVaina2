#ifndef __MAP_H__
#define __MAP_H__

#include "TextureManager.h"
#include "GameSprite.h"
#include "define.h"
class Map
{
private:
	GameTexture* _texture;
	GameSprite* _sprite;

	int columnTile, rowTile, totalTiles;
	int columnMap, rowMap;
	int heightBoard; // chiều cao board
	int titleMap[500][500];
public:
	Map();
	~Map();
	void loadMap(objectType type);
	void readMapTxt(char * filename);
	void drawMap(Camera* camera);

	int getMapWidth();
	int getMapHeight();
};

#endif