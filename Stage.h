#pragma once
#include "Engine/GameObject.h"

enum BLOCKTYPES
{
    TYPE_FLOOR,
    TYPE_WALL,
    TYPE_MAX,
};

const int MODEL_NUM{ 5 };
const int XSIZE{ 15 };
const int ZSIZE{ 15 };


//Stageを管理するクラス
class Stage : public GameObject
{
    int hModel_[MODEL_NUM];    //モデル番号
    int table_[XSIZE][ZSIZE];
    //int width_, height_;

public:
    //コンストラクタ
    //引数:parent 親オブジェクト(SceneManager)
    Stage(GameObject* parent);

    //デストラクタ
    ~Stage();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //指定した位置が通れるか通れないかを調べる
    //引数:x,z  調べる位置
    //戻り値:通れない=true/通れない=false
    //bool IsWall(int x, int z);
};