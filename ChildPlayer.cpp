#include "ChildPlayer.h"
#include "Engine/GameObject.h"
#include "Engine/Input.h"

ChildPlayer::ChildPlayer(GameObject* parent)
	:GameObject(parent, "ChildPlayer")
{
}

ChildPlayer::~ChildPlayer()
{
	Release();
}

void ChildPlayer::Initialize()
{
	pFbx = new Fbx;
	pFbx->Load("Assets/Cube.fbx");

	transform_.position_.x = -4.0f;
}

void ChildPlayer::Update()
{
	transform_.rotate_.y++;
}

void ChildPlayer::Draw()
{
	pFbx->Draw(transform_);
}

void ChildPlayer::Release()
{
	pFbx->Release();
	delete pFbx;
}

