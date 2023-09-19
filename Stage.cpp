#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Fbx.h"
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
    //tableにブロックのタイプをセット
    for (int z = 0; z < ZSIZE; z++) {
        for (int x = 0; x < XSIZE; x++) {
            SetBlock(x, z, (BLOCKTYPE)(0));
            SetBlockHeight(x, z, 0);
        }
    }
    controlId = IDC_RADIO_UP;
    
}

//更新
void Stage::Update()
{
    if (!Input::IsMouseButtonDown(0)) {
        return;
    }
    //ビューポート行列
    float w = (float)(Direct3D::scrWidth / 2.0f);
    float h = (float)(Direct3D::scrHeight / 2.0f);
    //Offsetx,yは0
    //minZ = 0 maxZ = 1
    XMMATRIX vp = 
    {
        w, 0,0,0,
        0,-h,0,0,
        0, 0,1,0,
        w, h,0,1,
    };
    //ビューポート
    XMMATRIX intVP = XMMatrixInverse(nullptr, vp);
    //プロジェクション変換
    XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
    //ビュー変換
    XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());
    XMFLOAT3 mousePosFront = Input::GetMousePosition();
    mousePosFront.z = 0.0f;
    XMFLOAT3 mousePosBack = Input::GetMousePosition();
    mousePosBack.z = 1.0f;
    //①　mousePosFrontをベクトルに変換
    XMVECTOR vMouseFront = XMLoadFloat3(&mousePosFront);
    //②　①にinvVP, invPrj, intViewをかける
    vMouseFront = XMVector3TransformCoord(vMouseFront,intVP * invProj * invView );
    //③　mousePosBackをベクトルに変換
    XMVECTOR vMouseBack = XMLoadFloat3(&mousePosBack);
    //④　③にinvVP, invPrj, invViewをかける
    vMouseBack = XMVector3TransformCoord(vMouseBack,intVP * invProj * invView );

    for (int x = 0; x < 15; x++) {
        for (int z = 0; z < 15; z++) {
            for (int y = 0; y < table_[x][z].height + 1; y++) {

                //⑤　②から④に向かってレイをうつ（とりあえずモデル番号はhModel_[0]）
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
                    //⑥レイが当たったらブレークポイントで止める
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
        SendMessage(GetDlgItem(hDlg,IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);             //ラジオボタンの初期化
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"デフォルト");    //コンボボックスの初期化
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"レンガ");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"草");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"砂");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"水");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_SETCURSEL, 0, 0);
        return 0;
    case WM_COMMAND:
        controlId = LOWORD(wParam); // コントロールのIDを取得
        notificationCode = HIWORD(wParam); // 通知コードを取得
        
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

