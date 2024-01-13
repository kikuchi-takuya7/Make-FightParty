#pragma once
#include "../../Engine/GameObject.h"
#include "EnemyState/EnemyStateManager.h"
#include "EnemyState/EnemyState.h"


struct Status {
    int hp;
    int attackPower;
    bool isDead;
};

class PlayerStateManager;

/// <summary>
/// ���삷��v���C���[�̃N���X
/// </summary>
class Enemy : public GameObject
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
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    /// <summary>
    /// �ʂ�collider�ɏՓ˂����Ƃ��ɌĂ΂��֐�
    /// </summary>
    /// <param name="pTarget">������������</param>
    void OnCollision(GameObject* pTarget) override;

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
    Status status_;

    EnemyStateManager* pState_; //�G�̏�Ԃ�\��

    //�����蔻��
    BoxCollider* pBodyCollision_;

};