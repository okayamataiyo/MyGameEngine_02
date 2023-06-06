#pragma once
#include <DirectXMath.h>
#include "Direct3D.h"

using namespace DirectX;

//コンスタントバッファー
struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
};

class Quad
{
	//メンバ変数
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;	//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ
public:
	//メンバ関数
	
	/// <summary>
	/// 四角形を表すクラスのコンストラクタ
	/// </summary>
	Quad();
	~Quad();
	HRESULT Initialize();
	void Draw();
	void Release();
};

