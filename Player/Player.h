#pragma once
#include "../Engine/GameObject.h"
#include "../State/PlayerState.h"
#include "../State/PlayerStateManager.h"


class PlayerState;

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

    /// <summary>
    /// ��Ԃ�ύX����
    /// </summary>
    /// <param name="nextState">���̏��</param>
    void ChangeState(PlayerStateManager* nextState);

    /// <summary>
    /// �v���C���[�̈ړ�����
    /// </summary>
    void MovePlayer();

private:

    int hModel_;

    PlayerStateManager* pState_; //�v���C���[�̏�Ԃ�\��

};