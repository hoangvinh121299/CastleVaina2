#include "StairTop.h"



StairTop::StairTop(float X, float Y, int Direction)
{
	width = 50;
	height = 5;

	x = X - width / 2;
	y = Y;

	direction = Direction;
	ObjectType = objectType::STAIR_TOP;
	y -= height;
}

StairTop::~StairTop()
{
}

void StairTop::getBoundingBox(float& left, float& top, float& right, float& bottom)
{

	left = x;
	right = x + width;
	top = y;
	bottom = y + height;

}

void StairTop::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void StairTop::Render(Camera* camera)
{
	if (IS_DEBUG_RENDER_BBOX)
		renderBoundingBox(camera);
}
