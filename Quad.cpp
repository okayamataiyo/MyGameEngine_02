#include "Quad.h"
#include "Camera.h"

Quad::Quad():
	pVertexBuffer_(nullptr),pIndexBuffer_(nullptr), pConstantBuffer_(nullptr)
{

}

Quad::~Quad()
{
	Release();
}

HRESULT Quad::Initialize()
{
	HRESULT hr;
	// 頂点情報
	XMVECTOR vertices[] = //[4]でも同じ意味
	{
		XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),	// 四角形の頂点（左上)0
		XMVectorSet( 1.0f,  1.0f, 0.0f, 0.0f),	// 四角形の頂点（右上)1
		XMVectorSet( 1.0f, -1.0f, 0.0f, 0.0f),	// 四角形の頂点（右下)2
		XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),	// 四角形の頂点（左下)3	
//		XMVectorSet( 0.0f,  2.0f, 0.0f, 0.0f),
	};

	// 頂点データ用バッファの設定
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(vertices);
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;

	hr = Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr))
	{
		//エラー処理,早期リターン
		OutputDebugString("頂点データ用バッファの設定に失敗");
		return hr;
	}

	//インデックス情報
	int index[] = { 0,2,3, 0,1,2,};// 0, 4, 1};

	// インデックスバッファを生成する
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(index);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	hr = Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	if (FAILED(hr))
	{
		//エラー処理,早期リターン
		OutputDebugString("インデックスバッファの作成に失敗");
		return hr;
	}

	//コンスタントバッファ作成
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// コンスタントバッファの作成
	hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		//エラー処理,早期リターン
		OutputDebugString("コンストラクタバッファの作成に失敗");
		return hr;
	}
	
	return S_OK;
}

void Quad::Draw(XMMATRIX& worldMatrix)
{
	//コンスタントバッファに渡す情報
	
	
	
	



	D3D11_MAPPED_SUBRESOURCE pdata;
	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(worldMatrix * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
	Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	//GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));					//データを値を送る
	Direct3D::pContext->Unmap(pConstantBuffer_, 0);										//再開

	//頂点バッファ
	UINT stride = sizeof(XMVECTOR);
	UINT offset = 0;
	Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
	Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用

//	Direct3D::pContext->DrawIndexed(9, 0, 0);
	Direct3D::pContext->DrawIndexed(6, 0, 0);//6は頂点の数を決めている	
}

void Quad::Release()
{
	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}