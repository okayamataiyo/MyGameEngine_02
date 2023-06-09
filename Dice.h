#pragma once
#include<DirectXMath.h>
#include"Direct3D.h"
#include"Texture.h"

using namespace DirectX;

struct CONSTANT_BUFFER
{
	XMMATRIX matWVP;
};

struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
};

class Dice
{
	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer* pIndexBuffer_;	//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ
	Texture* pTexture_;
public:
	//メンバ関数

	/// <summary>
	/// 四角形を表すクラスのコンストラクタ
	/// </summary>
	Dice();
	~Dice();
	HRESULT Initialize();
	void Draw(XMMATRIX& worldMatrix);
	void Release();
};

