#include "Camera.h"


Camera::Camera(int w, int h)
{
	_width = w;
	_height = h;
	isAllowFollowSimon = true;
	isAutoGoX = false;

	//Biên mặc định ban đầu là kích thước map
	_boundaryLeft = 0;
	_boundaryRight = 0;
	_xCamBackup = _yCamBackup = 0;
	setBoundaryBackup(_boundaryLeft, _boundaryRight);
	vx = 0;
}
Camera::~Camera()
{

}
void Camera::Update(DWORD dt)
{
	this->dt = dt;
	if (isAutoGoX == true)
	{
		float dx = vx * dt;
		_xCam += dx;
	}
	if ()
}