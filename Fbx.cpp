#include "Camera.h"
#include "Fbx.h"


Fbx::Fbx()
    :vertexCount_(0),polygonCount_(0),pTexture_(nullptr),
    pVertexBuffer_(nullptr),pIndexBuffer_(nullptr),pConstantBuffer_(nullptr)
{
}

HRESULT Fbx::Load(std::string fileName)
{
    //�}�l�[�W�����쐬
    FbxManager* pFbxManager = FbxManager::Create();

    //�C���|�[�^�[���쐬
    FbxImporter* fbxImporter = FbxImporter::Create(pFbxManager, "imp");
    fbxImporter->Initialize(fileName.c_str(), -1, pFbxManager->GetIOSettings());

    //�V�[���I�u�W�F�N�g��FBX�t�@�C���̏��𗬂�����
    FbxScene* pFbxScene = FbxScene::Create(pFbxManager, "fbxscene");
    fbxImporter->Import(pFbxScene);
    fbxImporter->Destroy();

    //���b�V�������擾
    FbxNode* rootNode = pFbxScene->GetRootNode();
    FbxNode* pNode = rootNode->GetChild(0);
    FbxMesh* mesh = pNode->GetMesh();

    //�e���̌����擾

    vertexCount_ = mesh->GetControlPointsCount();	//���_�̐�

    polygonCount_ = mesh->GetPolygonCount();	//�|���S���̐�

    InitVertex(mesh);		//���_�o�b�t�@����

    InitIndex(mesh);		//�C���f�b�N�X�o�b�t�@����

    InitConstantBuffer();	//�R���X�^���g�o�b�t�@����

    //�}�l�[�W���J��
    pFbxManager->Destroy();
    return S_OK;
}

//���_�o�b�t�@����
void Fbx::InitVertex(fbxsdk::FbxMesh* mesh)
{
    //���_��������z��
    VERTEX* vertices = new VERTEX[vertexCount_];

    //�S�|���S��
    for (DWORD poly = 0; poly < polygonCount_; poly++)
    {
        //3���_��
        for (int vertex = 0; vertex < 3; vertex++)
        {
            //���ׂ钸�_�̔ԍ�
            int index = mesh->GetPolygonVertex(poly, vertex);

            //���_�̈ʒu
            FbxVector4 pos = mesh->GetControlPointAt(index);
            vertices[index].position = XMVectorSet((float)pos[0], (float)pos[1], (float)pos[2], 0.0f);
        }
    }

    // ���_�o�b�t�@�쐬
    HRESULT hr;
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(VERTEX) * vertexCount_;
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;
	hr = Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(NULL, "���_�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
	}
}

//�C���f�b�N�X�o�b�t�@����
void Fbx::InitIndex(fbxsdk::FbxMesh* mesh)
{
    int* index = new int[polygonCount_ * 3];
    int count = 0;

    //�S�|���S��
    for (DWORD poly = 0; poly < polygonCount_; poly++)
    {
        //3���_��
        for (DWORD vertex = 0; vertex < 3; vertex++)
        {
            index[count] = mesh->GetPolygonVertex(poly, vertex);
            count++;
        }
    }
}

void Fbx::InitConstantBuffer()
{
    D3D11_BUFFER_DESC cb;
    cb.ByteWidth = sizeof(CONSTANT_BUFFER);
    cb.Usage = D3D11_USAGE_DYNAMIC;
    cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cb.MiscFlags = 0;
    cb.StructureByteStride = 0;
    // �R���X�^���g�o�b�t�@�̍쐬
    HRESULT hr;
    hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
    if (FAILED(hr))
    {
        MessageBox(NULL, "�R���X�^���g�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
    }
}

HRESULT Fbx::CreateIndexBuffer()
{
    //���_��������z��
    VERTEX* vertices = new VERTEX[polygonCount_];
    // �C���f�b�N�X�o�b�t�@�𐶐�����
    D3D11_BUFFER_DESC   bd;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(int) * polygonCount_;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA InitData;
    InitData.pSysMem = vertices;
    InitData.SysMemPitch = 0;
    InitData.SysMemSlicePitch = 0;

    HRESULT hr;
    hr = Direct3D::pDevice_->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
    if (FAILED(hr))
    {
        MessageBox(NULL, "�C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
        return hr;
    }
    return S_OK;
}


//�e�N�X�`�������[�h
void Fbx::Draw(Transform& transform)
{
    pTexture_ = new Texture;
    HRESULT hr;
    hr = pTexture_->Load("Assets\\Oden_01.fbx");
    if (FAILED(hr))
    {
        MessageBox(NULL, "�e�N�X�`���̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
    }
}

void Fbx::Release()
{
    SAFE_RELEASE(pConstantBuffer_);
    SAFE_RELEASE(pIndexBuffer_);
    SAFE_RELEASE(pVertexBuffer_);
}
