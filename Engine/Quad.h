#pragma once
#include <DirectXMath.h>
#include <vector>
#include "Direct3D.h"
#include "Texture.h"
#include "Transform.h"



using namespace DirectX;

//�R���X�^���g�o�b�t�@�[
struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
	XMMATRIX	matNormal;
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
protected:
	int vertexNum_;
	std::vector<VERTEX> vertices_;
	int indexNum_;				//�C���f�b�N�X��
	std::vector<int> index_;	//�C���f�b�N�X���

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
	HRESULT Initialize();
	void Draw(Transform& transform);
	void Release();
private:
	virtual void InitVertexData();
	HRESULT CreateVertexBuffer();
	virtual void InitIndexData();
	HRESULT CreateIndexBuffer();
	HRESULT CreateConstantBuffer();
	HRESULT LoadTexture();

	//---------Draw�֐�����Ă΂��֐�---------
	void PassDataToCB(Transform transform);	//�R���X�^���g�o�b�t�@�Ɋe�����n��
	void SetBufferToPipeline();
};
