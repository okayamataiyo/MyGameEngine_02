#include "PlayScene.h"
#include "Engine/Fbx.h"
#include "Player.h"
#include "ChildPlayer.h"
#include "Enemy.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"),pFbx(nullptr)
{
}

//������
void PlayScene::Initialize()
{
	//Player* pPlayer;
	//pPlayer = new Player(this);		//�v���C���[�̐e�́A����(PlayScene)
	//pPlayer->Initialize();
	//childList_.push_back(pPlayer);	//PlayScene�̎q�Ƃ��āA�v���C���[��o�^
	/*this->transform_.scale_.x = 0.5;
	this->transform_.scale_.y = 0.5;
	this->transform_.scale_.z = 0.5;*/
	GameObject* pPlayer = Instantiate<Player>(this);
	GameObject* pEnemy = Instantiate<Enemy>(this);
//	pPlayer->transform_.scale_.x;
}

//�X�V
void PlayScene::Update()
{
	
}

//�`��
void PlayScene::Draw()
{

}

//�J��
void PlayScene::Release()
{
	/*pFbx->Release();
	delete pFbx;*/
}