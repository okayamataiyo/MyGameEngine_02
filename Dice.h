#pragma once
#include<DirectXMath.h>
#include"Direct3D.h"
#include"Texture.h"

using namespace DirectX;

struct CONSTANT_BUFFER
{
	XMMATRIX matWVP;
};

struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
};

class Dice
{
	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer* pIndexBuffer_;	//�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@
	Texture* pTexture_;
public:
	//�����o�֐�

	/// <summary>
	/// �l�p�`��\���N���X�̃R���X�g���N�^
	/// </summary>
	Dice();
	~Dice();
	HRESULT Initialize();
	void Draw(XMMATRIX& worldMatrix);
	void Release();
};

