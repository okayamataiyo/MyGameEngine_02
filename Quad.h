#pragma once
#include <DirectXMath.h>
#include "Direct3D.h"

using namespace DirectX;

//�R���X�^���g�o�b�t�@�[
struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
};

class Quad
{
	//�����o�ϐ�
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;	//�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@
public:
	//�����o�֐�
	Quad();
	~Quad();
	void Initialize();
	void Draw();
	void Release();
};

