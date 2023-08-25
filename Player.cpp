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

//	MirrorRotate(2, 0, 0);	//âÒì]ÇÃîΩì]Ç≥ÇπÇΩÇ©Ç¡ÇΩÇØÇ«Ç‹ÇæèoóàÇƒÇ¢Ç»Ç¢ÅB

	float VerPosX = 0;	//Xé≤à⁄ìÆó 
	float VerRotX = 0;	//Xé≤âÒì]ó 
	float VerRotY = 1;	//Yé≤âÒì]ó 

	if (Input::IsKey(DIK_W)) {

		VerRotX += 2;
		VerRotY = VerRotY * 5;
	}
	else if (Input::IsKey(DIK_S)) {

		VerRotX -= 2;
		VerRotY = VerRotY * 5;
	}
	if (Input::IsKey(DIK_D)) {

		VerPosX++;
	}
	else if (Input::IsKey(DIK_A)) {

		VerPosX--;
	}

	if (Input::IsKey(DIK_LSHIFT)) {
		
		VerPosX *= 0.5;
	}

	VerPosX = VerPosX * 0.5;
	VerRotX = VerRotX;

	transform_.rotate_.y += VerRotY;
	transform_.rotate_.x += VerRotX;
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

void Player::OnCollision(GameObject* pTarget)
{

}
