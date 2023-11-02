//�C���N���[�h
#include <Windows.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "Engine/Direct3D.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Rootjob.h"
#include "Engine/Model.h"
#include "DirectXCollision.h"

#include "resource.h"
#include "Stage.h"

//ImGui�֘A�f�[�^�̃C���N���[�h
//#include "ImGui/imgui.h"
//#include "ImGui/imgui_impl_dx11.h"
//#include "ImGui/imgui_impl_win32.h"

#pragma comment(lib, "winmm.lib")

//�萔�錾
const char* WIN_CLASS_NAME = "SampleGame";  //�E�B���h�E�N���X��
const int WINDOW_WIDTH = 800;  //�E�B���h�E�̕�
const int WINDOW_HEIGHT = 600; //�E�B���h�E�̍���

Rootjob* pRootjob = nullptr;

//�v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);

//�G���g���[�|�C���g
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	////TriangleTests::Intersects();
	//setlocale(LC_ALL, "Japanese");
	//HANDLE hFile = CreateFile(
	//	"dataFile.txt",
	//	GENERIC_WRITE,
	//	0,
	//	NULL,
	//	CREATE_ALWAYS,
	//	FILE_ATTRIBUTE_NORMAL,
	//	NULL
	//);
	//if (hFile == INVALID_HANDLE_VALUE)//���s�����Ƃ�
	//{
	//	std::cout << "�t�@�C���I�[�v���Ɏ��s" << GetLastError() << std::endl;
	//	return -1;
	//}
	////std::string writeStr = 
	//XMVECTOR beginP = XMVectorSet(1, 5, 1, 0);
	//XMVECTOR dirVec = XMVectorSet(0, -1, 0, 0);
	//XMVECTOR P1 = XMVectorSet(0, 0, 0, 0);
	//XMVECTOR P2 = XMVectorSet(0, 0, 3, 0);
	//XMVECTOR P3 = XMVectorSet(3, 0, 0, 0);
	//float dist;

	//bool result = TriangleTests::Intersects(beginP, dirVec, P1, P2, P3, dist);

	//�E�B���h�E�N���X�i�݌v�}�j���쐬
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);             //���̍\���̂̃T�C�Y
	wc.hInstance = hInstance;                   //�C���X�^���X�n���h��
	wc.lpszClassName = WIN_CLASS_NAME;            //�E�B���h�E�N���X��
	wc.lpfnWndProc = WndProc;                   //�E�B���h�E�v���V�[�W��
	wc.style = CS_VREDRAW | CS_HREDRAW;         //�X�^�C���i�f�t�H���g�j
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //�A�C�R��
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //�������A�C�R��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //�}�E�X�J�[�\��
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);                     //���j���[�i�Ȃ��j
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //�w�i�i���j
	RegisterClassEx(&wc); //�N���X��o�^

	//�E�B���h�E�T�C�Y�̌v�Z
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, TRUE);
	int winW = winRect.right - winRect.left;     //�E�B���h�E��
	int winH = winRect.bottom - winRect.top;     //�E�B���h�E����

	//�E�B���h�E���쐬
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,         //�E�B���h�E�N���X��
		"�}�b�v�G�f�B�^�[",     //�^�C�g���o�[�ɕ\��������e
		WS_OVERLAPPEDWINDOW, //�X�^�C���i���ʂ̃E�B���h�E�j
		CW_USEDEFAULT,       //�\���ʒu���i���܂����j
		CW_USEDEFAULT,       //�\���ʒu��i���܂����j
		winW,               //�E�B���h�E��
		winH,               //�E�B���h�E����
		NULL,                //�e�E�C���h�E�i�Ȃ��j
		NULL,                //���j���[�i�Ȃ��j
		hInstance,           //�C���X�^���X
		NULL                 //�p�����[�^�i�Ȃ��j
	);

	//�E�B���h�E��\��
	ShowWindow(hWnd, nCmdShow);

	//Direct3D������
	HRESULT hr;
	hr = Direct3D::Initialize(winW, winH, hWnd);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Direct3D�̏������Ɏ��s", "�G���[", MB_OK);
		PostQuitMessage(0); //�G���[�N�����狭���I��
		return hr;
	}

	//Fbx* pFbx = new Fbx;
	//pFbx->Load("Assets/BoxBrick.fbx");
	//RayCastData data;
	//data.start = XMFLOAT3(0, 5, 0);
	//data.dir = XMFLOAT3(0, -1, -1);
	////�����ŗ����Ƃ�܂��B
	//pFbx->RayCast(data);
	//int a = 6;
	//a++;

	//�J�����̏�����
	Camera::Initialize();

	//DirectInput�̏�����
	Input::Initialize(hWnd);

	pRootjob = new Rootjob(nullptr);
	pRootjob->Initialize();

	HWND hDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)DialogProc);
	//DialogBox();

	//���b�Z�[�W���[�v�i�����N����̂�҂j
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//���b�Z�[�W����
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}

		//���b�Z�[�W�Ȃ�
		else
		{
			timeBeginPeriod(1);

			static DWORD countFps = 0;

			static DWORD startTime = timeGetTime();
			DWORD nowTime = timeGetTime();
			static DWORD lastUpdateTime = nowTime;

			if (nowTime - startTime >= 1000)
			{
				char str[16];
				wsprintf(str, "%u", countFps);
				SetWindowText(hWnd, str);

				countFps = 0;
				startTime = nowTime;
			}

			if ((nowTime - lastUpdateTime) * 60 <= 1000)
			{
				continue;
			}
			lastUpdateTime = nowTime;

			countFps++;


			timeEndPeriod(1);

			if (Input::IsKeyUp(DIK_ESCAPE))
			{
				static int cnt = 0;
				cnt++;
				if (cnt >= 1) {
					PostQuitMessage(0);
				}
			}

			//���Q�[���̏���
			//�J�����̏���
			Camera::Update();

			//���͂̏���
			Input::Update();

			pRootjob->UpdateSub();

			//���`��
			Direct3D::BeginDraw();

			//���[�g�W���u����A���ׂẴI�u�W�F�N�g�̃h���[���Ă�
			pRootjob->DrawSub();

			Direct3D::EndDraw();

		}
	}

	Model::Release();
	pRootjob->ReleaseSub();
	SAFE_DELETE(pRootjob);

	Input::Release();
	Direct3D::Release();

	return S_OK;
}

//�E�B���h�E�v���V�[�W���i�������������ɂ�΂��֐��j
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int a = 0;
	switch (msg)
	{
	case WM_MOUSEMOVE:
		Input::SetMousePosition(LOWORD(lParam), HIWORD(lParam));
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);  //�v���O�����I��
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) 
		{
		case ID_MENU_NEW:
			a++;
			break;
		case ID_MENU_OPEN:
			a++;
			((Stage*)pRootjob->FindObject("stage"))->Load();
			return 0;
		case ID_MENU_SAVE:
			//�t�@�C���ۑ��_�C�A���O�Ŗ��O�����߂�
			//���߂��t�@�C�����ŃZ�[�u�����s
			((Stage*)pRootjob->FindObject("stage"))->Save();
			return 0;
		}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//Main�̃_�C�A���O�v���V�[�W��
BOOL CALLBACK DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//Stage* pStage = (Stage*)pRootjob->FindObject("Stage");
	return ((Stage*)pRootjob->FindObject("Stage"))->DialogProc(hDlg, msg, wParam, lParam);

	//(Stage*)(pRootjob->FindObject("Stage"))->DialogProc(hDlg, msg, wParam, lParam);

}

