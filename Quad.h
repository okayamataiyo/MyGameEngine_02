#pragma once
#include <DirectXMath.h>
#include "Direct3D.h"
#include "Texture.h"


using namespace DirectX;

//�R���X�^���g�o�b�t�@�[
struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
	XMMATRIX	matW;
};

//���_���
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
	XMVECTOR normal;
};

class Quad
{
	//�����o�ϐ�
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;	//�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@
	Texture* pTexture_;
public:
	//�����o�֐�
	
	/// <summary>
	/// �l�p�`��\���N���X�̃R���X�g���N�^
	/// </summary>
	Quad();
	~Quad();
	virtual HRESULT Initialize();
	virtual void Draw(XMMATRIX& worldMatrix);
	virtual void Release();
	HRESULT CreateBuffers(VERTEX* _ver, int vn, int* _index, int in);

	void SetBuffers(int _in, XMMATRIX& worldMatrix);
};

