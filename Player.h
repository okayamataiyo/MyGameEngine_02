#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"

class Fbx;

//�v���C�V�[�����Ǘ�����N���X
class Player : public GameObject
{
	Fbx* pFbx;
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