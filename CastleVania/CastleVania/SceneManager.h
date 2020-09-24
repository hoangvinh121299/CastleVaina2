#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__
#include"Scence.h"
#include"Camera.h"
#include "define.h"
class SceneManager
{
private:
	static SceneManager * _Instance;
	Scene *_scene;
public:
	SceneManager();
	~SceneManager();

	static SceneManager * getInstance();
	void SetScene(Scene * x);
	
	void KeyState(BYTE *state);
	void OnKeyDown(int Keycode);
	void OnKeyUp(int Keycode);

	void LoadResources();
	void Update(DWORD dt);
	void Render();
	
	Scene *getScene();
};
#endif
