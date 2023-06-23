#include "Fbx.h"

HRESULT Fbx::Load(std::string fileName)
{
    //マネージャを作成
    FbxManager* pFbxManager = FbxManager::Create();

    //インポーターを作成
    FbxImporter* fbxImporter = FbxImporter::Create(pFbxManager, "imp");
    fbxImporter->Initialize(fileName.c_str(), -1, pFbxManager->GetIOSettings());

    //シーンオブジェクトにFBXファイルの情報を流し込む
    FbxScene* pFbxScene = FbxScene::Create(pFbxManager, "fbxscene");
    fbxImporter->Import(pFbxScene);
    fbxImporter->Destroy();

    //メッシュ情報を取得
    FbxNode* rootNode = pFbxScene->GetRootNode();
    FbxNode* pNode = rootNode->GetChild(0);
    FbxMesh* mesh = pNode->GetMesh();

    //各情報の個数を取得

    vertexCount_ = mesh->GetControlPointsCount();	//頂点の数

    polygonCount_ = mesh->GetPolygonCount();	//ポリゴンの数

    //マネージャ開放
    pFbxManager->Destroy();
    return S_OK;
}
