#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Direct3D.h"
#include "Transform.h"

#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

class Texture;

class Fbx
{
	//�}�e���A��
	struct MATERIAL
	{
		Texture* pTexture;
	};

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
	int polygonCount_;	//�|���S����
	int materialCount_;	//�}�e���A���̌�

	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;	//�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@
	MATERIAL* pMaterialList_;

	void InitVertex(fbxsdk::FbxMesh* mesh);
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void InitConstantBuffer();

	void InitMaterial(fbxsdk::FbxNode* pNode);

public:
	//�����o�֐�
	Fbx();
	HRESULT Load(std::string fileName);
	
	
	void Draw(Transform& transform);
	void Release();
};

