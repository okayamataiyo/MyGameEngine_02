#include "Engine/Model.h"
#include "Stage.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")
{

    for (int x = 0; x < MODEL_NUM; x++)
    {
        for (int z = 0; z < MODEL_NUM; z++)
        {
            hModel_[x] = -1;
            table_[x][z] = 0;
        }
    }

}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{

    string modelname[] = {
        "BoxDefault.fbx",
        "BoxBrick.fbx",
        "BoxGrass.fbx",
        "BoxSand.fbx",
        "BoxWater.fbx",
    };
    string fname_base = "assets/";

    //モデルデータのロード
    for (int i = 0; i < MODEL_NUM; i++){
        hModel_[i] = Model::Load(fname_base + modelname[i]);
        assert(hModel_[i] >= 0);
    }

    /*for (int i = 0; i < MODEL_NUM; i++) {
        hModel_[i] = -1;
    }*/
    for (int z = 0; z < ZSIZE; z++) {
        for (int x = 0; x < XSIZE; x++) {
            table_[x][z] = x%5;
        }
    }

    //tableにブロックのタイプをセット
}

//更新
void Stage::Update()
{
}

//描画
void Stage::Draw()
{
    Transform blockTrans;

    for (int x = 0; x < 15; x++)
    {
        for (int z = 0; z < 15; z++)
        {
            int type = table_[x][z];
            blockTrans.position_.x = x;
            blockTrans.position_.z = z;
            Model::SetTransform(hModel_[type], blockTrans);
            Model::Draw(hModel_[type]);
        }
    }

}

//開放
void Stage::Release()
{
    /*for (int x = 0; x < width_; x++)
    {
        delete[] table_[x];
    }
    delete[]table_;*/
}

//bool Stage::IsWall(int x, int z)
//{
//    if (table_[x][z] == TYPE_WALL)
//    {
//        return true;
//    }
//}