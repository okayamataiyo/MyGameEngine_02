#pragma once
#include "Engine/GameObject.h"

//�O���錾
class Fbx;

//�v���C�V�[�����Ǘ�����N���X
class PlayScene
	: public GameObject
{
	Fbx* pFbx;
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