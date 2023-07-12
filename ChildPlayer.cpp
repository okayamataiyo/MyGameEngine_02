#include "ChildPlayer.h"
#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "Engine/Fbx.h"

ChildPlayer::ChildPlayer(GameObject* parent)
	:GameObject(parent, "ChildPlayer"), pFbx(nullptr)
{
}

ChildPlayer::~ChildPlayer()
{
	Release();
}

void ChildPlayer::Initialize()
{
	pFbx = new Fbx;
	pFbx->Load("Assets/Oden.fbx");
	transform_.scale_.x = 0.5;
	transform_.scale_.y = 0.5;
	transform_.scale_.z = 0.5;
	transform_.position_.x = -4.0f;
}

void ChildPlayer::Update()
{
	transform_.rotate_.y++;

	if (Input::IsKey(DIK_G)) {
		KillMe();
	}
}

void ChildPlayer::Draw()
{
	pFbx->Draw(transform_);
}

void ChildPlayer::Release()
{
	/*pFbx->Release();
	delete pFbx;*/
}

