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
    //モデルデータのロード
    hModel_ = Model::Load("Assets/BoxWater.fbx");
    assert(hModel_ >= 0);

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

    //戦車の現在地をベクトル型に変換
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    //1フレームの移動ベクトル
    XMVECTOR vMove1{ 0.0f, 0.0f, 0.1f, 0.0f }; //奥に0.1m

    //1フレームの移動ベクトル
    XMVECTOR vMove2{ 0.1f, 0.0f, 0.0f, 0.0f };//横に0.1m

    XMVECTOR vMove3{ 0.0f, 0.1f, 0.0f, 0.0f };//縦に0.1m

    //transform_.rotate_.y度回転させる行列を作成
    XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    //移動ベクトルを変換させる
    vMove1 = XMVector3TransformCoord(vMove1, mRotY);

    //移動ベクトルを変換させる
    vMove2 = XMVector3TransformCoord(vMove2, mRotY);

    vMove3 = XMVector3TransformCoord(vMove3, mRotY);

    //Wキーが押されたら移動
    if (Input::IsKey(DIK_W))
    {
        //移動
        vPos += vMove1;

        //現在地をベクトルからいつものtransform_.position_に戻す
        XMStoreFloat3(&transform_.position_, vPos);
    }

    //Sキーが押されたら移動
    if (Input::IsKey(DIK_S))
    {
        //移動
        vPos -= vMove1;

        //現在地をベクトルからいつものtransform_.position_に戻す
        XMStoreFloat3(&transform_.position_, vPos);
    }

    if (Input::IsKey(DIK_D))
    {
        //何らかの処理
        //transform_.rotate_.y += -1.0f;     // 1dd°ずつ回転
        //移動
        vPos += vMove2;

        //現在地をベクトルからいつものtransform_.position_に戻す
        XMStoreFloat3(&transform_.position_, vPos);
    }

    if (Input::IsKey(DIK_A))
    {
        //何らかの処理
        //transform_.rotate_.y += 1.0f;     // 1dd°ずつ回転
        //移動
        vPos -= vMove2;

        //現在地をベクトルからいつものtransform_.position_に戻す
        XMStoreFloat3(&transform_.position_, vPos);
    }

    if (Input::IsKey(DIK_UP))
    {
        vPos += vMove3;

        XMStoreFloat3(&transform_.position_, vPos);
    }

    if (Input::IsKey(DIK_DOWN))
    {
        vPos += vMove1;

        XMStoreFloat3(&transform_.position_, vPos);
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

    Camera::SetTarget(transform_.position_);
    XMVECTOR vCam = { 0, 5, -10, 0 };
    vCam = XMVector3TransformCoord(vCam, mRotY);
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, vPos + vCam);
    Camera::SetPosition(camPos);

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
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Controller::Release()
{
}