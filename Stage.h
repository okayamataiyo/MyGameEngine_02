#pragma once
#include "Engine/GameObject.h"
#include <Windows.h>

namespace 
{
    const int MODEL_NUM{ 5 };
    const int XSIZE{ 15 };
    const int ZSIZE{ 15 };
    enum BLOCKTYPE{
        DEFAULT, BRICK, GRASS, SAND, WATER
    };
}

//Stageを管理するクラス
class Stage : public GameObject
{
private:
    struct Block {
        int type;
        int height;
    }table_[XSIZE][ZSIZE];


    int mode_;              //0:上げる 1:下げる 2:種類を変える
    int select_;            //種類
    int hModel_[MODEL_NUM]; //モデル番号
    int controlId_;         //コントロールのIDを取得
    int comboId_;           //コンボのIDを取得
    int notificationCode_;  //通知コードを取得
    int setComboId_;        //コンボIDをセット
    bool rayHit_;   //レイがヒットしたかどうかを示すフラグ
    //int table_[XSIZE][ZSIZE];
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

    BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);

    void SetBlock(int _x, int _z, BLOCKTYPE _type);

    void SetBlockHeight(int _x, int _z, int _y);

    string BlockData(const Block& block);

    Block GetBlock(int _x, int _z) { return table_[_x][_z]; }

    void Save();



    //指定した位置が通れるか通れないかを調べる
    //引数:x,z  調べる位置
    //戻り値:通れない=true/通れない=false
    //bool IsWall(int x, int z);
};