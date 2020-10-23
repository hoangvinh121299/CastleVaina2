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
	if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
		camera->SetPosition(camera->GetXCam() + 2, camera->GetYCam());
	if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
		camera->SetPosition(camera->GetXCam() - 2, camera->GetYCam());
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
	}
}
void SceneGame::OnKeyUp(int keycode)
{
	
}
void SceneGame::InitGame()
{
	resetResources();
}
void SceneGame::resetResources()
{
	gridGame->reloadMapGrid();
}
void SceneGame::Update(DWORD dt)
{
	/*gridGame->getListObjectFromMapGrid(listObject, camera);
	camera->Update(dt);*/
	for (UINT i = 0; i < listObject.size(); i++)
	{
		listObject[i]->Update(dt, &listObject);
	}
}
void SceneGame::Render()
{
	for (UINT i = 0; i < listObject.size(); i++)
		listObject[i]->Render(camera);
}
void SceneGame::LoadResources()
{
	TextureManager*_textureMangager = TextureManager::GetInstance();

	gridGame = new Grid();
	camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);

	InitGame();
}