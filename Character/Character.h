#pragma once
#include "../Engine/GameObject.h"

struct Status {
    int hp;
    int attackPower;
    bool dead;

    int winPoint;
    int killPoint;
    int trapKillPoint;
    std::string playerName;

    Status() {
        hp = ZERO;
        attackPower = ZERO;
        dead = false;
        winPoint = ZERO;
        killPoint = ZERO;
        trapKillPoint = ZERO;
        playerName = "noname";
    }

    Status(int h, int p, bool d, int win, int kill, int obj, std::string n) {
        hp = h;
        attackPower = p;
        dead = d;
        winPoint = win;
        killPoint = kill;
        trapKillPoint = obj;
        playerName = n;
    }

};

class PlayerUI;
class CharacterStateManager;
enum CharacterStateList;

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
    void OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType) override;


    /////////////////////�����o�֐�/////////////////////////////////////

    /// <summary>
    /// �U���ɓ���������
    /// </summary>
    /// <param name="damage">�H������_���[�W��</param>
    /// <returns>���̃_���[�W�Ŏ��S������true</returns>
    bool HitDamage(int damage);

    void StopDraw();

    void StartDraw();

    void Dead();

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
    virtual void MoveCharacter();

    //�q���̓����蔻��iEnemy��Player�Ŏ኱�������Ⴄ�j
    virtual void ChildOnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType) {};

    //���^AI�ɏ���������֐�
    virtual void TellStatus() {};


    //state�܂Ƃ߂ď������������ǉ��Ƃ��ł��Ȃ�����
    void ResetStatus();
    

    ///////////////////�A�N�Z�X�֐�/////////////////////////////////////

    /// <summary>
    /// ���݂�state��ς���
    /// </summary>
    /// <param name="nextState">����state</param>
    void ChangeState(CharacterStateList nextState);


    Status GetStatus() { return status_; }
    XMFLOAT3 GetStartPos() { return startPos_; }
    XMFLOAT3 GetTargetRot() { return targetRot_; }
    void SetStatus(Status status) { status_ = status; }
    void SetStartPos(XMFLOAT3 pos) { startPos_ = pos; }
    void SetColliderRotate(XMFLOAT3 rotate) { pAttackCollision_->SetRotate(rotate); }
    void SetTargetRotate(XMFLOAT3 rot) { targetRot_ = rot; }
    void SetAttackCollider() { AddCollider(pAttackCollision_, ColliderAttackType::COLLIDER_ATTACK); }
    void SetUIPos(XMFLOAT3 pos);

    void SetCharacterName(std::string name);

protected:

    //���f���ԍ�
    int hModel_;

    //HP���̃X�e�[�^�X
    Status status_;

    //�L�����N�^�[�N���X�̃X�e�[�g
    CharacterStateManager* pState_;

    //�����蔻��
    BoxCollider* pBodyCollision_;
    BoxCollider* pAttackCollision_;

    //���ꂼ��̃L�����̃X�^�[�g�n�_
    XMFLOAT3 startPos_;

    //�O�ɂ������W
    XMFLOAT3 prevPos_;

    //�L�����N�^�[�����ꂼ��Ŏ���UI
    PlayerUI* pPlayerUI_;



private:

    

    ////////////////////////////////////////////

    bool stopDraw_;

    //�U����H��������ɉ�]����̂Ɏg��
    XMFLOAT3 targetRot_;

};