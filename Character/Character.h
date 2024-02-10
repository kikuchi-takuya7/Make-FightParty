#pragma once
#include "../Engine/GameObject.h"

struct Status {
    int hp;
    int attackPower;
    int winPoint;
    bool dead;
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

    void StopDraw();

    void StartDraw();

    void Dead();

    //////////////////////KnockBackstate�Ŏg���֐�/////////////////////////////

    void KnockBackEnter(float distance);

    void KnockBackUpdate(int rigidityFlame);

    float GetRateValue(float begin, float end, float rate);

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

    virtual void ChildOnCollision() {};

    //state�܂Ƃ߂ď������������ǉ��Ƃ��ł��Ȃ�����
    virtual void ResetStatus() {};

    ///////////////////�A�N�Z�X�֐�/////////////////////////////////////
    Status GetStatus() { return status_; }
    XMFLOAT3 GetStartPos() { return startPos_; }
    void SetStatus(Status status) { status_ = status; }
    void SetStartPos(XMFLOAT3 pos) { startPos_ = pos; }
    void SetColliderRotate(XMFLOAT3 rotate) { pAttackCollision_->SetRotate(rotate); }
    void SetTargetRotate(XMFLOAT3 rot) { targetRot_ = rot; }
    void SetAttackCollider() { AddCollider(pAttackCollision_, ColliderAttackType::COLLIDER_ATTACK); }


protected:

    int hModel_;

    //HP���̃X�e�[�^�X
    Status status_;

    //CharacterStateManager* pState_; //�v���C���[�̏�Ԃ�\��

    //�����蔻��
    BoxCollider* pBodyCollision_;
    BoxCollider* pAttackCollision_;

    //���ꂼ��̃L�����̃X�^�[�g�n�_
    XMFLOAT3 startPos_;

private:


    //////�m�b�N�o�b�N�֐��Ŏg�����/////////

    //�ɋ}��t���郌�[�g
    float knockBackRate_;

    //�ŏI�I�Ȉʒu
    XMFLOAT3 lastPoint_;

    XMFLOAT3 targetRot_;

    ////////////////////////////////////////////

    bool stopDraw_;


};