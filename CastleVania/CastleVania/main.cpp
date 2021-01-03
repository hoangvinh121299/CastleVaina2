#include "debug.h"
#include "Game.h"
#include "ScenenIntro.h"
#include "SceneManager.h"
#include "SceneGame.h"
#define WINDOW_CLASS_NAME L"CastleVania"
#define MAIN_WINDOW_TITLE L"CastleVania"
Game *game;
SceneManager *sceneManager;

LRESULT CALLBACK WinProc(HWND hwnd, UINT message,WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}
void loadResources()
{
	sceneManager->LoadResources();
}
void Update(DWORD dt)
{
	sceneManager->Update(dt);
}
void Render()
{
	LPDIRECT3DDEVICE9 d3dvv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 backBuffer = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();
		if (d3dvv->BeginScene())
		{
			d3dvv->ColorFill(backBuffer,NULL, D3DCOLOR_BACKGROUND);
			spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
			sceneManager->Render();
			spriteHandler->End();
			d3dvv->EndScene();
		}
	d3dvv->Present(NULL,NULL,NULL,NULL);
}
HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;
	/*camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);
	camera->SetPosition(0, 0);
	simon = new Simon(camera);
	simon->setPostion(SIMON_POSITION_DEFAULT);*/
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();
		
		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();
			//DebugOut(L"dt = %d , tickPerFrame = %d \n", dt, tickPerFrame)
			Update(dt);
			Render();
		}
		else
		Sleep(tickPerFrame - dt);
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = Game::GetInstance();
	game->Init(hWnd);

	sceneManager = SceneManager::getInstance();

	sceneManager->SetScene(new Scene_Intro());
	
	game->InitKeyboard();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}