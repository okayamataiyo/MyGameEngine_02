#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"
#include "Player.h"

class Fbx;

//�v���C���[�̎q�����Ǘ�����N���X
class ChildPlayer : public GameObject
{
	Fbx* pFbx;
	int hModel_;	//���f���ԍ�
public:
	//�R���X�g���N�^
	//����:parent �e�I�u�W�F�N�g(SceneManager)
	ChildPlayer(GameObject*parent);

	~ChildPlayer();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

};

