#pragma once
#include "Quad.h"

class Dice :public Quad
{
public:
	//メンバ関数

	/// <summary>
	/// 四角形を表すクラスのコンストラクタ
	/// </summary>
	Dice();
	~Dice();
	HRESULT Initialize()override;
	void Draw(XMMATRIX& worldMatrix)override;
	void Release()override;
};

