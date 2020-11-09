#include "Map.h"

Map::Map()
{

}
Map::~Map()
{
	SAFE_DELETE(_sprite);
}

void Map::loadMap(objectType type)
{
	switch (type)
	{
	case objectType::MAP1:
		readMapTxt((char*)"Resources/Map/Map_1/readfile_map_1.txt");
		break;
	case objectType::MAP2:
		readMapTxt((char*)"Resources/map/readfile_map_2.txt");
		break;
	default:
		DebugOut(L"[MAP] Load map that bai!");
		return;
		break;
	}
	_texture = TextureManager::GetInstance()->GetTexture(type);
	_sprite = new GameSprite(_texture, 100);
}

void Map::readMapTxt(char* filename)
{
	ifstream inp(filename, ios::in);
	inp >> rowMap >> columnMap >> columnTile >> rowTile >> totalTiles >> heightBoard;
	for (int i = 0; i < rowMap; i++)
		for (int j = 0; j < columnMap; j++)
			inp >> titleMap[i][j];
	inp.close();
}
void Map::drawMap(Camera* camera)
{
	int row = (int)(camera->GetYCam()) / _texture->GetFrameWidth();
	int column = (int)(camera->GetXCam()) / _texture->GetFrameHeight();

	float x = -(float)((int)(camera->GetXCam()) % _texture->GetFrameHeight());
	float y = -(float)((int)(camera->GetYCam()) % _texture->GetFrameHeight());

	for (int i = 0; i < SCREEN_HEIGHT / _texture->GetFrameHeight() + 1; i++)
	{
		for (int j = 0; j < SCREEN_WIDTH / _texture->GetFrameWidth() + 1; j++)
		{
			if (!(row + 1 < 0 || row + i >= rowMap || j + column<0 || j + column>columnMap))
			{
				_sprite->DrawFrame(titleMap[row + i][column + j], x + _texture->GetFrameWidth() * j, y + _texture->GetFrameHeight() * i + heightBoard);
			}
		}
	}
}
int Map::getMapHeight()
{
	return columnMap * _texture->GetFrameHeight();
}
int Map::getMapWidth()
{
	return columnMap * _texture->GetFrameWidth();
}