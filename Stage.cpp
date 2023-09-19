#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Fbx.h"
#include "Stage.h"
#include "Resource.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")
{
    for (int i = 0; i < MODEL_NUM; i++) {
        hModel_[i] = -1;
    }

    for (int x = 0; x < MODEL_NUM; x++)
    {
        for (int z = 0; z < MODEL_NUM; z++)
        {
            SetBlock(x, z, DEFAULT);
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

    string modelname[] = {
        "BoxDefault.fbx",
        "BoxBrick.fbx",
        "BoxGrass.fbx",
        "BoxSand.fbx",
        "BoxWater.fbx",
    };
    string fname_base = "assets/";

    //���f���f�[�^�̃��[�h
    for (int i = 0; i < MODEL_NUM; i++){
        hModel_[i] = Model::Load(fname_base + modelname[i]);
        assert(hModel_[i] >= 0);
    }

    /*for (int i = 0; i < MODEL_NUM; i++) {
        hModel_[i] = -1;
    }*/
    //table�Ƀu���b�N�̃^�C�v���Z�b�g
    for (int z = 0; z < ZSIZE; z++) {
        for (int x = 0; x < XSIZE; x++) {
            SetBlock(x, z, (BLOCKTYPE)(0));
            SetBlockHeight(x, z, 0);
        }
    }
    controlId = IDC_RADIO_UP;
    
}

//�X�V
void Stage::Update()
{
    if (!Input::IsMouseButtonDown(0)) {
        return;
    }
    //�r���[�|�[�g�s��
    float w = (float)(Direct3D::scrWidth / 2.0f);
    float h = (float)(Direct3D::scrHeight / 2.0f);
    //Offsetx,y��0
    //minZ = 0 maxZ = 1
    XMMATRIX vp = 
    {
        w, 0,0,0,
        0,-h,0,0,
        0, 0,1,0,
        w, h,0,1,
    };
    //�r���[�|�[�g
    XMMATRIX intVP = XMMatrixInverse(nullptr, vp);
    //�v���W�F�N�V�����ϊ�
    XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
    //�r���[�ϊ�
    XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());
    XMFLOAT3 mousePosFront = Input::GetMousePosition();
    mousePosFront.z = 0.0f;
    XMFLOAT3 mousePosBack = Input::GetMousePosition();
    mousePosBack.z = 1.0f;
    //�@�@mousePosFront���x�N�g���ɕϊ�
    XMVECTOR vMouseFront = XMLoadFloat3(&mousePosFront);
    //�A�@�@��invVP, invPrj, intView��������
    vMouseFront = XMVector3TransformCoord(vMouseFront,intVP * invProj * invView );
    //�B�@mousePosBack���x�N�g���ɕϊ�
    XMVECTOR vMouseBack = XMLoadFloat3(&mousePosBack);
    //�C�@�B��invVP, invPrj, invView��������
    vMouseBack = XMVector3TransformCoord(vMouseBack,intVP * invProj * invView );

    for (int x = 0; x < 15; x++) {
        for (int z = 0; z < 15; z++) {
            for (int y = 0; y < table_[x][z].height + 1; y++) {

                //�D�@�A����C�Ɍ������ă��C�����i�Ƃ肠�������f���ԍ���hModel_[0]�j
                RayCastData data;
                XMStoreFloat4(&data.start, vMouseFront);
                XMStoreFloat4(&data.dir, vMouseBack- vMouseFront);
                Transform trans;
                trans.position_.x = x;
                trans.position_.y = y;
                trans.position_.z = z;
                Model::SetTransform(hModel_[0], trans);

                Model::RayCast(hModel_[0], data);

                if (data.hit) {
                    //�E���C������������u���[�N�|�C���g�Ŏ~�߂�
                    if (controlId == IDC_RADIO_UP) {
                        table_[x][z].height++;
                        break;
                    }
                    else if (controlId == IDC_RADIO_DOWN) {
                        if (y > 0) {
                            table_[x][z].height--;
                            break;
                        }
                    }
                    else if (controlId == IDC_RADIO_CHANGE) {
                        SetBlock(x, z, (BLOCKTYPE)(comboId));
                        break;
                    }
                }
            }
        }
    }
}

//�`��
void Stage::Draw()
{
    Transform blockTrans;

    for (int x = 0; x < 15; x++)
    {
        for (int z = 0; z < 15; z++)
        {
            for (int y = 0; y < table_[x][z].height + 1; y++)
            {
                int type = table_[x][z].type;

                blockTrans.position_.x = x;
                blockTrans.position_.z = z;
                blockTrans.position_.y = y;

                Model::SetTransform(hModel_[type], blockTrans);
                Model::Draw(hModel_[type]);
            }
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

//Stage�̃_�C�A���O�v���V�[�W��
BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    //�_�C�A���O���o������
    case WM_INITDIALOG:
        SendMessage(GetDlgItem(hDlg,IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);             //���W�I�{�^���̏�����
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"�f�t�H���g");    //�R���{�{�b�N�X�̏�����
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"�����K");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"��");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"��");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"��");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_SETCURSEL, 0, 0);
        return 0;
    case WM_COMMAND:
        controlId = LOWORD(wParam); // �R���g���[����ID���擾
        notificationCode = HIWORD(wParam); // �ʒm�R�[�h���擾
        
        if (controlId == IDC_COMBO1 || notificationCode == CBN_SELCHANGE) {
            comboId = SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_GETCURSEL, 0, 0);
            controlId = IDC_RADIO_CHANGE;
        }
        return 0;
    }
    return DefWindowProc(hDlg, msg, wParam, lParam);
}

void Stage::SetBlock(int _x, int _z, BLOCKTYPE _type)
{
    //�G���[�`�F�b�N �͈͓��̒l���ǂ���
    table_[_x][_z].type = _type;
}

void Stage::SetBlockHeight(int _x, int _z, int _y)
{
    table_[_x][_z].height = _y;
}



//bool Stage::IsWall(int x, int z)
//{
//    if (table_[x][z] == TYPE_WALL)
//    {
//        return true;
//    }
//}

