#pragma once
#include "../../Engine/GameObject.h"
#include "EnemyState/EnemyStateManager.h"
#include "EnemyState/EnemyState.h"
#include "../Character.h"
#include "../../AI/CharacterAI.h"

class PlayerStateManager;

/// <summary>
/// �L�����N�^�[AI�œ������G�̃N���X
/// </summary>
class Enemy : public Character
{

public:
    //�R���X�g���N�^
    Enemy(GameObject* parent);

    //�f�X�g���N�^
    ~Enemy();

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
    /// �ړ�����
    /// </summary>
    void Move();

    ///////////////////�A�N�Z�X�֐�/////////////////////////////////////
    Status GetStatus() { return status_; }
    void SetDead() { status_.isDead = true; }


private:

    int hModel_;

    //HP���̃X�e�[�^�X
    //Status status_;

    EnemyStateManager* pState_; //�G�̏�Ԃ�\��

    //�����蔻��
    //BoxCollider* pBodyCollision_;

};