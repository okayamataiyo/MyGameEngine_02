#include "Player.h"
#include "ChildPlayer.h"
#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/SceneManager.h"

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

	float VerPosX = 0;	//Xé≤à⁄ìÆó 
	float VerRotY = 0;	//Yé≤à⁄ìÆó 



	if (Input::IsKey(DIK_W)) {

		VerRotY++;
	}
	else if (Input::IsKey(DIK_S)) {

		VerRotY--;
	}
	if (Input::IsKey(DIK_A)) {
		
		VerPosX--;
	}
	else if (Input::IsKey(DIK_D)) {
		
		VerPosX++;
	}

	if (Input::IsKey(DIK_LSHIFT)) {
		
		VerPosX *= 0.5;
	}

	VerPosX = VerPosX * 0.5;
	VerRotY = VerRotY * 0.5;

	transform_.rotate_.x += VerRotY;
	transform_.position_.x += VerPosX;

	if (Input::IsKey(DIK_F)) {
		
		KillMe();
	}

	if (Input::IsKeyDown(DIK_SPACE)) {
		
		GameObject * pBullet = Instantiate<ChildPlayer>(pParent_);
		pBullet->SetPosition(transform_.position_);
	}

	
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
