#pragma once
#include "Engine/GameObject.h"

namespace {
    const int MODEL_NUM{ 5 };
    const int XSIZE{ 15 };
    const int ZSIZE{ 15 };
    enum BLOCKTYPE
    {
        DEFAULT, BRICK, GRASS, SAND, WATER
    };
}

//Stage���Ǘ�����N���X
class Stage : public GameObject
{
    struct Block {
        int type;
        int height;
    }table_[XSIZE][ZSIZE];

    int hModel_[MODEL_NUM];    //���f���ԍ�
    //int table_[XSIZE][ZSIZE];
    //int width_, height_;

public:
    //�R���X�g���N�^
    //����:parent �e�I�u�W�F�N�g(SceneManager)
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void SetBlock(int _x, int _z, BLOCKTYPE _type);

    void SetBlockHeight(int _x, int _z, int _y);



    //�w�肵���ʒu���ʂ�邩�ʂ�Ȃ����𒲂ׂ�
    //����:x,z  ���ׂ�ʒu
    //�߂�l:�ʂ�Ȃ�=true/�ʂ�Ȃ�=false
    //bool IsWall(int x, int z);
};