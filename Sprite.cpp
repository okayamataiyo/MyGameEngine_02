#include "Sprite.h"
#include "Camera.h"

Sprite::Sprite()
	:vertexNum_(0),pVertexBuffer_(nullptr), indexNum_(0)
	,pIndexBuffer_(nullptr), pConstantBuffer_(nullptr),pTexture_(nullptr){


}

Sprite::~Sprite(){

	
}

HRESULT Sprite::Initialize() {
	
	HRESULT hr;
	// 頂点情報
	VERTEX vertices[] ={ //[4]でも同じ意味
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)},	// 四角形の頂点（左上)0
		{XMVectorSet( 1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)},	// 四角形の頂点（右上)1
		{XMVectorSet( 1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f)},	// 四角形の頂点（右下)2
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)},	// 四角形の頂点（左下)3	
	};

	vertexNum_ = sizeof(vertices);

	vertices_ = new VERTEX[4];

	//インデックス情報
	int index[] = {
		0,2,3, 0,1,2,
	};

	indexNum_ = sizeof(vertices);

	int indexSize = sizeof(index);
	index_ = new int[indexSize];


	InitVertexData();		//頂点情報を準備
	CreateVertexBuffer();	//頂点バッファを作成
	InitIndexData();		//インデックス情報を準備
	CreateIndexBuffer();	//インデックスバッファを作成
	LoadTexture();			//テクスチャをロード

	delete[] vertices_;

	return S_OK;
}

void Sprite::Draw(XMMATRIX& worldMatrix){

	PassDataToCB(worldMatrix);
	SetBufferToPipeline();
}

void Sprite::Release(){
	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
	SAFE_RELEASE(pTexture_);
}

void Sprite::InitVertexData(){

	// 頂点データ用バッファの設定
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(VERTEX) * vertexNum_;
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices_;

	Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
//	CreateVertexBuffer(bd_vertex, data_vertex);
}

HRESULT Sprite::CreateVertexBuffer(){

	//HRESULT hr;

	//if (FAILED(hr))
	//{
	//	MessageBox(nullptr, "頂点データ用バッファの設定にエラーが起きました", "エラー", MB_OK);
	//	return hr;
	//	//エラー処理
	//}
	return S_OK;
}

void Sprite::InitIndexData(){

	// インデックスバッファを生成する
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(int) * indexNum_;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index_;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	Direct3D::pDevice_->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	//CreateIndexBuffer(&bd, &InitData, pIndexBuffer_);
}

HRESULT Sprite::CreateIndexBuffer() {


	return S_OK;
}

HRESULT Sprite::CreateConstantBuffer(){

	HRESULT hr;

	//コンスタントバッファ作成
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// コンスタントバッファの作成
	hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, "頂点バッファの作成に失敗しました", "エラー", MB_OK);
		return hr;
		//エラー処理
	}

}

HRESULT Sprite::LoadTexture(){

	pTexture_ = new Texture();
	if (FAILED(pTexture_->Load("Assets\\dice.png"))) {

		return E_FAIL;
	}
}

void Sprite::PassDataToCB(DirectX::XMMATRIX& worldMatrix)
{
}

void Sprite::SetBufferToPipeline()
{

}


