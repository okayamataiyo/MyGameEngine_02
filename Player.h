#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"

class Fbx;

//プレイヤーを管理するクラス
class Player : public GameObject
{
	Fbx* pFbx;
	int hModel_;	//モデル番号
public:
	//コンストラクタ
	//引数:parent 親オブジェクト(SceneManager)
	Player(GameObject* parent);

	~Player();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//何かに当たった
	//引数:pTarget当たった相手
	void OnCollision(GameObject* pTarget) override;
};