#pragma once
#include <DirectXMath.h>
#include <vector>
#include "Direct3D.h"
#include "Texture.h"



using namespace DirectX;

//コンスタントバッファー
struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
	XMMATRIX	matNormal;
};

//頂点情報
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
	XMVECTOR normal;
};

class Quad
{
protected:
	int vertexNum_;
	std::vector<VERTEX> vertices_;
	int indexNum_;				//インデックス数
	std::vector<int> index_;	//インデックス情報

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
	HRESULT Initialize();
	void Draw(XMMATRIX& worldMatrix);
	void Release();
	HRESULT CreateBuffers(VERTEX* _ver, int _vn, int* _index, int _in);

	void SetBuffers(int _in, XMMATRIX& worldMatrix);
private:
	virtual void InitVertexData();
	HRESULT CreateVertexBuffer();
	virtual void InitIndexData();
	HRESULT CreateIndexBuffer();
	HRESULT CreateConstantBuffer();
	HRESULT LoadTexture();

	//---------Draw関数から呼ばれる関数---------
	void PassDataToCB(DirectX::XMMATRIX& worldMatrix);	//コンスタントバッファに各種情報を渡す
	void SetBufferToPipeline();
};

