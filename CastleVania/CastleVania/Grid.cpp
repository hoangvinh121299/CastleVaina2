#include "Grid.h"

Grid::Grid()
{

}
Grid::~Grid()
{
	//Vòng lặp giải phòng vùng nhớ của Grid
	for (int i = 0; i < GRID_MAP_CELL_MAX_ROW; i++)
	{
		for (int j = 0; j < GRID_MAP_CELL_MAX_COLLUM; j++)
			mapCells[i][j].clear();
	}
}
void Grid::setObjectFilePath(char* filePath)
{
	objectFilePath = filePath;
}
void Grid::reloadMapGrid()
{
	//Reset giá trị của vector chưa Grid về lại mảng rỗng
	for (int i = 0; i < GRID_MAP_CELL_MAX_ROW; i++)
	{
		for (int j = 0; j < GRID_MAP_CELL_MAX_COLLUM; j++)
			mapCells[i][j].clear();
	}
	
	float x, y;
	int objectID, objectType, objectDirection, objectHeight, objectWidth, brickModel, numberofObjects;
	ifstream fileInfo(objectFilePath, ios::in);
	fileInfo >> numberofObjects;
	for (int i=0;i<numberofObjects;i++)
		for (int i = 0; i < numberofObjects; i++)
		{
			
			fileInfo >> objectID >> objectType >> objectDirection >> x >> y >> objectWidth >> objectHeight >> brickModel;
			insertObjectToGrid(objectID, objectType, objectDirection, x, y, objectWidth, objectHeight, brickModel);
		}
	fileInfo.close();
}
GameObject * Grid::createNewGridObject(int objectType, float x, float y, float objectWidth, int objectHeight, int brickModel)
{
	switch (objectType)
	{
	case eType::BRICK:
		return new Brick(x, y, objectWidth, objectHeight, brickModel);
	}
	return NULL;
}
void Grid::getListObjectFromMapGrid(vector <GameObject*> & listObject, Camera*camera)
{
	listObject.clear();
	unordered_map<int, GameObject*> mapObject;
	int bottom = (int)((camera->GetYCam() + camera->GetHeight() - 1) / GRID_CELL_HEIGHT);
	int top = (int)((camera->GetYCam() + 1) / GRID_CELL_HEIGHT);
	
	int left = (int)((camera->GetXCam() + 1) / GRID_CELL_WIDTH);
	int right = (int)((camera->GetXCam() + camera->GetWidth() - 1) / GRID_CELL_WIDTH );

	for (int i = top; i <= bottom; i++)
	{
		for (int j = left; j <= right; j++)
		{
			for (UINT k = 0; k < mapCells[i][j].size(); k++)
			{
				if (mapCells[i][j].at(k)->getHealth() > 0) // Còn tồn tại trên bản đồ 
				{
					if (mapObject.find(mapCells[i][j].at(k)->getID()) == mapObject.end())
						mapObject[mapCells[i][j].at(k)->getID()] = mapCells[i][j].at(k);
				}
			}
		}
	}
	for (auto& x : mapObject)
	{
		listObject.push_back( x.second);
	}
}
void Grid::insertObjectToGrid(int objectID, int ObjectTye, int objectDirection, float x, float y, int objectWidth, int objectHeight, int brickModel)
{
	int top = (int)(y / GRID_CELL_HEIGHT);
	int bottom = (int)((y + objectHeight) / GRID_CELL_HEIGHT);

	int left = (int)(x / GRID_CELL_WIDTH);
	int right = (int)((x + objectWidth) / GRID_CELL_WIDTH);

	GameObject* obj = createNewGridObject(ObjectTye, x, y, objectWidth, objectHeight, brickModel);

	if (obj == NULL)
		return;
	obj->setID(objectID);
	obj->setDirection(objectDirection);

	for (int i = top; i <= bottom; i++)
		for (int j = left; j <= right; j++)
			mapCells[i][j].push_back(obj);

}