//インクルード
#include <Windows.h>
#include "Direct3D.h"
//#include "Quad.h"
#include "Camera.h"
#include "Dice.h"
#include "Sprite.h"
#include "Transform.h"
#include "Fbx.h"
#include "Input.h"

//定数宣言
const char* WIN_CLASS_NAME = "SampleGame";  //ウィンドウクラス名
const int WINDOW_WIDTH = 800;  //ウィンドウの幅
const int WINDOW_HEIGHT = 600; //ウィンドウの高さ

//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


//Quad* pQuad;
//Dice* pDice;
Fbx* pFbx;

//エントリーポイント
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
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
	wc.lpszMenuName = NULL;                     //メニュー（なし）
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景（白）
	RegisterClassEx(&wc); //クラスを登録

	//ウィンドウサイズの計算
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
	int winW = winRect.right - winRect.left;     //ウィンドウ幅
	int winH = winRect.bottom - winRect.top;     //ウィンドウ高さ

	//ウィンドウを作成
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,         //ウィンドウクラス名
		"サンプルゲーム",     //タイトルバーに表示する内容
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

	//DirectInputの初期化
	Input::Initialize(hWnd);

	if (FAILED(hr))
	{
		PostQuitMessage(0); //エラー起きたら強制終了
	}

	Camera::Initialize();



	//pQuad = new Quad;
	//pQuad->Initialize();

	Dice* pDice = new Dice;
	hr = pDice->Initialize();

	Sprite* pSprite = new Sprite;
	hr = pSprite->Initialize();

	pFbx = new Fbx;
	pFbx->Load("Assets/Cube.fbx");

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

			Camera::Update();

			//ゲームの処理
			Direct3D::BeginDraw();

			//入力情報の更新
			Input::Update();

			if (Input::IsKey(DIK_ESCAPE))
			{
 				PostQuitMessage(0);
			}

			static float angle = 0;
			angle += 0.05;
			//XMMATRIX mat = XMMatrixRotationY(XMConvertToRadians(angle)) * XMMatrixTranslation(0,3,0);

			Transform diceTransform;
//			diceTransform.position_.y = 1.0f;
			diceTransform.rotate_.y = -2.0f;
			diceTransform.rotate_.y =  3.0f;
			diceTransform.rotate_.y = angle;

//			mat = XMMatrixScaling(512.0f / 800.0f, 256.0f / 600.0f, 1.0f);
//			Transform spriteTransform;
//			spriteTransform.scale_.x = 512.0f / 800.0f;
//			spriteTransform.scale_.y = 256.0f / 600.0f;
			//mat = XMMatrixScaling(512.0f/800.0f, 256.0f/600.0f, 1.0f);

			//描画処理
			//static float a = 0;
			//a += 0.01;
			//XMMATRIX mata = XMMatrixRotationZ(XMConvertToRadians(a));
			//static float b = 0;
			//b += 0.01;
			//XMMATRIX matb = XMMatrixRotationX(XMConvertToRadians(b));
			//static float a = 0;
			//a += 0.1;
			//XMMATRIX matR = XMMatrixRotationZ(XMConvertToRadians(a));
			//XMMATRIX matT = XMMatrixTranslation(2, 0, 0);
			//XMMATRIX matS = XMMatrixTranslation(2.0, 2.0, 2.0);
			//XMMATRIX mat = matS * matT * matR;
			//XMMATRIX mat = XMMatrixRotationY(XMConvertToRadians(a));

//			pDice->Draw(diceTransform);

//			pSprite->Draw(spriteTransform);

			pFbx->Draw(diceTransform);

			Direct3D::EndDraw();

		}
	}


	//SAFE_DELETE(pQuad);
	SAFE_DELETE(pDice);
	SAFE_DELETE(pFbx);
	SAFE_DELETE(pSprite);

	Input::Release();
	Direct3D::Release();

	return 0;
}

//ウィンドウプロシージャ（何かあった時によばれる関数）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);  //プログラム終了
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}