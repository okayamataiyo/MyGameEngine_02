#include "Player.h"
#include "Engine/GameObject.h"
#include "Engine/Input.h"

Player::Player(GameObject* parent)
	:GameObject(parent,"Player"),pFbx(nullptr)
{
}

Player::~Player()
{

}

void Player::Initialize()
{
	pFbx = new Fbx;
	pFbx->Load("Assets/oden.fbx");
}

void Player::Update()
{
	this->transform_.rotate_.y++;

	if (Input::IsKey(DIK_A)) {
		this->transform_.position_.x++;
	}
	else if (Input::IsKey(DIK_D)) {
		this->transform_.position_.x--;
	}
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
