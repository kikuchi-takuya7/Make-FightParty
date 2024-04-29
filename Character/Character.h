#pragma once
#include "../Engine/GameObject.h"

/// <summary>
/// �U���͂⎎������kill�|�C���g�����o����X�e�[�^�X
/// </summary>
struct Status {

    //�����Ɋ֌W����X�e�[�^�X
    int hp;                 //HP
    int attackPower;        //�G�����������ɗ^����_���[�W
    float moveSpeed;        //���̃L�����̈ړ����x
    bool dead;              //����ł��邩�ǂ����B����ł���true

    //�X�R�A�Ɋ֌W����X�e�[�^�X
    int winPoint;           //���������v��
    int killPoint;          //�������ɓ|�����G�̐�
    int trapKillPoint;      //�g���b�v�œ|����
    std::string playerName; //�v���C���[�̖��O

    //�f�t�H���g�R���X�g���N�^
    Status() {
        hp = ZERO;
        attackPower = ZERO;
        moveSpeed = ZERO;
        dead = false;
        winPoint = ZERO;
        killPoint = ZERO;
        trapKillPoint = ZERO;
        playerName = "noname";
    }

    //�����t���R���X�g���N�^
    Status(int h, int p, float s, bool d, int win, int kill, int obj, std::string n) {
        hp = h;
        attackPower = p;
        moveSpeed = s;
        dead = d;
        winPoint = win;
        killPoint = kill;
        trapKillPoint = obj;
        playerName = n;
    }

};

enum SoundEffect {
    HIT,
    DEAD,
    SE_NUM
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

    //////////////////�q���Ɍp��������֐�//////////////////////////////

    /// <summary>
    /// �p����p�̏������֐�
    /// </summary>
    virtual void ChildInitialize() {};

    /// <summary>
    /// �p����p��Update�֐�
    /// </summary>
    virtual void ChildUpdate() {};

    /// <summary>
    /// �p����p�̕`��֐�
    /// </summary>
    virtual void ChildDraw() {};

    /// <summary>
    /// �p����p�̊J���֐�
    /// </summary>
    virtual void ChildRelease() {};

    /// <summary>
    /// �L�����N�^�[���̈ړ������i�G�Ȃ�AI�A�l�Ȃ瑀��j
    /// </summary>
    virtual void MoveCharacter() {};

    /// <summary>
    /// Enemy���U����H��������Ɉ��m���ő_����ς���p�̊֐�
    /// </summary>
    virtual void ChangeTarget(GameObject* pTarget) {};

    /// <summary>
    /// ���^AI�ɏ���������֐�
    /// </summary>
    virtual void TellStatus() {};

    /////////////////////�����o�֐�/////////////////////////////////////

    /// <summary>
    /// �U���ɓ�����������HP�����炷�֐�
    /// </summary>
    /// <param name="damage">�H������_���[�W��</param>
    /// <returns>���̃_���[�W�Ŏ��S������true</returns>
    bool HitDamage(int damage);

    /// <summary>
    /// �X�e�[�^�X���Q�[���J�n���Ƀ��Z�b�g����֐��iwinPoint�͂��̂܂܁j
    /// </summary>
    void ResetStatus();

    //////////////////////////////////�v���C���[UI�Ƃ܂Ƃ߂ď�Ԃ�ς���֐�/////////////////

    void StopDraw();    //�`����~�߂�
    void StartDraw();   //�`���������
    void StopDrawUI();  //UI�̕`����~�߂�
    void Dead();        //�X�e�[�^�X��dead��true�ɂ���i���g�p�j

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

    //�U����H��������̃G�t�F�N�g
    void HitEffect();

    //���񂾎��ɂł�G�t�F�N�g
    void DieEffect();

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

    //���ʉ�
    int hSoundEffect_[SE_NUM];
    

private:

    //�U����H��������ɉ�]����̂Ɏg��
    XMFLOAT3 targetRot_;

};