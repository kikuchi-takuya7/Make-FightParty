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
    /// �ʂ�collider�ɏՓ˂����Ƃ��ɌĂ΂��֐�
    /// </summary>
    /// <param name="pTarget">������������</param>
    void ChildOnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType) override;

    /////////////////////�����o�֐�/////////////////////////////////////

    /// <summary>
    /// CharavterAI�Ɉړ�����ꏊ�𕷂��Ĉړ�����
    /// </summary>
    void MoveCharacter() override;

    /////////////////////AI�ɓ`����֐�/////////////////////////////

    void TellStatus() override;

    ///////////////////�A�N�Z�X�֐�/////////////////////////////////////
    void SetCharacterAI(CharacterAI* AI) { pCharacterAI_ = AI; }
    
    //�Z�b�^�[�̒��ŃZ�b�^�[�͌ĂׂȂ��������畁�ʂ�gameScene�ŗp�ӂ����Ⴄ
    //void SetNavi(NavigationAI* naviAI) { pCharacterAI_->SetNavigationAI(naviAI); }


private:


    CharacterAI* pCharacterAI_;//�F��Ȕ��f�����Ă����AI�̂���

};