#pragma once
#include "../../Engine/GameObject.h"

struct Status {
    int hp;
    int attackPower;
    bool isDead;
};


/// <summary>
/// ���삷��v���C���[�̃N���X
/// </summary>
class Character : public GameObject
{

public:
    //�R���X�g���N�^
    Character(GameObject* parent);

    //�f�X�g���N�^
    ~Character();

    /////////////�I�[�o�[���C�h�����֐�/////////////////

    //������
    virtual void Initialize() override;

    //�X�V
    virtual void Update() override;

    //�`��
    virtual void Draw() override;

    //�J��
    virtual void Release() override;

    /// <summary>
    /// �ʂ�collider�ɏՓ˂����Ƃ��ɌĂ΂��֐�
    /// </summary>
    /// <param name="pTarget">������������</param>
    virtual void OnCollision(GameObject* pTarget) override;


    /////////////////////�����o�֐�/////////////////////////////////////


    ///////////////////�A�N�Z�X�֐�/////////////////////////////////////
    Status GetStatus() { return status_; }
    void SetDead() { status_.isDead = true; }


private:

    int hModel_;

    //HP���̃X�e�[�^�X
    Status status_;

    //CharacterStateManager* pState_; //�v���C���[�̏�Ԃ�\��

    //�����蔻��
    BoxCollider* pBodyCollision_;
    BoxCollider* pAttackCollision_;
    XMFLOAT3 attackCollisionCenter_;//AttackCollision�̍U������̌���
    XMFLOAT3 attackCollisionSize_;//�U������̑傫��



};