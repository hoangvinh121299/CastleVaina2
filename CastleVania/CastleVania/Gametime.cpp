#include "Gametime.h"

Gametime::Gametime()
{
	//Thiết lập giá trị default khi khởi tạo đối tượng Gametime
	this->_accumulationnTime = 0; 
	setTime(0);
}
Gametime::~Gametime()
{

}
void Gametime::Update(DWORD dt)
{
	//Kiểm tra xem thời gian đã tích luỹ + thêm thời gian dt có lớn hơn 1000 hay không
	if (_accumulationnTime + dt < 1000)
	{
		//Nếu có
		_accumulationnTime += dt;
	}
	//Nếu không 
	else
	{
		_accumulationnTime = (_accumulationnTime + dt) % 1000;
		_time++;
		isTimeChanged = true; // set true cho biến cờ hiệu khi có sự thay đổi trong biến _time 
	}
}
void Gametime::setTime(int t)
{
	_time = t;
}
int Gametime::getTime()
{
	return _time;
}
bool Gametime::checkIsTimeChanged()
{
	bool result = isTimeChanged;
	isTimeChanged = false; // Sau khi lấy trạng thái xong rồi thì xem như "chưa thay đổi"
	return result;
}