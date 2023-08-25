#include "ChildPlayer.h"
#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "Engine/Fbx.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

ChildPlayer::ChildPlayer(GameObject* parent)
	:GameObject(parent, "ChildPlayer"), pFbx(nullptr),hModel_(-1)
{
}

ChildPlayer::~ChildPlayer()
{
	Release();
}

void ChildPlayer::Initialize()
{
	hModel_ = Model::Load("Assets/Oden.fbx");
	assert(hModel_ >= 0);
	transform_.scale_.x = 0.5;
	transform_.scale_.y = 0.5;
	transform_.scale_.z = 0.5;
	transform_.rotate_.x = 90;
//	transform_.position_.x = -4.0f;
	SphereCollider* col = new SphereCollider(1.2f);
	AddCollider(col);
}

void ChildPlayer::Update()
{
	transform_.rotate_.z += 5;
	transform_.position_.z += 0.5f;
	if (transform_.position_.z > 50) KillMe();

	if (Input::IsKey(DIK_G)) {
		KillMe();
	}
}

void ChildPlayer::Draw()
{
	Model::SetTransform(hModel_,transform_);
	Model::Draw(hModel_);
}

void ChildPlayer::Release()
{
	/*pFbx->Release();
	delete pFbx;*/
}

//Õ“Ë”»’è
void ChildPlayer::OnCollision(GameObject* pTarget)
{
	//Enemy‚É‚Ô‚Â‚©‚Á‚½‚Æ‚«
	if (pTarget->GetObjectName() == "Enemy")
	{
		KillMe();
	}
}

