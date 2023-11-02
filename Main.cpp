//インクルード
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

//ImGui関連データのインクルード
//#include "ImGui/imgui.h"
//#include "ImGui/imgui_impl_dx11.h"
//#include "ImGui/imgui_impl_win32.h"

#pragma comment(lib, "winmm.lib")

//定数宣言
const char* WIN_CLASS_NAME = "SampleGame";  //ウィンドウクラス名
const int WINDOW_WIDTH = 800;  //ウィンドウの幅
const int WINDOW_HEIGHT = 600; //ウィンドウの高さ

Rootjob* pRootjob = nullptr;

//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);

//エントリーポイント
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
	//if (hFile == INVALID_HANDLE_VALUE)//失敗したとき
	//{
	//	std::cout << "ファイルオープンに失敗" << GetLastError() << std::endl;
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

	//ウィンドウクラス（設計図）を作成
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);             //この構造体のサイズ
	wc.hInstance = hInstance;                   //インスタンスハンドル
	wc.lpszClassName = WIN_CLASS_NAME;            //ウィンドウクラス名
	wc.lpfnWndProc = WndProc;                   //ウィンドウプロシージャ
	wc.style = CS_VREDRAW | CS_HREDRAW;         //スタイル（デフォルト）
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //アイコン
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //小さいアイコン
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //マウスカーソル
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);                     //メニュー（なし）
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景（白）
	RegisterClassEx(&wc); //クラスを登録

	//ウィンドウサイズの計算
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, TRUE);
	int winW = winRect.right - winRect.left;     //ウィンドウ幅
	int winH = winRect.bottom - winRect.top;     //ウィンドウ高さ

	//ウィンドウを作成
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,         //ウィンドウクラス名
		"マップエディター",     //タイトルバーに表示する内容
		WS_OVERLAPPEDWINDOW, //スタイル（普通のウィンドウ）
		CW_USEDEFAULT,       //表示位置左（おまかせ）
		CW_USEDEFAULT,       //表示位置上（おまかせ）
		winW,               //ウィンドウ幅
		winH,               //ウィンドウ高さ
		NULL,                //親ウインドウ（なし）
		NULL,                //メニュー（なし）
		hInstance,           //インスタンス
		NULL                 //パラメータ（なし）
	);

	//ウィンドウを表示
	ShowWindow(hWnd, nCmdShow);

	//Direct3D初期化
	HRESULT hr;
	hr = Direct3D::Initialize(winW, winH, hWnd);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Direct3Dの初期化に失敗", "エラー", MB_OK);
		PostQuitMessage(0); //エラー起きたら強制終了
		return hr;
	}

	//Fbx* pFbx = new Fbx;
	//pFbx->Load("Assets/BoxBrick.fbx");
	//RayCastData data;
	//data.start = XMFLOAT3(0, 5, 0);
	//data.dir = XMFLOAT3(0, -1, -1);
	////ここで落ちとります。
	//pFbx->RayCast(data);
	//int a = 6;
	//a++;

	//カメラの初期化
	Camera::Initialize();

	//DirectInputの初期化
	Input::Initialize(hWnd);

	pRootjob = new Rootjob(nullptr);
	pRootjob->Initialize();

	HWND hDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)DialogProc);
	//DialogBox();

	//メッセージループ（何か起きるのを待つ）
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//メッセージあり
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}

		//メッセージなし
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

			//▼ゲームの処理
			//カメラの処理
			Camera::Update();

			//入力の処理
			Input::Update();

			pRootjob->UpdateSub();

			//▼描画
			Direct3D::BeginDraw();

			//ルートジョブから、すべてのオブジェクトのドローを呼ぶ
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

//ウィンドウプロシージャ（何かあった時によばれる関数）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int a = 0;
	switch (msg)
	{
	case WM_MOUSEMOVE:
		Input::SetMousePosition(LOWORD(lParam), HIWORD(lParam));
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);  //プログラム終了
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
			//ファイル保存ダイアログで名前を決める
			//決めたファイル名でセーブを実行
			((Stage*)pRootjob->FindObject("stage"))->Save();
			return 0;
		}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//Mainのダイアログプロシージャ
BOOL CALLBACK DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//Stage* pStage = (Stage*)pRootjob->FindObject("Stage");
	return ((Stage*)pRootjob->FindObject("Stage"))->DialogProc(hDlg, msg, wParam, lParam);

	//(Stage*)(pRootjob->FindObject("Stage"))->DialogProc(hDlg, msg, wParam, lParam);

}

