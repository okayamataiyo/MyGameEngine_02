#include "PlayScene.h"
#include "Engine/Fbx.h"
#include "Player.h"
#include "ChildPlayer.h"
#include "Enemy.h"

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"),pFbx(nullptr)
{
}

//初期化
void PlayScene::Initialize()
{
	//Player* pPlayer;
	//pPlayer = new Player(this);		//プレイヤーの親は、自分(PlayScene)
	//pPlayer->Initialize();
	//childList_.push_back(pPlayer);	//PlaySceneの子として、プレイヤーを登録
	/*this->transform_.scale_.x = 0.5;
	this->transform_.scale_.y = 0.5;
	this->transform_.scale_.z = 0.5;*/
	GameObject* pPlayer = Instantiate<Player>(this);
	GameObject* pEnemy = Instantiate<Enemy>(this);
//	pPlayer->transform_.scale_.x;
}

//更新
void PlayScene::Update()
{
	
}

//描画
void PlayScene::Draw()
{

}

//開放
void PlayScene::Release()
{
	/*pFbx->Release();
	delete pFbx;*/
}