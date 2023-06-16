#pragma once
#include"Direct3D.h"
#include"Texture.h"
#include<DirectXMath.h>
#include<vector>

using namespace DirectX;

#define SAFE_DELETE_ARRAY(p) if(p != nullptr){ delete[] }

class Sprite
{
	//コンスタントバッファー
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matW;
	};

	//頂点情報
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
	};

protected:
	UINT64 vertexNum_;
	std::vector<VERTEX> vertices_;
	ID3D11Buffer* pVertexBuffer_;

	UINT64 indexNum_;
	std::vector<int> index_;

	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;

	Texture* pTexture_;

public:
	Sprite();
	~Sprite();

	//初期化（ポリゴンを表示するための各種情報を準備）
	//戻り値:成功/失敗
	HRESULT Initialize();

	//描画
	//引数:worldMatrix ワールド行列
	void Draw(XMMATRIX& worldMatrix);

	//解放
	void Release();

private:
	//-----Initializeから呼ばれる関数-----
	virtual void InitVertexData(VERTEX* _ver, int _vn);		//頂点情報を準備
	HRESULT CreateVertexBuffer(VERTEX* _ver, int vn, int* _index, int in);		//頂点バッファを作成

	virtual void InitIndexData(int* _index, int _in);							//インデックス情報を準備
	HRESULT CreateIndexBuffer(VERTEX* _ver, int vn, int* _index, int in);		//インデックスバッファを作成

	HRESULT CreateConstantBuffer();							//コンスタントバッファを作成

	HRESULT LoadTexture();									//テクスチャをロード

	//-----Draw関数から呼ばれる関数-----
	void PassDataToCB(DirectX::XMMATRIX& worldMatrix);		//コンスタント
	void SetBufferToPipeline();								//各バッファを
};

