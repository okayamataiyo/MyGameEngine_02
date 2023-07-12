#include "GameObject.h"
#include "Direct3D.h"

GameObject::GameObject()
	:pParent_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
	: pParent_(parent),Is_DeadFlag(false),objectName_(name)
{
	if (pParent_ != nullptr) {
		this->transform_.pParent_ = &(parent->transform_);
	}
	 
}

//template <class T>

void Instantiate(GameObject* parent)
{
	/*T* pPlayScene;
	pPlayScene = new T(parent);
	pPlayScene->Initialize();
	childList_.push_back(pPlayScene);*/
}

GameObject::~GameObject()
{
}

bool GameObject::IsDead()
{
	return(Is_DeadFlag != false );
}

void GameObject::KillMe()
{
	Is_DeadFlag = true;
}

void GameObject::SetPosition(XMFLOAT3 position)
{
	transform_.position_ = position;
}

void GameObject::SetPosition(float x, float y, float z)
{
	SetPosition(XMFLOAT3(x, y, z));
}

void GameObject::MirrorPosition(float x, float y, float z)
{
	SetPosition(XMFLOAT3(-x, -y, -z));
}

void GameObject::SetRotate(XMFLOAT3 rotate)
{
	transform_.rotate_ = rotate;
}

void GameObject::MirrorRotate(float x, float y, float z)
{
	SetRotate(XMFLOAT3(-transform_.rotate_.x* x, -transform_.rotate_.y * y, -transform_.rotate_.z * z));
}

void GameObject::DrawSub()
{
	Draw();

	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	(*itr)->DrawSub();
}

void GameObject::UpdateSub()
{
	Update();

	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {

		(*itr)->UpdateSub();
	}

	for (auto itr = childList_.begin(); itr != childList_.end();) {

		if ((*itr)->IsDead() == true) {

			(*itr)->ReleaseSub();
			SAFE_DELETE(*itr);				//自分自身を消す
			itr = childList_.erase(itr);	//リストからも削除
		}
		else {
			itr++;
		}
	}
}

void GameObject::ReleaseSub()
{

	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {

		(*itr)->ReleaseSub();	//*itrのリリースを呼ぶ
		SAFE_DELETE(*itr);		//*itr自体を消す
	}

	Release();
}