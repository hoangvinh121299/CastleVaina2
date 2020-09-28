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
	if (isAutoGoX == true)
	{
		if (abs(_xCam - autoGoxBackupX) >= autoGoXDistance)
		{
			_xCam = _xCam - (abs(_xCam - autoGoxBackupX) - autoGoXDistance);
			isAutoGoX = false;
		}
	}
	if (_xCam < _boundaryLeft)
		_xCam = _boundaryLeft;
	if (_xCam > _boundaryRight)
		_xCam = _boundaryRight;
}
D3DXVECTOR2 Camera::TransForm(float xWorld, float yWorld)
{
	return D3DXVECTOR2(xWorld - _xCam, yWorld - _yCam);

}
void Camera::SetPosition(float x, float y)
{
	_xCam = x;
	_yCam = y;
}
float Camera::GetXCam()
{
	return _xCam;
}
float Camera::GetYCam()
{
	return _yCam;
}
int Camera::GetHeight()
{
	return _height;
}
int Camera::GetWidth()
{
	return _width;
}
bool Camera::checkObjectInCamera(float x, float y, float w, float h)
{
	if (x + w < _xCam || _xCam + _width < x)
		return false;
	if (y + h < _yCam || _yCam + _height < y)
		return false;
	return true;
}
bool Camera::AllowFollowSimon()
{
	return isAllowFollowSimon;
}
void Camera::setAutoGoX(float Distance, float Speed)
{
	if (isAutoGoX == true)
		return;
	vx = Speed;
	autoGoxBackupX = _xCam;
	autoGoXDistance = Distance;
	isAutoGoX = true;
	isAllowFollowSimon = false;
}
void Camera::stopAutoGoX()
{
	isAutoGoX = false;
}
bool Camera::getIsAutoX()
{
	return isAutoGoX;
}
float Camera::getBoundaryLeft()
{
	return _boundaryLeft;
}
float Camera::getBoundaryRight()
{
	return _boundaryRight;
}
void Camera::setPositionCamBackup(float x, float y)
{
	_xCamBackup = x;
	_yCamBackup = y;
}
void Camera::setBoundaryBackup(float l, float r)
{
	_boundaryLeftBackup = l;
	_boundaryRightBackup = r;
}
void Camera::RestoreBoundary()
{
	_boundaryLeft = _boundaryLeftBackup;
	_boundaryRight = _boundaryRightBackup;
}
void Camera::RestorePosition()
{
	_xCam = _xCamBackup;
	_yCam = _yCamBackup;
	_boundaryLeft = _boundaryLeftBackup;
	_boundaryRight = _boundaryRightBackup;
}
void Camera::SetBoundary(float left, float right)
{
	_boundaryLeft = left;
	_boundaryRight = right;
}
void Camera::setAllowFollowSimon(bool temp)
{
	isAllowFollowSimon = temp;
}