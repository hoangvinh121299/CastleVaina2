#ifndef __GRID_H__
#define __GRID_H__

#include "Game.h"
#include "GameSprite.h"
#include "define.h"
#include "GameObject.h"
#include "Brick.h"

using namespace std;
#define GRID_CELL_WIDTH (SCREEN_WIDTH /4.0f)
#define GRID_CELL_HEIGHT (SCREEN_HEIGHT/4.0f)

#define GRID_MAP_CELL_MAX_COLLUM 100//Số lượng hàng tối đa chứa các cell trong map
#define GRID_MAP_CELL_MAX_ROW 20 //Số lượng hàng tối đa chưa các cell trong map
class Grid
{
private:
	vector<LPGAMEOBJECT> mapCells[GRID_MAP_CELL_MAX_ROW][GRID_MAP_CELL_MAX_COLLUM]; // Ma trận chứa các cell trong map
	char *objectFilePath;
public:
	Grid();
	~Grid();

	void setObjectFilePath(char*objectFilePath);
	void reloadMapGrid();

	GameObject * createNewGridObject(int objectType, float x, float y, float objectWidth, int objectHeight, int brickModel);
	void insertObjectToGrid(int objectID, int ObjectTye, int objectDirection, float x, float y, int objectWidth, int objectHeight, int brickModel);
	void getListObjectFromMapGrid(vector<GameObject*> &objectsList, Camera *camera);
};

#endif