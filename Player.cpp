#include "Player.h"
#include "ChildPlayer.h"
#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), pFbx(nullptr), hModel_(-1)
{
}

Player::~Player()
{
	Release();
}

void Player::Initialize()
{
	hModel_ = Model::Load("Assets/oden.fbx");
	assert(hModel_ >= 0);
	/*GameObject* pCP1 = Instantiate<ChildPlayer>(this);
	pCP1->SetPosition(2, 0, 0);
	GameObject* pCP2 = Instantiate<ChildPlayer>(this);
	pCP2->SetPosition(-2,0,0);
	*/
}

void Player::Update()
{
	transform_.rotate_.y++;

//	MirrorRotate(2, 0, 0);	//âÒì]ÇÃîΩì]Ç≥ÇπÇΩÇ©Ç¡ÇΩÇØÇ«Ç‹ÇæèoóàÇƒÇ¢Ç»Ç¢ÅB

	float Verocity = 0;


	if (Input::IsKey(DIK_A)) {
		Verocity--;
	}
	else if (Input::IsKey(DIK_D)) {
		Verocity++;
	}

	if (Input::IsKey(DIK_LSHIFT)) {
		Verocity *= 0.5;
	}

	if (Input::IsKey(DIK_F)) {
		KillMe();
	}

	if (Input::IsKeyDown(DIK_SPACE)) {
		GameObject * pBullet = Instantiate<ChildPlayer>(pParent_);
		pBullet->SetPosition(transform_.position_);
	}
	
	transform_.position_.x += Verocity;
}

void Player::Draw()
{
//	pFbx->Draw(transform_);
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player::Release()
{

	/*pFbx->Release();
	delete pFbx;*/
}
