#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Fbx.h"
#include "Stage.h"
#include "Resource.h"

using std::to_string;

struct Block {
    int type;
    int height;
}table_[XSIZE][ZSIZE];

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")
{
    for (int i = 0; i < MODEL_NUM; i++) {
        hModel_[i] = -1;
    }

    for (int x = 0; x < XSIZE; x++){
        for (int z = 0; z < ZSIZE; z++){
            table_[x][z].type = BLOCKTYPE::DEFAULT;
            table_[x][z].height = 0;
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
    controlId_ = IDC_RADIO_UP;

}

//�X�V
void Stage::Update()
{
    if (Input::IsMouseButtonDown(0)) {
        BlockWrite();
    }

}

void Stage::BlockWrite()
{
    float w = (float)(Direct3D::scrWidth / 2.0f);   //�r���[�|�[�g�s��
    float h = (float)(Direct3D::scrHeight / 2.0f);
    //Offsetx,y��0
    //minZ = 0 maxZ = 1
    XMMATRIX vp = {
        w, 0,0,0,
        0,-h,0,0,
        0, 0,1,0,
        w, h,0,1,
    };
    XMMATRIX intVP = XMMatrixInverse(nullptr, vp);                              //�r���[�|�[�g
    XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix()); //�v���W�F�N�V�����ϊ�    
    XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());       //�r���[�ϊ�
    //���C��-5���ړ������āA���߂���
    //constexpr float angleIncrement = XMConvertToRadians(-5.0f); // �p�x�����W�A���ɕϊ�
    //XMMATRIX rotationMatrix = XMMatrixRotationX(angleIncrement); // X������ɉ�]
    //invView = XMMatrixMultiply(rotationMatrix, invView); // �r���[�s��ɉ�]�s���K�p

    XMFLOAT3 mousePosFront = Input::GetMousePosition();
    mousePosFront.z = 0.0f;
    XMFLOAT3 mousePosBack = Input::GetMousePosition();
    mousePosBack.z = 1.0f;
    XMVECTOR vMouseFront = XMLoadFloat3(&mousePosFront);                            //�@�@mousePosFront���x�N�g���ɕϊ�    
    vMouseFront = XMVector3TransformCoord(vMouseFront, intVP * invProj * invView);  //�A�@�@��invVP, invPrj, intView��������    
    XMVECTOR vMouseBack = XMLoadFloat3(&mousePosBack);                              //�B�@mousePosBack���x�N�g���ɕϊ�    
    vMouseBack = XMVector3TransformCoord(vMouseBack, intVP * invProj * invView);    //�C�@�B��invVP, invPrj, invView��������

    rayHit_ = false;

    for (int x = 0; x < 15; x++) {
        for (int z = 0; z < 15; z++) {
            for (int y = 0; y < table_[x][z].height + 1; y++) {

                //�D�@�A����C�Ɍ������ă��C�����i�Ƃ肠�������f���ԍ���hModel_[0]�j
                RayCastData data;
                XMStoreFloat4(&data.start, vMouseFront);
                XMStoreFloat4(&data.dir, vMouseBack - vMouseFront);
                Transform trans;
                trans.position_.x = x;
                trans.position_.y = y;
                trans.position_.z = z;
                Model::SetTransform(hModel_[0], trans);
                Model::RayCast(hModel_[0], data);

                if (data.hit && !rayHit_) {
                    rayHit_ = true;
                    //�E���C������������u���[�N�|�C���g�Ŏ~�߂�
                    if (controlId_ == IDC_RADIO_UP) {
                        table_[x][z].height++;
                        break;
                    }
                    else if (controlId_ == IDC_RADIO_DOWN) {
                        if (y > 0) {
                            table_[x][z].height--;
                            break;
                        }
                    }
                    else if (controlId_ == IDC_RADIO_CHANGE) {
                        SetBlock(x, z, (BLOCKTYPE)(comboId_));
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

    for (int x = 0; x < 15; x++){
        for (int z = 0; z < 15; z++){
            for (int y = 0; y < table_[x][z].height + 1; y++){
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
    /*for (int x = 0; x < width_; x++){
        delete[] table_[x];
    }
    delete[]table_;*/
}

//Stage�̃_�C�A���O�v���V�[�W��
BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg){
    //�_�C�A���O���o������
    case WM_INITDIALOG:
        SendMessage(GetDlgItem(hDlg,IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);             //���W�I�{�^���̏�����
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"�f�t�H���g");    //�R���{�{�b�N�X�̏�����
        SendMessage(GetDlgItem(hDlg, ID_MENU_SAVE), BM_SETCHECK, BST_CHECKED, 0);             //���W�I�{�^���̏�����
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"�����K");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"��");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"��");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"��");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_SETCURSEL, 0, 0);
        return TRUE;
    case WM_COMMAND:
        controlId_ = LOWORD(wParam); // �R���g���[����ID���擾
        notificationCode_ = HIWORD(wParam); // �ʒm�R�[�h���擾
        comboId_ = SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_GETCURSEL, 0, 0);
        if (controlId_ == IDC_COMBO1 || notificationCode_ == CBN_SELCHANGE) {
            controlId_ = IDC_RADIO_CHANGE;
        }
        return TRUE;
    }
    return FALSE;
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

void Stage::Save()
{
    char fileName[MAX_PATH] = "����.map";
    std::string buffer;
    std::stringstream oss;

    //OPENFILENAME�\���̂�������
    OPENFILENAME ofn; {
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.lpstrFilter = TEXT("�}�b�v�f�[�^(*.map)\0*.map\0");
        ofn.lpstrFile = fileName;
        ofn.nMaxFile = MAX_PATH;
        ofn.Flags = OFN_OVERWRITEPROMPT;
        ofn.lpstrDefExt = TEXT("map");
    }

    //�t�@�C���ɕۑ�
    if (GetSaveFileName(&ofn)) {
        
        std::fstream outputFile(fileName, std::ios::binary | std::ios::out);
        for (int x = 0; x < XSIZE; x++) {
            for (int z = 0; z < ZSIZE; z++) {
                outputFile.write((char*)&table_[x][z], sizeof(Block));

            }
        }
        outputFile.close();
    }

}

//���[�h
void Stage::Load() 
{
    char fileName[MAX_PATH] = "����.map";
    std::string buffer;
    std::stringstream oss;

    //OPENFILENAME�\���̂�������
    OPENFILENAME ofn; {
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.lpstrFilter = TEXT("�}�b�v�f�[�^(*.map)\0*.map\0");
        ofn.lpstrFile = fileName;
        ofn.nMaxFile = MAX_PATH;
        ofn.Flags = OFN_FILEMUSTEXIST;
        ofn.lpstrDefExt = TEXT("map");
    }

    //�t�@�C�����J��
    if (GetOpenFileName(&ofn)) {
        std::fstream inputFile(fileName, std::ios::binary | std::ios::in);

        for (int x = 0; x < XSIZE; x++) {
            for (int z = 0; z < ZSIZE; z++) {
                inputFile.read((char*)&table_[x][z], sizeof(Block));
            }
        }
        inputFile.close();
    }
}

//bool Stage::IsWall(int x, int z)
//{
//    if (table_[x][z] == TYPE_WALL)
//    {
//        return true;
//    }
//}

    //���삵��Save�֐��̒��g
    //char fileName[MAX_PATH] = "�}�b�v�f�[�^.map";  //�t�@�C����������ϐ�

    ////�u�t�@�C����ۑ��v�_�C�A���O�̐ݒ�
    //OPENFILENAME ofn;                         	//���O�����ĕۑ��_�C�A���O�̐ݒ�p�\����
    //ZeroMemory(&ofn, sizeof(ofn));            	//�\���̏�����
    //ofn.lStructSize = sizeof(OPENFILENAME);   	//�\���̂̃T�C�Y
    //ofn.lpstrFilter = TEXT("�}�b�v�f�[�^(*.map)\0*.map\0")  //�����t�@�C���̎��
    //    TEXT("���ׂẴt�@�C��(*.*)\0*.*\0\0");             //����
    //ofn.lpstrFile = fileName;               	//�t�@�C����
    //ofn.nMaxFile = MAX_PATH;                  	//�p�X�̍ő啶����
    //ofn.Flags = OFN_OVERWRITEPROMPT;   		    //�t���O�i�����t�@�C�������݂�����㏑���m�F�j
    //ofn.lpstrDefExt = "map";                  	//�f�t�H���g�g���q

    ////�u�t�@�C����ۑ��v�_�C�A���O
    //BOOL selFile;
    //selFile = GetSaveFileName(&ofn);

    ////�L�����Z�������璆�f
    //if (selFile == FALSE) return;

    //HANDLE hFile;
    //hFile = CreateFile(
    //    fileName, //�t�@�C����
    //    GENERIC_WRITE,  //�A�N�Z�X���[�h
    //    0,
    //    NULL,
    //    CREATE_ALWAYS,  //�쐬���@
    //    FILE_ATTRIBUTE_NORMAL,
    //    NULL
    //);

    //string data = "";
    //for (int x = 0; x < XSIZE; x++) {
    //    for (int z = 0; z < ZSIZE; z++) {
    //        data += to_string(table_[x][z].type) + " "
    //            + to_string(table_[x][z].height) + "\n";
    //    }
    //    data + "\n";
    //}
    //const char* charData = data.c_str();

    ////data.length()
    //DWORD bytes = 0;
    //WriteFile(
    //    hFile,      //�t�@�C���n���h��
    //    charData,   //�ۑ�������������
    //    static_cast<DWORD>(data.length()),         //�ۑ����镶����
    //    &bytes,     //�ۑ������T�C�Y
    //    NULL
    //);

    //CloseHandle(hFile);
