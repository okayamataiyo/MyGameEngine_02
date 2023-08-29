#include "Engine/Model.h"
#include "Stage.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"),hModel_{-1,-1}//,table_(nullptr)
{
    ZeroMemory(table_, sizeof(table_));

    for (int x = 0; x < 15; x++)
    {
        for (int z = 0; z < 15; z++)
        {
            table_[x][z] = 0;
        }
    }
}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
    const char*fileName[] = { "Assets/BoxDefault.fbx" , "Assets/BoxBrick.fbx"};

    //���f���f�[�^�̃��[�h
    for (int i = 0; i < TYPE_MAX; i++)
    {
        hModel_[i] = Model::Load(fileName[i]);
        assert(hModel_[i] >= 0);
    }
}

//�X�V
void Stage::Update()
{
}

//�`��
void Stage::Draw()
{
    Transform blockTrans;

    for (int x = 0; x < 15; x++)
    {
        for (int z = 0; z < 15; z++)
        {
            blockTrans.position_.x = x;
            blockTrans.position_.z = z;

            int type = table_[x][z];
            Model::SetTransform(hModel_[type], blockTrans);
            Model::Draw(hModel_[type]);
        }
    }

}

//�J��
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