#pragma once

#include <list>
#include <string>
#include "Transform.h"
#include "Direct3D.h"

using std::string;
using std::list;

class SphereCollider;

class GameObject
{
	bool Is_DeadFlag;	//�����t���O
	
protected:
	list<GameObject*>	childList_;
	Transform			transform_;
	GameObject*			pParent_;
	string				objectName_;	//�I�u�W�F�N�g�̖��O�̔z��
	SphereCollider*		pCollider_;

public:
	GameObject();
	GameObject(GameObject* _parent, const std::string& _name);
	~GameObject();

	virtual void Initialize() =0;
	virtual void Update() =0;
	virtual void Draw() =0;
	virtual void Release() =0;
	bool IsDead();
	void KillMe();
	void DrawSub();
	void UpdateSub();
	void ReleaseSub();
	void SetPosition(XMFLOAT3 _position);
	void SetPosition(float _x, float _y, float _z);
	GameObject* FindChildObject(string _objName);
	GameObject* GetRootJob();
	GameObject* FindObject(string _objName);
	void AddCollider(SphereCollider* _pCollider);
	void Collision(GameObject* _pTarget);
	void RoundRobin(GameObject* _pTarget);

	//�����ƏՓ˂����ꍇ�ɌĂ΂��(�I�[�o�[���C�h�p)
	//����:pTarget�Փ˂��Ă邩���ׂ鑊��
	virtual void OnCollision(GameObject* _pTarget) {};

public:	//�e���v���[�g�̒�`
	template <class T>
	GameObject* Instantiate(GameObject* _parent)
	{
		T* pObject;
		pObject = new T(_parent);
		pObject->Initialize();
		childList_.push_back(pObject);
		return pObject;
	}

	//�ǉ��ŏ������ނ��
	//�I�u�W�F�N�g�̖��O���擾
	//�ߒl:���O
	const std::string& GetObjectName(void) const;
};

