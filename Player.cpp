#include "Player.h"
#include "Engine/GameObject.h"

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
	this->transform_.rotate_.y += 10;
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
