#include"Controller.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"


enum
{
};

//�R���X�g���N�^
Controller::Controller(GameObject* parent)
    :GameObject(parent, "Controller"), hModel_(-1)
{
}

//�f�X�g���N�^
Controller::~Controller()
{
}

//������
void Controller::Initialize()
{
    ////���f���f�[�^�̃��[�h
    //hModel_ = Model::Load("Assets/BoxWater.fbx");
    //assert(hModel_ >= 0);

    transform_.position_.x = 7.0f;
    transform_.position_.z = 7.0f;
    transform_.position_.y = -0.0001f;

    //Instantiate<ControllerHead>(this);
}

//�X�V
void Controller::Update()
{
    //if (Input::IsKey(DIK_A))
    //{
    //    //���炩�̏���
    //    transform_.rotate_.y += -1.0f;     // 1dd������]
    //}

    //if (Input::IsKey(DIK_D))
    //{
    //    //���炩�̏���
    //    transform_.rotate_.y += 1.0f;     // 1������]
    //}

    //Debug::Log("angle = ");
    //Debug::Log(transform_.rotate_.y, true);

    //transform_.rotate_.y�x��]������s����쐬
    XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));

    //��Ԃ̌��ݒn���x�N�g���^�ɕϊ�
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    //�ړ��x�N�g��
    XMVECTOR frontMove = XMVectorSet(0, 0, 0.1f, 0);          //��������XMVECTOR�\���̂�p�ӂ�
    frontMove = XMVector3TransformCoord(frontMove, mRotY);    //�ړ��x�N�g����]
    XMVECTOR rightMove = XMVectorSet(0.1f, 0, 0, 0);
    rightMove = XMVector3TransformCoord(rightMove, mRotY);

    XMVECTOR vMove1{ 0.0f, 0.0f, 0.1f, 0.0f };          //����0.1m
    vMove1 = XMVector3TransformCoord(vMove1, mRotY);    //�ړ��x�N�g����ϊ�������
    XMVECTOR vMove2{ 0.1f, 0.0f, 0.0f, 0.0f };          //����0.1m
    vMove2 = XMVector3TransformCoord(vMove2, mRotY);
    XMVECTOR vMove3{ 0.0f, 0.1f, 0.0f, 0.0f };          //�c��0.1m
    vMove3 = XMVector3TransformCoord(vMove3, mRotY);

    //W�L�[�������ꂽ��ړ�
    if (Input::IsKey(DIK_W))
    {
        //�ړ�
        vPos += vMove1;
        vPos += frontMove;

        //���ݒn���x�N�g�����炢����transform_.position_�ɖ߂�
        XMStoreFloat3(&transform_.position_, vPos);
    }

    //S�L�[�������ꂽ��ړ�
    if (Input::IsKey(DIK_S))
    {
        //�ړ�
        vPos -= vMove1;
        vPos -= frontMove;

        //���ݒn���x�N�g�����炢����transform_.position_�ɖ߂�
        XMStoreFloat3(&transform_.position_, vPos);
    }

    if (Input::IsKey(DIK_D))
    {
        //���炩�̏���
        //transform_.rotate_.y += -1.0f;     // 1dd������]
        // 
        //�ړ�
        vPos += vMove2;
        vPos += rightMove;

        //���ݒn���x�N�g�����炢����transform_.position_�ɖ߂�
        XMStoreFloat3(&transform_.position_, vPos);
    }

    if (Input::IsKey(DIK_A))
    {
        //���炩�̏���
        //transform_.rotate_.y += 1.0f;     // 1dd������]
        //�ړ�
        vPos -= vMove2;
        vPos -= rightMove;

        //���ݒn���x�N�g�����炢����transform_.position_�ɖ߂�
        XMStoreFloat3(&transform_.position_, vPos);
    }

    if (Input::IsKey(DIK_UP))
    {
        /*vPos += vMove3;

        XMStoreFloat3(&transform_.position_, vPos);*/

        if(transform_.rotate_.x <= 45) transform_.rotate_.x += 1.0f;     // 1dd������]
    }

    if (Input::IsKey(DIK_DOWN))
    {
        /*vPos += vMove1;

        XMStoreFloat3(&transform_.position_, vPos);*/
        if(transform_.rotate_.x >= -30) transform_.rotate_.x += -1.0f;     // 1dd������]
    }

    if (Input::IsKey(DIK_LEFT))
    {
        //���炩�̏���
        transform_.rotate_.y += -1.0f;     // 1dd������]
    }

    if (Input::IsKey(DIK_RIGHT))
    {
        //���炩�̏���
        transform_.rotate_.y += 1.0f;     // 1dd������]
    }



    /*Camera::SetTarget(transform_.position_);
    XMFLOAT3 camPos = transform_.position_;
    camPos.y += 5;
    camPos.z -= 10;
    Camera::SetPosition(camPos);*/

    //�J����
    XMVECTOR vCam = { 0, 7, -10, 0 };              //���B��_�p��
    vCam = XMVector3TransformCoord(vCam, mRotX * mRotY);    //���B��_��]
    //vCam = XMVector3TransformCoord(vCam, mRotX);
    //XMFLOAT3 camPos;
    //XMStoreFloat3(&camPos, vPos + vCam);
    Camera::SetPosition(vPos+ vCam);            //�J�����̈ʒu�͎��B��_�̐�[
    Camera::SetTarget(transform_.position_);    //�J�����̌���ʒu�͂��̃I�u�W�F�N�g�̈ʒu

}

    //Ground* pGround = (Ground*)FindObject("Ground");    //�X�e�[�W�I�u�W�F�N�g��T��
    //int hGroundModel = pGround->GetModelHandle();    //���f���ԍ����擾

    //RayCastData data;
    //data.start = transform_.position_;   //���C�̔��ˈʒu
    //data.start.y = 0;
    //data.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
    //Model::RayCast(hGroundModel, &data); //���C�𔭎�


    /*if (data.hit == true)
    {
    }*/
    //    transform_.position_.y = -data.dist;

//�`��
void Controller::Draw()
{
   /* Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);*/
}

//�J��
void Controller::Release()
{
}