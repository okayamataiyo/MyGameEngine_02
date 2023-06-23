#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
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
	int polygonCount_;	//�|���S����

	//�����o�ϐ�
	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;

public:
	Fbx();
	HRESULT Load(std::string fileName);
	void Draw(Transform& transform);
	void Release();
};

