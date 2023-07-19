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

GameObject* GameObject::FindChildObject(string _objName)
{
	if (_objName == this->objectName_) {

		return(this);	//自分が_objNameのオブジェクトだった！
	}
	else {

//		for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {
		for(auto itr: childList_){

			GameObject* obj = itr->FindChildObject(_objName);
			if (obj != nullptr)
				return obj;
		}
	}
	return nullptr;
}

/// <summary>
/// 再帰呼び出しでRootJobを探してそのアドレスを返す関数
/// </summary>
/// <returns>RootJobのアドレス(GameObject * 型)</returns>
GameObject* GameObject::GetRootJob()
{

	if(pParent_ == nullptr)	return this;
	
	return pParent_->GetRootJob();
}

GameObject* GameObject::FindObject(string _objName) 
{

	GameObject* rootJob = GetRootJob();
	GameObject* result = rootJob->FindChildObject(_objName);
	return (result);
//	return GetRootJob()->FindObject(_objName);
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