#pragma once
#include "../Engine/GameObject.h"
#include "../State/PlayerState.h"
#include "../State/PlayerStateManager.h"

struct Status {
    int hp;
    int attackPower;
    bool isDead;
};

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
    /// �v���C���[�̈ړ�����
    /// </summary>
    void MovePlayer();

    ///////////////////�A�N�Z�X�֐�/////////////////////////////////////
    Status GetStatus() { return status_; }
    void SetDead() { status_.isDead = true; }


private:

    int hModel_;

    //HP���̃X�e�[�^�X
    Status status_;

    //�����蔻��
    BoxCollider* pBodyCollision_;
    BoxCollider* pAttackCollision_;
    XMFLOAT3 attackCollisionCenter_;//AttackCollision�̍U������̌���
    XMFLOAT3 attackCollisionSize_;//�U������̑傫��

    PlayerStateManager* pState_; //�v���C���[�̏�Ԃ�\��

};