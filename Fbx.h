#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Direct3D.h"
#include "Texture.h"
#include "Transform.h"

#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MT.lib")
#pragma comment(lib, "zlib-MT.lib")

class Fbx
{
	//コンスタントバッファー
	struct CONSTANT_BUFFER {
		XMMATRIX matWVP;
		XMMATRIX matNormal;
	};

	//頂点情報
	struct VERTEX {
		XMVECTOR position;
	};

	int vertexCount_;	//頂点数	FBXファイルを扱うために必要になる変数を宣言する。
	VERTEX vertices_;
	int polygonCount_;	//ポリゴン数

	//メンバ変数
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;	//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ
	Texture* pTexture_;

public:
	//メンバ関数
	Fbx();
	HRESULT Load(std::string fileName);
	void InitVertex(fbxsdk::FbxMesh* mesh);
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void InitConstantBuffer();
	HRESULT CreateIndexBuffer();
	void Draw(Transform& transform);
	void Release();
};

