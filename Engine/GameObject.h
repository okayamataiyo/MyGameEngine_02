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
	bool Is_DeadFlag;	//消去フラグ
	
protected:
	list<GameObject*>	childList_;
	Transform			transform_;
	GameObject*			pParent_;
	string				objectName_;	//オブジェクトの名前の配列
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

	//何かと衝突した場合に呼ばれる(オーバーライド用)
	//引数:pTarget衝突してるか調べる相手
	virtual void OnCollision(GameObject* _pTarget) {};

public:	//テンプレートの定義
	template <class T>
	GameObject* Instantiate(GameObject* _parent)
	{
		T* pObject;
		pObject = new T(_parent);
		pObject->Initialize();
		childList_.push_back(pObject);
		return pObject;
	}

	//追加で書き込むやつ
	//オブジェクトの名前を取得
	//戻値:名前
	const std::string& GetObjectName(void) const;
};

