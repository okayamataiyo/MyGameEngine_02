#pragma once
#include "Engine/GameObject.h"

//�v���C�V�[�����Ǘ�����N���X
class PlayScene : public GameObject
{
public:
	//�R���X�g���N�^
	//����:parent �e�I�u�W�F�N�g(SceneManager)
	PlayScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};