#pragma once
#include "../../Engine/GameObject.h"
#include "../Character.h"

class EnemyStateManager;
class NavigationAI;
class CharacterAI;

/// <summary>
/// �L�����N�^�[AI�œ������G�̃N���X
/// </summary>
class Enemy : public Character
{

public:
    //�R���X�g���N�^
    Enemy(GameObject* parent);

    //�f�X�g���N�^
    ~Enemy();

    /////////////�I�[�o�[���C�h�����֐�/////////////////

    //������
    void ChildInitialize() override;

    //�X�V
    void ChildUpdate() override;

    //�`��
    void ChildDraw() override;

    //�J��
    void ChildRelease() override;

    /// <summary>
    /// �G����U����H��������ɌĂяo�����A���m���Ń^�[�Q�b�g��ς���֐�
    /// </summary>
    void ChangeTarget(GameObject* pTarget) override;

    /////////////////////�����o�֐�/////////////////////////////////////

    /// <summary>
    /// CharavterAI�Ɉړ�����ꏊ�𕷂��Ĉړ�����֐�
    /// </summary>
    void MoveCharacter() override;

    /// <summary>
    /// ���^AI�Ɍ��݂̃X�e�[�^�X��`����֐�
    /// </summary>
    void TellStatus() override;

    ///////////////////�A�N�Z�X�֐�/////////////////////////////////////
    void SetCharacterAI(CharacterAI* AI) { pCharacterAI_ = AI; }

private:

    //�L�����N�^�[AI�̃C���X�^���X
    CharacterAI* pCharacterAI_;

};