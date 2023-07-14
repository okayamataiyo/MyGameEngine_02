#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"
#include "Player.h"

class Fbx;

//プレイヤーの子供を管理するクラス
class ChildPlayer : public GameObject
{
	Fbx* pFbx;
	int hModel_;	//モデル番号
public:
	//コンストラクタ
	//引数:parent 親オブジェクト(SceneManager)
	ChildPlayer(GameObject*parent);

	~ChildPlayer();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

};

