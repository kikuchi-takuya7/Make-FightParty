#pragma once
#include "../../Engine/GameObject.h"
//#include "PlayerState/PlayerState.h"
#include "PlayerState/PlayerStateManager.h"
#include "../Character.h"

class PlayerStateManager;

/// <summary>
/// ���삷��v���C���[�̃N���X
/// </summary>
class Player : public Character
{

public:
    //�R���X�g���N�^
    Player(GameObject* parent);

    //�f�X�g���N�^
    ~Player();

    /////////////�I�[�o�[���C�h�����֐�/////////////////

    //������
    void ChildInitialize() override;

    //�X�V
    void ChildUpdate() override;

    //�`��
    void ChildDraw() override;

    //�J��
    void ChildRelease() override;

    /// <summary>
    /// �ʂ�collider�ɏՓ˂����Ƃ��ɌĂ΂��֐�
    /// </summary>
    /// <param name="pTarget">������������</param>
    void OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType) override;


    /////////////////////�����o�֐�/////////////////////////////////////

    ///////////////////�A�N�Z�X�֐�/////////////////////////////////////
    void ChangeState(PlayerStatePattern nextState);


private:

    //int hModel_;

    ////HP���̃X�e�[�^�X
    //Status status_;

    PlayerStateManager* pState_; //�v���C���[�̏�Ԃ�\��
};