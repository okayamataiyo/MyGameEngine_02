//インクルード
#include <Windows.h>
#include "Direct3D.h"
#include "Quad.h"
#include "Camera.h"

Quad* P;

//定数宣言
const char* WIN_CLASS_NAME = "SampleGame";  //ウィンドウクラス名
const int WINDOW_WIDTH = 800;				//ウィンドウの幅
const int WINDOW_HEIGHT = 600;				//ウィンドウの高さ

//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//エントリーポイント
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウクラス（設計図）を作成
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);             //この構造体のサイズ
	wc.hInstance = hInstance;                   //インスタンスハンドル
	wc.lpszClassName = WIN_CLASS_NAME;          //ウィンドウクラス名
	wc.lpfnWndProc = WndProc;                   //ウィンドウプロシージャ
	wc.style = CS_VREDRAW | CS_HREDRAW;         //スタイル（デフォルト）
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //アイコン
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //小さいアイコン
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //マウスカーソル
	wc.lpszMenuName = NULL;                     //メニュー（なし）
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景（白）
	RegisterClassEx(&wc);						//クラスを登録

	//ウィンドウサイズの計算
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
	int winW = winRect.right - winRect.left;	//ウィンドウ幅
	int winH = winRect.bottom - winRect.top;	//ウィンドウ高さ

	//ウィンドウを作成
	HWND hWnd = CreateWindow(
	WIN_CLASS_NAME,			//ウィンドウクラス名
	"サンプルゲーム",		//タイトルバーに表示する内容
	WS_OVERLAPPEDWINDOW,	//スタイル（普通のウィンドウ）
	CW_USEDEFAULT,			//表示位置左（おまかせ）
	CW_USEDEFAULT,			//表示位置上（おまかせ）
	winW,					//ウィンドウ幅
	winH,					//ウィンドウ高さ
	NULL,					//親ウインドウ（なし）
	NULL,					//メニュー（なし）
	hInstance,				//インスタンス
	NULL					//パラメータ（なし）
	);

	//ウィンドウを表示
	ShowWindow(hWnd, nCmdShow);

	HRESULT hr;//こっからしたはhr使えるよ
	//Direct3D初期化
	hr = Direct3D::Initialize(winW, winH, hWnd);
	if (FAILED(hr))
	{
		PostQuitMessage(0);	//プログラム終了
	}
//	P = new Quad;

	if (FAILED(hr))
	{
		PostQuitMessage(0);
	}

//	P->Initialize();
	Camera::Initialize();
//	Camera::SetPosition(XMFLOAT3(2, 0, 0));
//	Camera::SetTarget(XMFLOAT3(2, 0, 0));
	P = new Quad;
	hr = P->Initialize();

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
			Camera::Update(); //カメラの更新処理
			//ゲームの処理 
			Direct3D::BeginDraw();

			//描画処理
			static float a = 0;
			a += 0.05;
			XMMATRIX matR = XMMatrixRotationY(XMConvertToRadians(a));
//			XMMATRIX matT = XMMatrixTranslation(4, 0, 0);
//			XMMATRIX matS = XMMatrixScaling(1, 3, 1);
//			XMMATRIX mat = matS * matR * matT;
			XMMATRIX mat = matR;
			P->Draw(mat);
			Direct3D::EndDraw();
			
		}
	}

	Direct3D::Release();
	SAFE_DELETE(P);
	
	return 0;
}

//ウィンドウプロシージャ（何かあった時によばれる関数）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYUP:
		PostQuitMessage(0); //プログラム終了
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);  //プログラム終了
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}