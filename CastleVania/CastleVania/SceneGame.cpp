#include "SceneGame.h"
SceneGame::SceneGame()
{
	LoadResources();
}
SceneGame::~SceneGame()
{

}
void SceneGame::KeyState(BYTE *state)
{
	if (Game::GetInstance()->IsKeyDown(DIK_DOWN))
	{
		simon->sit();
		if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
			simon->right();
		if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
			simon->left();
		return;
	}
	//Đi qua phải
	if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
	{
		 
		simon->right();
		simon->walking();
	}
	else
	{ //Hoặc đi qua trái 
		if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
		{
			simon->left();
			simon->walking();
		}
		else
			//Không thì đứng yên
		{
			simon->stop();
		}
	}
	//Simon ngồi 
	
}

void SceneGame::OnKeyDown(int keycode)
{
	if (keycode == DIK_R) //Render bounding box

	{
		if (isDebug_RenderBBox == 0)
			isDebug_RenderBBox = 1;
		else
			isDebug_RenderBBox = 0;
		DebugOut(L"OnkeyDown done\n");
	}

	//SIMON nhảy 
	if (keycode == DIK_SPACE && simon->isOnStair==false)
	{
		//Nếu vừa nhảy vừa đi thì nhảy 1 đoạn nhỏ theo vx
		if (Game::GetInstance()->IsKeyDown(DIK_LEFT) || Game::GetInstance()->IsKeyDown(DIK_RIGHT))
		{
			simon->stop(); // Vô hiệu hoá các động tác đang thực hiện 
			simon->setSpeed(SIMON_WALKING_SPEED * simon->getDirection(), -SIMON_VJUMP);
			simon->isJumping = 1;
			simon->isWalking = 1;
		}
		else
		//Nhảy tại chỗ
		{
			simon->jump();
		}
	}
	//Simon tấn công bình thường
	if (keycode == DIK_A)
		simon->attack();
	
}
void SceneGame::OnKeyUp(int keycode)
{
	
}
void SceneGame::InitGame()
{
	camera->SetPosition(0, 0);
	camera->setAllowFollowSimon(true);
	simon->setPostion(SIMON_POSITION_DEFAULT);
	simon->Init();
	DebugOut(L"InitGame done\n");
}
void SceneGame::resetResources()
{
	gridGame->reloadMapGrid();
}
void SceneGame::Update(DWORD dt)
{
	gridGame->getListObjectFromMapGrid(listObject, camera);
	simon->Update(dt, &listObject);
	camera->Update(dt);
	//for (UINT i = 0; i < listObject.size(); i++)
	//{
	//	listObject[i]->Update(dt, &listObject);
	//}
	//DebugOut(L"Scenegame Update done\n");
}
void SceneGame::Render()
{
	simon->Render(camera);
	/*for (UINT i = 0; i < listObject.size(); i++)
		listObject[i]->Render(camera);*/
}
void SceneGame::LoadResources()
{
	//TextureManager*_textureMangager = TextureManager::GetInstance();
	gridGame = new Grid();
	camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);
	simon = new Simon(camera);
	InitGame();
	DebugOut(L"SceneGame Loadresources done\n");
}
