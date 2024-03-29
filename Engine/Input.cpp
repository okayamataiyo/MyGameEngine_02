#include "Input.h"
#include "Direct3D.h"
#include <string>

namespace Input
{
	//DirectInputオブジェクト
	LPDIRECTINPUT8   pDInput = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;
	BYTE KeyState[256] = { 0 };
	BYTE prevKeyState[256];    //前フレームでの各キーの状態

	//マウス
	LPDIRECTINPUTDEVICE8	pMouseDevice;	//デバイスオブジェクト
	DIMOUSESTATE mouseState;				//マウスの状態
	DIMOUSESTATE prevMouseState;			//前フレームのマウスの状態
	XMFLOAT3 mousePosition;

	void Initialize(HWND hWnd)
	{
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, 
			(VOID**)&pDInput, nullptr);
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice->SetCooperativeLevel(hWnd,
			DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

		//マウス
		pDInput->CreateDevice(GUID_SysMouse, &pMouseDevice, nullptr);
		pMouseDevice->SetDataFormat(&c_dfDIMouse);
		pMouseDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE);
	}

	void Update()
	{
		memcpy(prevKeyState,KeyState,sizeof(KeyState));

		pKeyDevice->Acquire();
		pKeyDevice->GetDeviceState(sizeof(KeyState), &KeyState);

		//マウス
		pMouseDevice->Acquire();
		memcpy(&prevMouseState, &mouseState, sizeof(mouseState));
		pMouseDevice->GetDeviceState(sizeof(mouseState), &mouseState);

	}

	bool IsKey(int keyCode)
	{
		if (KeyState[keyCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	bool IsKeyDown(int keyCode)
	{
		//今は押してて、前回は押してない
		if ((KeyState[keyCode] & 0x80) && !(prevKeyState[keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	bool IsKeyUp(int keyCode)
	{
		//今は押してなくて、前回は押している
		if (!(KeyState[keyCode] & 0x80) && (prevKeyState[keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	XMFLOAT3 GetMousePosition()
	{
		return mousePosition;
	}

	XMFLOAT3 GetMouseMove()
	{
		XMFLOAT3 result = XMFLOAT3((float)mouseState.lX,
								   (float)mouseState.lY,
								   (float)mouseState.lZ);
		return result;

	}

	void SetMousePosition(int x, int y)
	{
		//mousePosition = XMVectorSet((float)x, (float)y, 0, 0);
		mousePosition.y = y;
		mousePosition.x = x;
		std::string resStr = std::to_string(x) + "," + std::to_string(y);
		OutputDebugString(resStr.c_str());
	}

	void Release()
	{
		SAFE_RELEASE(pDInput);

	}
	bool IsMouseButton(int buttonCode)
	{
		//押してる
		if (mouseState.rgbButtons[buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}
	bool IsMouseButtonDown(int buttonCode)
	{
		//今は押してて、前回は押してない
		if (IsMouseButton(buttonCode) && !(prevMouseState.rgbButtons[buttonCode] & 0x80))
		{
			return true;
		}
		return false;
	}
	bool IsMouseButtonUp(int buttonCode)
	{
		//今押してなくて、前回は押してる
		if (!IsMouseButton(buttonCode) && prevMouseState.rgbButtons[buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}
}