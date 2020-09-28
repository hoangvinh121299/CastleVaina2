#ifndef __GAMETIME_H__
#define __GAMETIME_H__

#include "define.h"
class Gametime
{
private:
	DWORD _accumulationnTime; // Thời gian đã tích luỹ
	int _time; //time game
	bool isTimeChanged; // biến cờ hiệu kiểm tra xem biến _time có phải vừa được cập nhập hay không
public:
	Gametime();
	~Gametime();
	void Update(DWORD dt);
	void setTime(int t);
	int getTime();
	bool checkIsTimeChanged();
};

#endif