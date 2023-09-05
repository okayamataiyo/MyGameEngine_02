#include "Input.h"
#include "Direct3D.h"
#include <string>

namespace Input
{
	LPDIRECTINPUT8   pDInput = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;
	BYTE KeyState[256] = { 0 };
	BYTE prevKeyState[256];    //�O�t���[���ł̊e�L�[�̏��

	//�}�E�X
	LPDIRECTINPUTDEVICE8	pMouseDevice;	//�f�o�C�X�I�u�W�F�N�g
	DIMOUSESTATE mouseState;				//�}�E�X�̏��
	DIMOUSESTATE prevMouseState;			//�O�t���[���̃}�E�X�̏��
	XMVECTOR mousePosition;

	void Initialize(HWND hWnd)
	{
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, 
			(VOID**)&pDInput, nullptr);
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice->SetCooperativeLevel(hWnd,
			DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	}

	void Update()
	{
		memcpy(prevKeyState,KeyState,sizeof(prevKeyState));

		pKeyDevice->Acquire();
		pKeyDevice->GetDeviceState(sizeof(KeyState), &KeyState);

		//�}�E�X
		pMouseDevice->Acquire();
		memcpy(&prevMouseState, &)

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
		//���͉����ĂāA�O��͉����ĂȂ�
		if (IsKey(keyCode) && !(prevKeyState[keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	bool IsKeyUp(int keyCode)
	{
		//���͉����ĂȂ��āA�O��͉����Ă���
		if (!IsKey(keyCode) && (prevKeyState[keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	XMVECTOR GetMousePosition()
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
		mousePosition = XMVectorSet((float)x, (float)y, 0, 0);
		//mousePosition.y = y;
		//mousePosition.x = x;
		std::string resStr = std::to_string(x) + "," + std::to_string(y);
		OutputDebugString(resStr.c_str());
	}

	void Release()
	{
		SAFE_RELEASE(pDInput);

	}
	bool IsMouseButton(int buttonCode)
	{
		//�����Ă�
		if (mouseState.rgbButtons[buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}
	bool IsMouseButtonDown(int buttonCode)
	{
		//���͉����ĂāA�O��͉����ĂȂ�
		if (IsMouseButton(buttonCode) && !(prevMouseState.rgbButtons[buttonCode] & 0x80))
		{
			return true;
		}
		return false;
	}
	bool IsMouseButtonUp(int buttonCode)
	{
		//�������ĂȂ��āA�O��͉����Ă�
		if (!IsMouseButton(buttonCode) && prevMouseState.rgbButtons[buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}
}