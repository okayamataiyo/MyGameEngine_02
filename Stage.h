#pragma once
#include "Engine/GameObject.h"
#include <Windows.h>

namespace 
{
    const int MODEL_NUM{ 5 };
    const int XSIZE{ 15 };
    const int ZSIZE{ 15 };
    enum BLOCKTYPE
    {
        DEFAULT, BRICK, GRASS, SAND, WATER
    };

    enum PUSHTYPE
    {
        ONE_PUSH,WAIT_MANY_PUSH,MANY_PUSH,FINISH,
    };
}

//Stage���Ǘ�����N���X
class Stage : public GameObject
{
private:

    //int mode_;          //0:�グ�� 1:������ 2:��ނ�ς���
    //int select_;        //���
    int hModel_[MODEL_NUM]; //���f���ԍ�
    int controlId_;     //�R���g���[����ID���擾
    int comboId_;       //�R���{��ID���擾
    int notificationCode_;  //�ʒm�R�[�h���擾
    int setComboId_;    //�R���{ID���Z�b�g
    bool rayHit_;       //���C���q�b�g�������ǂ����������t���O
    int pushType_;
    int timer_;         //�^�C�}�[ 
    int timerThresHold_;//�^�C�}�[��臒l
    bool pushFlag_;     //�{�^���������ꂽ���ǂ����������t���O
    //int table_[XSIZE][ZSIZE];
    //int width_, height_;

public:
    //�R���X�g���N�^
    //����:parent �e�I�u�W�F�N�g(SceneManager)
    Stage(GameObject* parent);

    ~Stage();    //�f�X�g���N�^

    void Initialize() override;    //������

    void Update() override;    //�X�V

    void BlockWrite();

    void Draw() override;    //�`��

    void Release() override;    //�J��

    BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);

    void SetBlock(int _x, int _z, BLOCKTYPE _type);

    void SetBlockHeight(int _x, int _z, int _y);

    void Save();    //�Z�[�u

    void Load();    //���[�h

    //�w�肵���ʒu���ʂ�邩�ʂ�Ȃ����𒲂ׂ�
    //����:x,z  ���ׂ�ʒu
    //�߂�l:�ʂ�Ȃ�=true/�ʂ�Ȃ�=false
    //bool IsWall(int x, int z);
};