#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"

class Fbx;

//�v���C���[���Ǘ�����N���X
class Player : public GameObject
{
	Fbx* pFbx;
	int hModel_;	//���f���ԍ�
public:
	//�R���X�g���N�^
	//����:parent �e�I�u�W�F�N�g(SceneManager)
	Player(GameObject* parent);

	~Player();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};