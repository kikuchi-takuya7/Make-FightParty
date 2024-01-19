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
    void Initialize() override;

    //�X�V
    void ChildUpdate() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    /// <summary>
    /// �ʂ�collider�ɏՓ˂����Ƃ��ɌĂ΂��֐�
    /// </summary>
    /// <param name="pTarget">������������</param>
    void OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetTypee) override;


    /////////////////////�����o�֐�/////////////////////////////////////

    /// <summary>
    /// �v���C���[�̈ړ�����
    /// </summary>
    void MovePlayer();

    ///////////////////�A�N�Z�X�֐�/////////////////////////////////////
    Status GetStatus() { return status_; }
    void SetDead() { status_.isDead = true; }


private:

    //int hModel_;

    ////HP���̃X�e�[�^�X
    //Status status_;

    PlayerStateManager* pState_; //�v���C���[�̏�Ԃ�\��

    ////�����蔻��
    //BoxCollider* pBodyCollision_;
    //BoxCollider* pAttackCollision_;
    

};