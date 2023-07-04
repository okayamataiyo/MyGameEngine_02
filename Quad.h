#pragma once
#include <DirectXMath.h>
#include <vector>
#include "Direct3D.h"
#include "Texture.h"



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
	void Draw(XMMATRIX& worldMatrix);
	void Release();
	HRESULT CreateBuffers(VERTEX* _ver, int _vn, int* _index, int _in);

	void SetBuffers(int _in, XMMATRIX& worldMatrix);
private:
	virtual void InitVertexData();
	HRESULT CreateVertexBuffer();
	virtual void InitIndexData();
	HRESULT CreateIndexBuffer();
	HRESULT CreateConstantBuffer();
	HRESULT LoadTexture();

	//---------Draw�֐�����Ă΂��֐�---------
	void PassDataToCB(DirectX::XMMATRIX& worldMatrix);	//�R���X�^���g�o�b�t�@�Ɋe�����n��
	void SetBufferToPipeline();
};

