#ifndef __GAME_H__
#define __GAME_H__
#define TITLE "Direct X Game"
#include <d3d9.h>

#define WIDTH 800
#define HEIGHT 600

class Game
{
private:
	/* Khoi tao kich thuoc cua so */
	int					m_Width;
	int					m_Height;
	bool				m_IsWindow;

	/* Cac bien dinh nghia cua so */
	HINSTANCE			m_HandleInstance;
	HWND				m_HandleWindow;

	/* Doi tuong cua Direct */
	LPDIRECT3D9			m_lpDirect3D;
	LPDIRECT3DDEVICE9 	m_lpDirect3DDevice;

	/* Ham Callback */
	static LRESULT CALLBACK WndProceduce(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	Game(int scr_Width, int scr_Height, bool isWindow);

	bool initHandleWindow();
	bool initDirectX3DEnviroment();
	bool initDirect3DDevice();

	/* Main game */
	void GameInit();
	void GameRun();
	void GameExit();
};
#endif

/* Khoi tao doi tuong Game */
Game::Game(int scr_Width, int scr_Height, bool isWindow) {
	this->m_Width = scr_Width;
	this->m_Height = scr_Height;
	this->m_IsWindow = isWindow;
	this->m_HandleInstance = 0;
	this->m_HandleWindow = 0;
	this->m_lpDirect3D = 0;
	this->m_lpDirect3DDevice = 0;
}

/* Khoi tao cua so */
bool Game::initHandleWindow()
{
	WNDCLASSEX WndcEx;
	ZeroMemory(&WndcEx, sizeof(WndcEx));
	WndcEx.cbSize = sizeof(WNDCLASSEX);
	WndcEx.hInstance = this->m_HandleInstance;
	WndcEx.lpfnWndProc = (WNDPROC)WndProceduce;
	WndcEx.lpszClassName = "Game";
	if (!RegisterClassEx(&WndcEx))
	{
		return false;
	}
	this->m_HandleWindow = CreateWindowEx(
		NULL,
		"Game", // đặt trung với WndcEx.lpszClassName
		TITLE, // TITLE của cửa sổ #define TITLE "GAME"
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, // style của cửa sổ
		100, // tọa độ x khi cửa sổ xuất hiện
		100, // tọa độ y khi cửa sổ xuất hiện
		this->m_Width, // chiều dài cửa sổ
		this->m_Height, // chiều cao cửa sổ
		0, // handle window parent của của sổ hiện tại. Để là 0
		0, // handle đến Menu. Để là 0
		this->m_HandleInstance, // Handle Instance của ứng dụng
		0); // giữ nguyên theo default là 0
	if (!this->m_HandleWindow) // Kiểm tra tạo thành công.
	{
		return false;
	}
	ShowWindow(m_HandleWindow, SW_SHOW); // show cửa sổ lên màn hình
	UpdateWindow(m_HandleWindow); // Update cửa sổ theo thời gian
	return true;
}

bool Game::initDirectX3DEnviroment()
{
	this->m_lpDirect3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_lpDirect3D){
		return true;
	}
	return false;
}

bool Game::initDirect3DDevice()
{
	D3DPRESENT_PARAMETERS d3dpp; // khai báo biến
	ZeroMemory(&d3dpp, sizeof(d3dpp)); // Khởi tạo vùng nhớ
	d3dpp.BackBufferCount = 1; // Số lượng Back buffer
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; // Chọn UNKNOW, DirectX sẽ tự chọn 1 định dạng phù hợp cho Device
	d3dpp.BackBufferHeight = HEIGHT; // chiều cao cảu BackBuffer
	d3dpp.BackBufferWidth = WIDTH; // Chiều dài của BackBuffer
	d3dpp.Windowed = true; // Window ở dạng cửa sổ, không phải full màn hình
	d3dpp.hDeviceWindow = this->m_HandleWindow; // Gán HandleWindow cho Device
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; // Phương thức swap của Buffer
	m_lpDirect3D->CreateDevice(
		D3DADAPTER_DEFAULT, // Chọn DEFAULT ADAPTER
		D3DDEVTYPE_HAL, // 
		m_HandleWindow, // Handle Window của của sổ
		D3DCREATE_HARDWARE_VERTEXPROCESSING, // Hard ware vertex processing
		&d3dpp,
		&m_lpDirect3DDevice); // Hàm tạo Device
	if (FAILED(m_lpDirect3DDevice))
	{
		return false;
	}
	return true;
}

void Game::GameInit()
{
	initHandleWindow();
	initDirectX3DEnviroment();
	initDirect3DDevice();
}

void Game::GameRun()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg)); // Tạo một Mesage để lắng nghe các sự kiện của cửa sổ
	while (true)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) // Lấy message và truyền vào biến msg đã khai báo
		{
			if (msg.message == WM_QUIT) // Kiểm tra nếu msg yêu cầu QUIT ứng dụng thì ứng dụng sẽ thoát
				break;
			TranslateMessage(&msg); // xử lý input và chuyển vào msg
			DispatchMessage(&msg); // gửi message đến hàm WndProceduce để xử lý
		}
		else
		{
			// Begin Draw something in Game
			m_lpDirect3DDevice->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(100, 100, 100), 1.0f, 0); // Clear cửa sổ 1 lần trước khi vẽ lên
			if (m_lpDirect3DDevice->BeginScene())
			{

				// Game Render Here
				m_lpDirect3DDevice->EndScene();
			}
			m_lpDirect3DDevice->Present(0, 0, 0, 0); // Thể hiện tất cả những gì đã vẽ lên màn hình
		}
	}
}

void Game::GameExit()
{
	if (this->m_lpDirect3D) {
		this->m_lpDirect3D->Release();
		this->m_lpDirect3D = NULL;
	}
	if (this->m_lpDirect3DDevice) {
		this->m_lpDirect3DDevice->Release();
		this->m_lpDirect3DDevice = NULL;
	}
}

LRESULT CALLBACK Game::WndProceduce(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}