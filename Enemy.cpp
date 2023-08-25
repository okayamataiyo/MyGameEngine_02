#include "Enemy.h"
#include "Engine/SphereCollider.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy")
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	pFbx = new Fbx;
	pFbx->Load("Assets/oden.fbx");
	transform_.position_.z = 20.0f;

	SphereCollider* col = new SphereCollider(1.2f);
	AddCollider(col);
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
	pFbx->Draw(transform_);
}

void Enemy::Release()
{
}

void Enemy::OnCollision(GameObject* pTarget)
{
	//ChildPlayer‚É‚Ô‚Â‚©‚Á‚½‚Æ‚«
	KillMe();
	pTarget->KillMe();
	
}


