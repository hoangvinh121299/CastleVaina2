#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "define.h"

class Camera
{
protected:
	float _xCam;
	float _yCam;

	float _xCamBackup;
	float _yCamBackup;
	float _boundaryLeftBackup;
	float _boundaryRightBackup;

	int _width;
	int _height;

	float _boundaryLeft; //giới hạn camera bên trái
	float _boundaryRight; // giới hạn camera bên phải

	float vx;
	DWORD dt;

	bool isAutoGoX; // Có đang ở chế độ tự động hay không
	float autoGoXDistance; //Khoảng cách cần tự động di chuyển theo trục x
	float autoGoxBackupX; // Vị trí Camera trước khi tự động di chuyển

	bool isAllowFollowSimon;
public:
	Camera(int w, int h);
	~Camera();

	void Update(DWORD dt);

	D3DXVECTOR2 TransForm(float, float);

	void SetPosition(float x, float y);
	float GetXCam();
	float GetYCam();
	int GetWidth();
	int GetHeight() :

		bool checkObjectInCamera(float x, float y, float w, float h);
		
		bool AllowFollowSimon();
		void setAllowFollowSimon(bool b);

		void setAutoGoX(float Distance, float Speed);//Tiết lập các thông số auto
		void stopAutoGoX();
		void getIsAutoX();

		void SetBoundary(float left, float right);//Set giới hạn biên cho Camera
		float getBoundaryRight();
		float getBoundaryLeft();

		void setPositionBackup(float x, float y);
		void RestorePosition();

		void setBoundaryBackup(float l, float r);
		void RestoreBoundary();
};
#endif