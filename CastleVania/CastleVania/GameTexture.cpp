#include "GameTexture.h"
// Lấy chiều rộng
int GameTexture::GetFrameWidth()
{
	return frameWidth;
}
// Lấy chiều cao
int GameTexture::GetFrameHeight()
{
	return frameHeight;
}
// Lấy tổng các cột của ma trận
int GameTexture::GetColumn()
{
	return Column;
}
// Lấy tổng các hàng của ma trận
int GameTexture::GetRow()
{
	return Row;
}
//Operator
GameTexture::GameTexture(const char* filePath,
	int column,
	int row,
	int totalframes,
	int R,
	int G,
	int B)
{
	Column = column;
	Row = row;
	TotalFrame = totalframes;
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFileA(filePath, &info);
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageFromeFile failed: %s\n", filePath);
		return;
	}
	this->frameWidth = info.Width / Column;
	this->frameHeight = info.Height / Row;
	LPDIRECT3DDEVICE9 d3dvv = Game::GetInstance()->GetDirect3DDevice();
	result = D3DXCreateTextureFromFileExA(
		d3dvv,
		filePath,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(R, G, B),
		&info,
		NULL,
		&Texture);
	if (result != D3D_OK)
	{
		OutputDebugString(L"[ERROR] CREATETEXTUREFROMFILEEXA FAILED\n");
		return;
	}
}
GameTexture::~GameTexture()
{
	if (this->Texture != NULL)
		this->Texture->Release();
}
