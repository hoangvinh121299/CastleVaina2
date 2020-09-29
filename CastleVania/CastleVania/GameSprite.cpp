#include "GameSprite.h"

//Xây dựng hình chữ nhật cho mỗi sprite
RECT GameSprite::getRectFrame(int idFrame)
{
	RECT res;
	//idFrame bắt đầu từ 0
	//Hiển thị vị trí biên trái của frame
	//Số id của frame chia lấy số dư cho số cột của texture sau đó nhân cho chiều rộng frame
	res.left = (idFrame % texture->GetColumn())*texture->GetFrameWidth();
	//Hiển thị vị trí biên trên của frame
	//Số id của frame chia lấy số dư cho số cột của texture sau đó nhân cho chiều cao frame 
	res.top = (idFrame %texture->GetColumn())*texture->GetFrameHeight();
	//Hiển thị bên phải
	res.right = res.left + texture->GetFrameWidth();
	//Hiển thị bên dưới
	res.bottom = res.top + texture->GetFrameHeight();
	return res;
}GameSprite::GameSprite(GameTexture * Texture, DWORD timeAnimation)
{
	texture = Texture;
	currentFrame = 0;
	totalFrames = texture->TotalFrame - 1;
	//Thời gian chuyển texture được truyền vào
	this->timeAnimation = timeAnimation;
	//Khởi tạo đối tượng singleton cho lớp spirte
	spriteHandler = Game::GetInstance()->GetSpriteHandler();
}
GameSprite::~GameSprite()
{

}
void GameSprite::Next()
{
	currentFrame++;
	//Reset về frame 0 khi frame hiện tại lớn hơn tổng số frame
	if (currentFrame > totalFrames)
		currentFrame = 0;
}
void GameSprite::ResetTime()
{
	//Đặt lại thời gian chờ đã tích luỹ
	timeAccumulated = 0;
}
void GameSprite::SelectFrame(int idFrame)
{
	currentFrame = idFrame;
}
void GameSprite::Update(DWORD dt)
{
	//Thời gian tích luỹ bằng tổng dt
	timeAccumulated += dt;
	if (timeAccumulated >= timeAnimation)// Nếu thời gian chờ tích luỹ lớn hơn tổng thời gian Animation
	{
		//TODO:Hỏi DUY
		timeAccumulated -= timeAnimation;// Đặt lại thời gian chờ tích luỹ
		//Chuyển qua frame khác
		this->Next();
	}
}
void GameSprite::Draw(float X, float Y, int alpha, int R, int G, int B)
{
	DrawFrame(currentFrame, X, Y, alpha, R, G, B);
}
void GameSprite::DrawFrame(int idFrame, float X, float Y, int alpha, int R, int G, int B)
{
	RECT r = getRectFrame(idFrame); // Khởi tạo khung chữ nhật bao quanh frame
	D3DXVECTOR3 p(trunc(X), trunc(Y), 0); //Vector tạo độ
	spriteHandler->Draw(texture->Texture, &r, NULL, &p, D3DCOLOR_ARGB(alpha, R, G, B));
}
//Lật hình
void GameSprite::DrawFlipX(float X, float Y, int alpha, int  R, int G, int B)
{
	this->DrawFrameFlipX(currentFrame, X, Y, alpha, R, G, B);
}
void GameSprite::DrawFrameFlipX(int idFrame, float X, float Y, int alpha, int R, int G, int B)
{
	RECT r = getRectFrame(idFrame);
	D3DXMATRIX AA, BB; //Khởi tạo 2 ma trận AA và BB
	spriteHandler->GetTransform(&AA);// Chuyển sprite thành ma trận AA
	//Khởi tạo ma trận -1 và truyền vào cho BB
	D3DXMatrixTransformation2D(&BB, &D3DXVECTOR2(X, X), 0.0f, &D3DXVECTOR2(-1.0f, -1.0f), NULL, 0.0f, NULL);
	D3DXMATRIX CC = AA * BB; //Đảo ngược ma trận AA bằng cách nhân AA cho ma trận -1
	spriteHandler->SetTransform(&CC); //Chuyển ma trận CC về lại thành sprite
	X -= texture->GetFrameWidth(); // Set lại tạo độ của X sau khi lật hình 
	D3DXVECTOR3 p(trunc(X), trunc(Y), 0); //Set lại vector toạ độ
	//Vẽ hình sau khi lật
	spriteHandler->Draw(texture->Texture, &r, NULL, &p, D3DCOLOR_ARGB(alpha, R, G, B));
	//Reset ma trận AA về thành sprite ban đầu sau khi vẽ xong
	//Xảy ra tình trạng conflict các sprite với nhau nều không reset về lại ban đầu 
	spriteHandler->SetTransform(&AA);
}
int GameSprite::getCurrentFrame()
{
	return currentFrame;
}
int GameSprite::getTotalFrames()
{
	return totalFrames;
}