#pragma once
#include "Quad.h"

class Dice :public Quad
{
public:
	//�����o�֐�

	/// <summary>
	/// �l�p�`��\���N���X�̃R���X�g���N�^
	/// </summary>
	Dice();
	~Dice();
	HRESULT Initialize()override;
	void Draw(XMMATRIX& worldMatrix)override;
	void Release()override;
};

