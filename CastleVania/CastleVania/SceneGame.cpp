#include "SceneGame.h"
SceneGame::SceneGame()
{
	/*camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);
	camera->SetPosition(0, 0);
	simon = new Simon(camera);
	simon->setPostion(SIMON_POSITION_DEFAULT);
	simon->Render(camera);
	simon->renderBoundingBox(camera);*/
	LoadResources();
}
SceneGame::~SceneGame()
{

}
void SceneGame::KeyState(BYTE *state)
{
	if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
	{
		camera->SetPosition(camera->GetXCam() + 2, camera->GetYCam());
	}
	if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
		camera->SetPosition(camera->GetXCam() - 2, camera->GetYCam());

	DebugOut(L"Keystate done\n");
}
void SceneGame::OnKeyDown(int keycode)
{
	if (keycode == DIK_R) //Render bounding box
		//Nhấn R để bật tắt trạng thái render bounding box
	{
		if (isDebug_RenderBBox == 0)
			isDebug_RenderBBox = 1;
		else
			isDebug_RenderBBox = 0;
		DebugOut(L"OnkeyDown done\n");
	}
}
void SceneGame::OnKeyUp(int keycode)
{
	
}
void SceneGame::InitGame()
{
	camera->SetPosition(0, 0);
	simon->setPostion(SIMON_POSITION_DEFAULT);
	simon->Init();
	simon->renderBoundingBox(camera);
	DebugOut(L"InitGame done\n");
}
void SceneGame::resetResources()
{
	gridGame->reloadMapGrid();
}
void SceneGame::Update(DWORD dt)
{
	/*gridGame->getListObjectFromMapGrid(listObject, camera);*/
	simon->Update(dt, &listObject);
	camera->Update(dt);
	for (UINT i = 0; i < listObject.size(); i++)
	{
		listObject[i]->Update(dt, &listObject);
	}
	DebugOut(L"Scenegame Update done\n");
}
void SceneGame::Render()
{
	simon->Render(camera);
	for (UINT i = 0; i < listObject.size(); i++)
		listObject[i]->Render(camera);
}
void SceneGame::LoadResources()
{
	TextureManager*_textureMangager = TextureManager::GetInstance();

	gridGame = new Grid();
	camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);
	simon = new Simon(camera);
	InitGame();
	DebugOut(L"SceneGame Loadresources done\n");
}
