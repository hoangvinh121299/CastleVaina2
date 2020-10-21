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
GameObject * createNewGridObject(int objectType, float x, float y, float objectWidth, int objectHeight, int brickModel)
{
	switch (objectType)
	{
	case eType::BRICK:

	}
}