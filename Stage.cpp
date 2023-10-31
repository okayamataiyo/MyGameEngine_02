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

//コンストラクタ
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
    controlId_ = IDC_RADIO_UP;

}

//更新
void Stage::Update()
{
    if (Input::IsMouseButtonDown(0)) {
        BlockWrite();
    }

}

void Stage::BlockWrite()
{
    float w = (float)(Direct3D::scrWidth / 2.0f);   //ビューポート行列
    float h = (float)(Direct3D::scrHeight / 2.0f);
    //Offsetx,yは0
    //minZ = 0 maxZ = 1
    XMMATRIX vp = {
        w, 0,0,0,
        0,-h,0,0,
        0, 0,1,0,
        w, h,0,1,
    };
    XMMATRIX intVP = XMMatrixInverse(nullptr, vp);                              //ビューポート
    XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix()); //プロジェクション変換    
    XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());       //ビュー変換
    //レイを-5°移動させて、調節した
    //constexpr float angleIncrement = XMConvertToRadians(-5.0f); // 角度をラジアンに変換
    //XMMATRIX rotationMatrix = XMMatrixRotationX(angleIncrement); // X軸周りに回転
    //invView = XMMatrixMultiply(rotationMatrix, invView); // ビュー行列に回転行列を適用

    XMFLOAT3 mousePosFront = Input::GetMousePosition();
    mousePosFront.z = 0.0f;
    XMFLOAT3 mousePosBack = Input::GetMousePosition();
    mousePosBack.z = 1.0f;
    XMVECTOR vMouseFront = XMLoadFloat3(&mousePosFront);                            //①　mousePosFrontをベクトルに変換    
    vMouseFront = XMVector3TransformCoord(vMouseFront, intVP * invProj * invView);  //②　①にinvVP, invPrj, intViewをかける    
    XMVECTOR vMouseBack = XMLoadFloat3(&mousePosBack);                              //③　mousePosBackをベクトルに変換    
    vMouseBack = XMVector3TransformCoord(vMouseBack, intVP * invProj * invView);    //④　③にinvVP, invPrj, invViewをかける

    rayHit_ = false;

    for (int x = 0; x < 15; x++) {
        for (int z = 0; z < 15; z++) {
            for (int y = 0; y < table_[x][z].height + 1; y++) {

                //⑤　②から④に向かってレイをうつ（とりあえずモデル番号はhModel_[0]）
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
                    //⑥レイが当たったらブレークポイントで止める
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

//描画
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

//開放
void Stage::Release()
{
    /*for (int x = 0; x < width_; x++){
        delete[] table_[x];
    }
    delete[]table_;*/
}

//Stageのダイアログプロシージャ
BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg){
    //ダイアログが出来た時
    case WM_INITDIALOG:
        SendMessage(GetDlgItem(hDlg,IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);             //ラジオボタンの初期化
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"デフォルト");    //コンボボックスの初期化
        SendMessage(GetDlgItem(hDlg, ID_MENU_SAVE), BM_SETCHECK, BST_CHECKED, 0);             //ラジオボタンの初期化
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"レンガ");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"草");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"砂");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"水");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_SETCURSEL, 0, 0);
        return TRUE;
    case WM_COMMAND:
        controlId_ = LOWORD(wParam); // コントロールのIDを取得
        notificationCode_ = HIWORD(wParam); // 通知コードを取得
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
    //エラーチェック 範囲内の値かどうか
    table_[_x][_z].type = _type;
}

void Stage::SetBlockHeight(int _x, int _z, int _y)
{
    table_[_x][_z].height = _y;
}

void Stage::Save()
{
    char fileName[MAX_PATH] = "無題.map";
    std::string buffer;
    std::stringstream oss;

    //OPENFILENAME構造体を初期化
    OPENFILENAME ofn; {
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.lpstrFilter = TEXT("マップデータ(*.map)\0*.map\0");
        ofn.lpstrFile = fileName;
        ofn.nMaxFile = MAX_PATH;
        ofn.Flags = OFN_OVERWRITEPROMPT;
        ofn.lpstrDefExt = TEXT("map");
    }

    //ファイルに保存
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

//ロード
void Stage::Load() 
{
    char fileName[MAX_PATH] = "無題.map";
    std::string buffer;
    std::stringstream oss;

    //OPENFILENAME構造体を初期化
    OPENFILENAME ofn; {
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.lpstrFilter = TEXT("マップデータ(*.map)\0*.map\0");
        ofn.lpstrFile = fileName;
        ofn.nMaxFile = MAX_PATH;
        ofn.Flags = OFN_FILEMUSTEXIST;
        ofn.lpstrDefExt = TEXT("map");
    }

    //ファイルを開く
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

    //自作したSave関数の中身
    //char fileName[MAX_PATH] = "マップデータ.map";  //ファイル名を入れる変数

    ////「ファイルを保存」ダイアログの設定
    //OPENFILENAME ofn;                         	//名前をつけて保存ダイアログの設定用構造体
    //ZeroMemory(&ofn, sizeof(ofn));            	//構造体初期化
    //ofn.lStructSize = sizeof(OPENFILENAME);   	//構造体のサイズ
    //ofn.lpstrFilter = TEXT("マップデータ(*.map)\0*.map\0")  //─┬ファイルの種類
    //    TEXT("すべてのファイル(*.*)\0*.*\0\0");             //─┘
    //ofn.lpstrFile = fileName;               	//ファイル名
    //ofn.nMaxFile = MAX_PATH;                  	//パスの最大文字数
    //ofn.Flags = OFN_OVERWRITEPROMPT;   		    //フラグ（同名ファイルが存在したら上書き確認）
    //ofn.lpstrDefExt = "map";                  	//デフォルト拡張子

    ////「ファイルを保存」ダイアログ
    //BOOL selFile;
    //selFile = GetSaveFileName(&ofn);

    ////キャンセルしたら中断
    //if (selFile == FALSE) return;

    //HANDLE hFile;
    //hFile = CreateFile(
    //    fileName, //ファイル名
    //    GENERIC_WRITE,  //アクセスモード
    //    0,
    //    NULL,
    //    CREATE_ALWAYS,  //作成方法
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
    //    hFile,      //ファイルハンドル
    //    charData,   //保存したい文字列
    //    static_cast<DWORD>(data.length()),         //保存する文字数
    //    &bytes,     //保存したサイズ
    //    NULL
    //);

    //CloseHandle(hFile);
