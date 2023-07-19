#pragma once

#include <list>
#include <string>
#include "Transform.h"
#include "Direct3D.h"

using std::string;
using std::list;

class GameObject
{
	bool Is_DeadFlag;	//消去フラグ

	
protected:
	list<GameObject*>	childList_;
	Transform			transform_;
	GameObject*			pParent_;
	string				objectName_;	//オブジェクトの名前の配列

public:
	GameObject();
	GameObject(GameObject* parent, const std::string& name);
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
	void SetPosition(XMFLOAT3 position);
	void SetPosition(float x, float y, float z);
	GameObject* FindChildObject(string _objName);
	GameObject* GetRootJob();
	GameObject* FindObject(string _objName);
	/*ここ個人制作*/
	void MirrorPosition(float x, float y, float z);
	void SetRotate(XMFLOAT3 rotate);
	void MirrorRotate(float x, float y, float z);
	/*ここまで*/
public:	//テンプレートの定義
	template <class T>
	GameObject* Instantiate(GameObject* parent)
	{
		T* pObject;
		pObject = new T(parent);
		pObject->Initialize();
		childList_.push_back(pObject);
		return pObject;
	}
};

