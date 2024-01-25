#pragma once
#include "../Engine/GameObject.h"

struct Status {
    int hp;
    int attackPower;
    bool isDead;
};


/// <summary>
/// �L�����N�^�[�̊��N���X
/// </summary>
class Character : public GameObject
{


public:
    //�R���X�g���N�^
    Character(GameObject* parent, std::string name);

    //�f�X�g���N�^
    ~Character();

    /////////////�I�[�o�[���C�h�����֐�/////////////////

    //������
    virtual void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    virtual void Draw() override;

    //�J��
    virtual void Release() override;

    /// <summary>
    /// �ʂ�collider�ɏՓ˂����Ƃ��ɌĂ΂��֐�
    /// </summary>
    /// <param name="pTarget">������������</param>
    virtual void OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType) override;


    /////////////////////�����o�֐�/////////////////////////////////////

    /// <summary>
    /// �U���ɓ���������
    /// </summary>
    /// <param name="damage">�H������_���[�W��</param>
    void HitDamage(int damage);

    //////////////////�q���Ɍp��������֐�//////////////////////////////

    /// <summary>
    /// �p����p�̏�����
    /// </summary>
    virtual void ChildInitialize() {};

    /// <summary>
    /// �p����p��Update
    /// </summary>
    virtual void ChildUpdate() {};

    /// <summary>
    /// �p����p�̕`��
    /// </summary>
    virtual void ChildDraw() {};

    /// <summary>
    /// �p����p�̊J��
    /// </summary>
    virtual void ChildRelease() {};

    /// <summary>
    /// �L�����N�^�[�̈ړ�����
    /// </summary>
    virtual void MoveCharacter() {};

    ///////////////////�A�N�Z�X�֐�/////////////////////////////////////
    Status GetStatus() { return status_; }
    void SetDead() { status_.isDead = true; }

protected:

    int hModel_;

    //HP���̃X�e�[�^�X
    Status status_;

    //CharacterStateManager* pState_; //�v���C���[�̏�Ԃ�\��

    //�����蔻��
    BoxCollider* pBodyCollision_;
    BoxCollider* pAttackCollision_;

private:

    



};