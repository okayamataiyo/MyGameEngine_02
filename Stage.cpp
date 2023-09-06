#include "Engine/Model.h"
#include "Stage.h"
#include "Resource.h"

//コンストラクタ
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

//デストラクタ
Stage::~Stage()
{
}

//初期化
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

    //モデルデータのロード
    for (int i = 0; i < MODEL_NUM; i++){
        hModel_[i] = Model::Load(fname_base + modelname[i]);
        assert(hModel_[i] >= 0);
    }

    /*for (int i = 0; i < MODEL_NUM; i++) {
        hModel_[i] = -1;
    }*/
    for (int z = 0; z < ZSIZE; z++) {
        for (int x = 0; x < XSIZE; x++) {
            //table_[x][z] = x%5;
            SetBlock(x, z, (BLOCKTYPE)(z%5));
            SetBlockHeight(x, z, x%4);
        }
    }

    //tableにブロックのタイプをセット
}

//更新
void Stage::Update()
{
    //ビューポート行列
    float w = (float)Direct3D::scrWidth / 2.0f;
    float h = (float)Direct3D::scrHeight / 2.0f;
    XMMATRIX vp = {
        w, 0,0,0,
        0,-h,0,0,
        0, 0,1,0,
        w, h,0,1,
    };
    //ビューポート
    XMMATRIX intVP =

        //プロジェクション変換
        XMMATRIX invProj =

        //ビュー変換
        XMMATRIX invView =
        XMFLOAT3 mousePosFront = GetMouse
        mousePosFront.z = 0.0;
    XMFLOAT3 mousePosBack = ごにょごにょ;
    mousePosBack.z = 1.0f;

}

//描画
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

//開放
void Stage::Release()
{
    /*for (int x = 0; x < width_; x++)
    {
        delete[] table_[x];
    }
    delete[]table_;*/
}

//Stageのダイアログプロシージャ
BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    //ダイアログが出来た時
    case WM_INITDIALOG:
        SendMessage(GetDlgItem(hDlg,IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);            //ラジオボタンの初期化
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"デフォルト");  //コンボボックスの初期化
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"レンガ");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"草");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"砂");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"水");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_SETCURSEL, 0, 0);
        return 0;
    case WM_COMMAND:

        return 0;
    }
    return DefWindowProc(hDlg, msg, wParam, lParam);
}

void Stage::SetBlock(int _x, int _z, BLOCKTYPE _type)
{
    //エラーチェック 範囲内の値かどうか
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

