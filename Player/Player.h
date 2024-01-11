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

    /// <summary>
    /// �v���C���[�̈ړ�����
    /// </summary>
    void MovePlayer();

    /////////�A�N�Z�X�֐�////////
    Status GetStatus() { return status_; }
    void SetDead() { status_.isDead = true; }


private:

    int hModel_;

    Status status_;

    BoxCollider* pBodyCollision_;

    BoxCollider* pAttackCollision_;

    PlayerStateManager* pState_; //�v���C���[�̏�Ԃ�\��

};