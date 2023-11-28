#include "GameObject.h"
#include "SphereCollider.h"
#include "Direct3D.h"

GameObject::GameObject()
	:pParent_(nullptr)
{
}

GameObject::GameObject(GameObject* _parent, const std::string& _name)
	: pParent_(_parent),Is_DeadFlag(false),objectName_(_name),pCollider_(nullptr)
{
	if (pParent_ != nullptr) {
		this->transform_.pParent_ = &(_parent->transform_);
	}
	 
}

//template <class T>

void Instantiate(GameObject* _parent)
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

void GameObject::SetPosition(XMFLOAT3 _position)
{
	transform_.position_ = _position;
}

void GameObject::SetPosition(float _x, float _y, float _z)
{
	SetPosition(XMFLOAT3(_x, _y, _z));
}

GameObject* GameObject::FindChildObject(string _objName)
{
	if (_objName == this->objectName_) {

		return(this);	//������_objName�̃I�u�W�F�N�g�������I
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
/// �ċA�Ăяo����RootJob��T���Ă��̃A�h���X��Ԃ��֐�
/// </summary>
/// <returns>RootJob�̃A�h���X(GameObject * �^)</returns>
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

void GameObject::DrawSub()
{
	Draw();

	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	(*itr)->DrawSub();
}

void GameObject::UpdateSub()
{
	Update();

	RoundRobin(GetRootJob());
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {

		(*itr)->UpdateSub();
	}

	for (auto itr = childList_.begin(); itr != childList_.end();) {

		if ((*itr)->IsDead() == true) {

			(*itr)->ReleaseSub();
			SAFE_DELETE(*itr);				//�������g������
			itr = childList_.erase(itr);	//���X�g������폜
		}
		else {
			itr++;
		}
	}
}

void GameObject::ReleaseSub()
{

	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {

		(*itr)->ReleaseSub();	//*itr�̃����[�X���Ă�
		SAFE_DELETE(*itr);		//*itr���̂�����
	}

	Release();
}

void GameObject::AddCollider(SphereCollider* _pCollider)
{

	pCollider_ = _pCollider;
}

void GameObject::Collision(GameObject* _pTarget)
{

	if (_pTarget == this || _pTarget->pCollider_ == nullptr) 
		return;		//�^�[�Q�b�g�ɃR���C�_�[���A�^�b�`����Ă��Ȃ�

		//XMVECTOR v{ transform_.position_.x - pTarget->transform_.position_.x,
		//			transform_.position_.y - pTarget->transform_.position_.y,
		//			transform_.position_.z - pTarget->transform_.position_.z,
		//			0 };
		//XMVECTOR dist = XMVector3Dot(v, v);
		float dist = (transform_.position_.x - _pTarget->transform_.position_.x) * (transform_.position_.x - _pTarget->transform_.position_.x)
			+ (transform_.position_.y - _pTarget->transform_.position_.y) * (transform_.position_.y - _pTarget->transform_.position_.y)
			+ (transform_.position_.z - _pTarget->transform_.position_.z) * (transform_.position_.z - _pTarget->transform_.position_.z);

		float rDist = (this->pCollider_->GetRadius() + _pTarget->pCollider_->GetRadius()) * (this->pCollider_->GetRadius() + _pTarget->pCollider_->GetRadius());

		//�����ƃ^�[�Q�b�g�̋���	<= R1+R2�Ȃ�
		//�����A�����̃R���C�_�[�ƃ^�[�Q�b�g���Ԃ����Ă�����
		//onCollision(pTarget)���Ăяo��
		if (dist <= rDist) {

			OnCollision(_pTarget);
		}
}

void GameObject::RoundRobin(GameObject* _pTarget)
{

	if (pCollider_ == nullptr)
		return;
	if (_pTarget->pCollider_ != nullptr)	//�����ƃ^�[�Q�b�g
		Collision(_pTarget);
	//�����̎q���S���ƃ^�[�Q�b�g
	for (auto itr:_pTarget->childList_)
		RoundRobin(itr);
}

//�I�u�W�F�N�g�̖��O���擾
const std::string& GameObject::GetObjectName(void)const
{

	return objectName_;
}

