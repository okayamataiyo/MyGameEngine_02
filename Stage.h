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

//Stageを管理するクラス
class Stage : public GameObject
{
private:

    //int mode_;          //0:上げる 1:下げる 2:種類を変える
    //int select_;        //種類
    int hModel_[MODEL_NUM]; //モデル番号
    int controlId_;     //コントロールのIDを取得
    int comboId_;       //コンボのIDを取得
    int notificationCode_;  //通知コードを取得
    int setComboId_;    //コンボIDをセット
    bool rayHit_;       //レイがヒットしたかどうかを示すフラグ
    int pushType_;
    int timer_;         //タイマー 
    int timerThresHold_;//タイマーの閾値
    bool pushFlag_;     //ボタンが押されたかどうかを示すフラグ
    //int table_[XSIZE][ZSIZE];
    //int width_, height_;

public:
    //コンストラクタ
    //引数:parent 親オブジェクト(SceneManager)
    Stage(GameObject* parent);

    ~Stage();    //デストラクタ

    void Initialize() override;    //初期化

    void Update() override;    //更新

    void BlockWrite();

    void Draw() override;    //描画

    void Release() override;    //開放

    BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);

    void SetBlock(int _x, int _z, BLOCKTYPE _type);

    void SetBlockHeight(int _x, int _z, int _y);

    void Save();    //セーブ

    void Load();    //ロード

    //指定した位置が通れるか通れないかを調べる
    //引数:x,z  調べる位置
    //戻り値:通れない=true/通れない=false
    //bool IsWall(int x, int z);
};