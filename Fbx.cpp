#include "Fbx.h"

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

    //�}�l�[�W���J��
    pFbxManager->Destroy();
    return S_OK;
}
