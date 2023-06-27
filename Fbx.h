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
	//�R���X�^���g�o�b�t�@�[
	struct CONSTANT_BUFFER {
		XMMATRIX matWVP;
		XMMATRIX matNormal;
	};

	//���_���
	struct VERTEX {
		XMVECTOR position;
	};

	int vertexCount_;	//���_��	FBX�t�@�C�����������߂ɕK�v�ɂȂ�ϐ���錾����B
	VERTEX vertices_;
	int polygonCount_;	//�|���S����

	//�����o�ϐ�
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;	//�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@
	Texture* pTexture_;

public:
	//�����o�֐�
	Fbx();
	HRESULT Load(std::string fileName);
	void InitVertex(fbxsdk::FbxMesh* mesh);
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void InitConstantBuffer();
	HRESULT CreateIndexBuffer();
	void Draw(Transform& transform);
	void Release();
};

