#include "Sprite.h"
#include "Camera.h"

Sprite::Sprite() :pVertexBuffer_(nullptr), pIndexBuffer_(nullptr), pConstantBuffer_(nullptr)
{

}

Sprite::~Sprite()
{
	Release();
}

HRESULT Sprite::Initialize() {
	
	HRESULT hr;
	// ���_���
	VERTEX vertices[] = //[4]�ł������Ӗ�
	{
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i����)0
		{XMVectorSet( 1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�E��)1
		{XMVectorSet( 1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�E��)2
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i����)3	
	};

	//�C���f�b�N�X���
	int index[] = {
		0,2,3, 0,1,2,
	};

	CreateIndexBuffer(vertices, 4, index, 6);

	return S_OK;
}

void Sprite::Draw(XMMATRIX& worldMatrix){
	PassDataToCB();

	SetBufferToPipeline(6, worldMatrix);
}

void Sprite::Release()
{
	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
	SAFE_RELEASE(pTexture_);
}

void Sprite::InitVertexData(VERTEX* _ver, int _vn){

	// ���_�f�[�^�p�o�b�t�@�̐ݒ�
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(VERTEX) * _vn;
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = _ver;

	CreateVertexBuffer(bd_vertex, data_vertex);
}

HRESULT Sprite::CreateVertexBuffer(VERTEX* _ver, int vn, int* _index, int in){

	HRESULT hr;

	hr = Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, "���_�f�[�^�p�o�b�t�@�̐ݒ�ɃG���[���N���܂���", "�G���[", MB_OK);
		return hr;
		//�G���[����
	}
}

void Sprite::InitIndexData(int* _index, int _in){

	// �C���f�b�N�X�o�b�t�@�𐶐�����
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(int) * _in;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = _index;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	CreateIndexBuffer(&bd, &InitData, pIndexBuffer_);
}

HRESULT Sprite::CreateIndexBuffer(VERTEX* _ver, int vn, int* _index, int in) {

	HRESULT hr;

	if (FAILED(hr))
	{
		MessageBox(nullptr, "�C���f�b�N�X�o�b�t�@�̐����Ɏ��s���܂���", "�G���[", MB_OK);
		return hr;
		//�G���[����
	}
	
}

HRESULT Sprite::CreateConstantBuffer(){

	HRESULT hr;

	//�R���X�^���g�o�b�t�@�쐬
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// �R���X�^���g�o�b�t�@�̍쐬
	hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, "���_�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return hr;
		//�G���[����
	}
	pTexture_ = new Texture;
	pTexture_->Load("Assets\\dice.png");
	return S_OK;
}

HRESULT Sprite::LoadTexture(){

	pTexture_ = new Texture;
	pTexture_->Load("Assets\\dice.png");
	return S_OK;
}


