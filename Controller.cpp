#include"Controller.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"


enum
{
};

//コンストラクタ
Controller::Controller(GameObject* parent)
    :GameObject(parent, "Controller"), hModel_(-1)
{
}

//デストラクタ
Controller::~Controller()
{
}

//初期化
void Controller::Initialize()
{
    ////モデルデータのロード
    //hModel_ = Model::Load("Assets/BoxWater.fbx");
    //assert(hModel_ >= 0);

    transform_.position_.x = 7.0f;
    transform_.position_.z = 7.0f;
    transform_.position_.y = -0.0001f;

    //Instantiate<ControllerHead>(this);
}

//更新
void Controller::Update()
{
    //if (Input::IsKey(DIK_A))
    //{
    //    //何らかの処理
    //    transform_.rotate_.y += -1.0f;     // 1dd°ずつ回転
    //}

    //if (Input::IsKey(DIK_D))
    //{
    //    //何らかの処理
    //    transform_.rotate_.y += 1.0f;     // 1°ずつ回転
    //}

    //Debug::Log("angle = ");
    //Debug::Log(transform_.rotate_.y, true);

    //transform_.rotate_.y度回転させる行列を作成
    XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));

    //戦車の現在地をベクトル型に変換
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    //移動ベクトル
    XMVECTOR frontMove = XMVectorSet(0, 0, 0.1f, 0);          //奥向きのXMVECTOR構造体を用意し
    frontMove = XMVector3TransformCoord(frontMove, mRotY);    //移動ベクトル回転
    XMVECTOR rightMove = XMVectorSet(0.1f, 0, 0, 0);
    rightMove = XMVector3TransformCoord(rightMove, mRotY);

    XMVECTOR vMove1{ 0.0f, 0.0f, 0.1f, 0.0f };          //奥に0.1m
    vMove1 = XMVector3TransformCoord(vMove1, mRotY);    //移動ベクトルを変換させる
    XMVECTOR vMove2{ 0.1f, 0.0f, 0.0f, 0.0f };          //横に0.1m
    vMove2 = XMVector3TransformCoord(vMove2, mRotY);
    XMVECTOR vMove3{ 0.0f, 0.1f, 0.0f, 0.0f };          //縦に0.1m
    vMove3 = XMVector3TransformCoord(vMove3, mRotY);

    //Wキーが押されたら移動
    if (Input::IsKey(DIK_W))
    {
        //移動
        vPos += vMove1;
        vPos += frontMove;

        //現在地をベクトルからいつものtransform_.position_に戻す
        XMStoreFloat3(&transform_.position_, vPos);
    }

    //Sキーが押されたら移動
    if (Input::IsKey(DIK_S))
    {
        //移動
        vPos -= vMove1;
        vPos -= frontMove;

        //現在地をベクトルからいつものtransform_.position_に戻す
        XMStoreFloat3(&transform_.position_, vPos);
    }

    if (Input::IsKey(DIK_D))
    {
        //何らかの処理
        //transform_.rotate_.y += -1.0f;     // 1dd°ずつ回転
        // 
        //移動
        vPos += vMove2;
        vPos += rightMove;

        //現在地をベクトルからいつものtransform_.position_に戻す
        XMStoreFloat3(&transform_.position_, vPos);
    }

    if (Input::IsKey(DIK_A))
    {
        //何らかの処理
        //transform_.rotate_.y += 1.0f;     // 1dd°ずつ回転
        //移動
        vPos -= vMove2;
        vPos -= rightMove;

        //現在地をベクトルからいつものtransform_.position_に戻す
        XMStoreFloat3(&transform_.position_, vPos);
    }

    if (Input::IsKey(DIK_UP))
    {
        /*vPos += vMove3;

        XMStoreFloat3(&transform_.position_, vPos);*/

        if(transform_.rotate_.x <= 45) transform_.rotate_.x += 1.0f;     // 1dd°ずつ回転
    }

    if (Input::IsKey(DIK_DOWN))
    {
        /*vPos += vMove1;

        XMStoreFloat3(&transform_.position_, vPos);*/
        if(transform_.rotate_.x >= -30) transform_.rotate_.x += -1.0f;     // 1dd°ずつ回転
    }

    if (Input::IsKey(DIK_LEFT))
    {
        //何らかの処理
        transform_.rotate_.y += -1.0f;     // 1dd°ずつ回転
    }

    if (Input::IsKey(DIK_RIGHT))
    {
        //何らかの処理
        transform_.rotate_.y += 1.0f;     // 1dd°ずつ回転
    }



    /*Camera::SetTarget(transform_.position_);
    XMFLOAT3 camPos = transform_.position_;
    camPos.y += 5;
    camPos.z -= 10;
    Camera::SetPosition(camPos);*/

    //カメラ
    XMVECTOR vCam = { 0, 7, -10, 0 };              //自撮り棒用意
    vCam = XMVector3TransformCoord(vCam, mRotX * mRotY);    //自撮り棒回転
    //vCam = XMVector3TransformCoord(vCam, mRotX);
    //XMFLOAT3 camPos;
    //XMStoreFloat3(&camPos, vPos + vCam);
    Camera::SetPosition(vPos+ vCam);            //カメラの位置は自撮り棒の先端
    Camera::SetTarget(transform_.position_);    //カメラの見る位置はこのオブジェクトの位置

}

    //Ground* pGround = (Ground*)FindObject("Ground");    //ステージオブジェクトを探す
    //int hGroundModel = pGround->GetModelHandle();    //モデル番号を取得

    //RayCastData data;
    //data.start = transform_.position_;   //レイの発射位置
    //data.start.y = 0;
    //data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
    //Model::RayCast(hGroundModel, &data); //レイを発射


    /*if (data.hit == true)
    {
    }*/
    //    transform_.position_.y = -data.dist;

//描画
void Controller::Draw()
{
   /* Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);*/
}

//開放
void Controller::Release()
{
}