#pragma once
#include <DirectXMath.h>
#include "Direct3D.h"
#include "Texture.h"


using namespace DirectX;

//コンスタントバッファー
struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
};

//頂点情報
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
};

class Quad
{
	//メンバ変数
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;	//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ
	Texture* pTexture_;
public:
	//メンバ関数
	
	/// <summary>
	/// 四角形を表すクラスのコンストラクタ
	/// </summary>
	Quad();
	~Quad();
	virtual HRESULT Initialize();
	virtual void Draw(XMMATRIX& worldMatrix);
	virtual void Release();
	HRESULT CreateBuffers(VERTEX* _ver, int vn, int* _index, int in);

	void SetBuffers(int _in, XMMATRIX& worldMatrix);
};

