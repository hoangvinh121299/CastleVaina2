#include "StairBottom.h"

StairBottom::StairBottom(float X, float Y, int Direction)
{
	x = X - 25;
	y = Y;
	width = 50;
	height = 50;
	direction = Direction;
	ObjectType = objectType::STAIR_BOTTOM;
	y -= width;
}

StairBottom::~StairBottom()
{
}

void StairBottom::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	right = x+width ;
	top = y;
	bottom = y+height;
}

void StairBottom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void StairBottom::Render(Camera* camera)
{
	if (IS_DEBUG_RENDER_BBOX)
		renderBoundingBox(camera);
}
