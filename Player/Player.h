#pragma once
#include "../Engine/GameObject.h"
#include "../State/PlayerState.h"
#include "../State/PlayerStateManager.h"


class PlayerStateManager;

/// <summary>
/// ���삷��v���C���[�̃N���X
/// </summary>
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

    /// <summary>
    /// �v���C���[�̈ړ�����
    /// </summary>
    void MovePlayer();

private:

    int hModel_;

    PlayerStateManager* pState_; //�v���C���[�̏�Ԃ�\��

};