#pragma once
#include "../Engine/GameObject.h"

//���������Ǘ�����N���X
class PlayerHand : public GameObject
{

public:
    //�R���X�g���N�^
    PlayerHand(GameObject* parent);

    //�f�X�g���N�^
    ~PlayerHand();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};