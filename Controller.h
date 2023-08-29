#pragma once
#include "Engine/GameObject.h"

//�^���N���Ǘ�����N���X
class Controller : public GameObject
{
    int hModel_;    //���f���ԍ�
    int camType_;
    XMFLOAT3 move_;
public:
    //�R���X�g���N�^
    Controller(GameObject* parent);

    //�f�X�g���N�^
    ~Controller();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};