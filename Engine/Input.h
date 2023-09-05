#pragma once

#include <dInput.h>
#include "Direct3D.h"

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

namespace Input
{
	void Initialize(HWND hWnd);
	void Update();
	bool IsKey(int keyCode);
	bool IsKeyDown(int keyCode);
	bool IsKeyUp(int keyCode);
	XMVECTOR GetMousePosition();
	void SetMousePosition(int x, int y);
	void Release();

	//�}�E�X
	bool IsMouseButton(int buttonCode);
	bool IsMouseButtonDown(int buttonCode);
	bool IsMouseButtonUp(int buttonCode);
	//XMFLOAT3 GetMousePosition();
	XMFLOAT3 GetMouseMove();
	void SetMousePosition(int x, int y);

};
