#pragma once
#include "../Engine/GameObject.h"
#include "../State/PlayerState.h"
#include "../Engine/Global.h"

//���������Ǘ�����N���X
class Player : public GameObject
{

public:
    //�R���X�g���N�^
    Player(GameObject* parent);

    //�f�X�g���N�^
    ~Player();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    

private:

    int hModel_;

    PlayerState* pState_; //�v���C���[�̏�Ԃ�\��

};