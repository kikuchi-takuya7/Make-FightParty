#pragma once
#include "../../Engine/GameObject.h"
#include "../Character.h"

class PlayerStateManager;

/// <summary>
/// ���삷��v���C���[�̃N���X
/// </summary>
class Player : public Character
{

public:
    //�R���X�g���N�^
    Player(GameObject* parent);

    //�f�X�g���N�^
    ~Player();

    /////////////�I�[�o�[���C�h�����֐�/////////////////

    //������
    void ChildInitialize() override;

    //�X�V
    void ChildUpdate() override;

    //�`��
    void ChildDraw() override;

    //�J��
    void ChildRelease() override;

    /////////////////////�����o�֐�/////////////////////////////////////

    /// <summary>
    /// ���͂ɂ���Ĉړ�����֐�
    /// </summary>
    void MoveCharacter() override;

    /// <summary>
    /// ���^AI�ɃX�e�[�^�X��`����֐�
    /// </summary>
    void TellStatus() override;


private:

    

};