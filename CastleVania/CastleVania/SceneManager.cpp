#include "SceneManager.h"
SceneManager * SceneManager::_Instance = NULL;

SceneManager::SceneManager()
{

}
SceneManager::~SceneManager()
{

}
SceneManager *SceneManager::getInstance()
{
	if (_Instance == NULL)
		_Instance = new SceneManager();
	return _Instance;
}
void SceneManager::SetScene(Scene * x)
{
	Scene * scene_temp = _scene;
	_scene = x;
	SAFE_DELETE(scene_temp);
}
void SceneManager::KeyState(BYTE *state)
{
	_scene->KeyState(state);
}
void SceneManager::OnKeyDown(int Keycode)
{
	_scene->OnKeyDown(Keycode);
}
void SceneManager::OnKeyUp(int Keycode)
{
	_scene->OnKeyUp(Keycode);
}
void SceneManager::LoadResources()
{
	_scene->Loadresources();
}
void SceneManager::Update(DWORD dt)
{
	_scene->Update(dt);

}
void SceneManager::Render()
{
	_scene->Render();
}
Scene * SceneManager::getScene()
{
	return _scene;
}