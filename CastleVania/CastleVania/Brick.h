#ifndef __BRICK_H__
#define __BRICK_H_
#include "GameObject.h"
#include "TextureManager.h"
#define BRICK_MODEL_1 1 // GẠCH LOẠI 1 , 32PX
#define BRICK_MODEL_2 2 // GẠCH LOẠI 2, 32PX
#define BRICK_MODEL_3 3 // GẠCH MÀN 3, Ô NHỎ 16PX
#define BRICK_MODEL_TRANSPARENT 4 // GẠCH LOẠI TRONG SUỐT
#define BRICK_MODEL_3_3_32 5// GẠCH LOẠI 3 VIÊN LOẠI 3
#define BRICK_MODEL_3_4_32 6// gACG5 LOẠI 4 VIÊN LOẠI 3
class Brick: public GameObject
{
protected:
	int width;
	int height;
	int model;
public:
	Brick(float X, float Y, int W, int H, int Model);
	virtual void Render(Camera *camera);
	virtual void getBoundingBox(float &l, float &t, float &r, float &b);
	int getModel();
};

#endif