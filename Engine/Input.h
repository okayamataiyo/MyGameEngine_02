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
	void SetMousePosition(int x, int y);
	void Release();

	//マウス
	bool IsMouseButton(int buttonCode);
	bool IsMouseButtonDown(int buttonCode);
	bool IsMouseButtonUp(int buttonCode);	//マウスのボタンを今離したか調べる
	XMFLOAT3 GetMousePosition();			//マウスカーソルの位置を取得
	XMFLOAT3 GetMouseMove();				//そのフレームでマウスの移動量を取得
	void SetMousePosition(int x, int y);

};
