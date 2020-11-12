#include "HiddenObject.h"

HiddenObject::HiddenObject(float x, float y, float w, float h)
{
	this->x = x;
	this->y = y;
	width = w;
	height = h;
	ObjectType = objectType::OBJECT_HIDDEN;
	id = 0;
	health = 1;
}

HiddenObject::~HiddenObject()
{

}
void HiddenObject::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = this->x;
	top = this->y;
	right = this->x + width;
	bottom = this->y + height;
}
void HiddenObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}
void HiddenObject::Render(Camera* camera)
{
	if (IS_DEBUG_RENDER_BBOX)
		renderBoundingBox(camera);
}