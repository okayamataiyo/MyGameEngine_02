#include "Player.h"
#include "ChildPlayer.h"
#include "Engine/GameObject.h"
#include "Engine/Input.h"

Player::Player(GameObject* parent)
	:GameObject(parent,"Player"),pFbx(nullptr)
{
}

Player::~Player()
{
	Release();
}

void Player::Initialize()
{
	pFbx = new Fbx;
	pFbx->Load("Assets/oden.fbx");

	Instantiate<ChildPlayer>(this);
}

void Player::Update()
{
	this->transform_.rotate_.y++;

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
	
	this->transform_.position_.x += Verocity;
}

void Player::Draw()
{
	pFbx->Draw(transform_);
}

void Player::Release()
{

	pFbx->Release();
	delete pFbx;
}
