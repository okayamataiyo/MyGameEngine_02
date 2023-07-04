#pragma once
#include"Direct3D.h"
#include"Texture.h"
#include<DirectXMath.h>
#include<vector>

using namespace DirectX;

#define SAFE_DELETE_ARRAY(p) if(p != nullptr){ delete[] }

class Sprite
{
	//�R���X�^���g�o�b�t�@�[
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matW;
	};

	//���_���
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
	};

protected:
	UINT64 vertexNum_;
	std::vector<VERTEX> vertices_;
	ID3D11Buffer* pVertexBuffer_;

	UINT64 indexNum_;
	std::vector<int> index_;

	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;

	Texture* pTexture_;

public:
	Sprite();
	~Sprite();

	//�������i�|���S����\�����邽�߂̊e����������j
	//�߂�l:����/���s
	HRESULT Initialize();

	//�`��
	//����:worldMatrix ���[���h�s��
	void Draw(XMMATRIX& worldMatrix);

	//���
	void Release();

private:
	//-----Initialize����Ă΂��֐�-----
	virtual void InitVertexData(VERTEX* _ver, int _vn);		//���_��������
	HRESULT CreateVertexBuffer(VERTEX* _ver, int vn, int* _index, int in);		//���_�o�b�t�@���쐬

	virtual void InitIndexData(int* _index, int _in);							//�C���f�b�N�X��������
	HRESULT CreateIndexBuffer(VERTEX* _ver, int vn, int* _index, int in);		//�C���f�b�N�X�o�b�t�@���쐬

	HRESULT CreateConstantBuffer();							//�R���X�^���g�o�b�t�@���쐬

	HRESULT LoadTexture();									//�e�N�X�`�������[�h

	//-----Draw�֐�����Ă΂��֐�-----
	void PassDataToCB(DirectX::XMMATRIX& worldMatrix);		//�R���X�^���g
	void SetBufferToPipeline();								//�e�o�b�t�@��
};

