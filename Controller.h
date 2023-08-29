#pragma once
#include "Engine/GameObject.h"

//タンクを管理するクラス
class Controller : public GameObject
{
    int hModel_;    //モデル番号
    int camType_;
    XMFLOAT3 move_;
public:
    //コンストラクタ
    Controller(GameObject* parent);

    //デストラクタ
    ~Controller();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};