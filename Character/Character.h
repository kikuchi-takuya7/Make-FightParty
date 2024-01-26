#pragma once
#include "../Engine/GameObject.h"

struct Status {
    int hp;
    int attackPower;
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
    virtual void OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType) override;


    /////////////////////�����o�֐�/////////////////////////////////////

    /// <summary>
    /// �U���ɓ���������
    /// </summary>
    /// <param name="damage">�H������_���[�W��</param>
    void HitDamage(int damage);

    /// <summary>
    /// �U���p�̃R���C�_�[���Z�b�g����
    /// </summary>
    void SetAttackCollider();

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
    void ChangeKnockBack(bool next) { isKnockBack_ = next; }
    bool IsKnockBack() { return isKnockBack_; }

protected:

    int hModel_;

    //HP���̃X�e�[�^�X
    Status status_;

    //CharacterStateManager* pState_; //�v���C���[�̏�Ԃ�\��

    //�����蔻��
    BoxCollider* pBodyCollision_;
    BoxCollider* pAttackCollision_;

    bool isKnockBack_;

private:

    



};