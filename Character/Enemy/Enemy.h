#pragma once
#include "../../Engine/GameObject.h"
#include "EnemyState/EnemyStateManager.h"
#include "EnemyState/EnemyState.h"
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
    void OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType) override;

    /////////////////////�����o�֐�/////////////////////////////////////

    /// <summary>
    /// CharavterAI�Ɉړ�����ꏊ�𕷂��Ĉړ�����
    /// </summary>
    void MoveCharacter() override;

    /////////////////////AI�ɓ`����֐�/////////////////////////////



    ///////////////////�A�N�Z�X�֐�/////////////////////////////////////
    void SetCharacterAI(CharacterAI* AI) { pCharacterAI_ = AI; }

    void ChangeState(EnemyStatePattern nextState);
    
    //�Z�b�^�[�̒��ŃZ�b�^�[�͌ĂׂȂ��������畁�ʂ�gameScene�ŗp�ӂ����Ⴄ
    //void SetNavi(NavigationAI* naviAI) { pCharacterAI_->SetNavigationAI(naviAI); }


private:

    int hModel_;

    //HP���̃X�e�[�^�X
    //Status status_;

    EnemyStateManager* pState_; //�G�̏�Ԃ�\��

    CharacterAI* pCharacterAI_;//�F��Ȕ��f�����Ă����AI�̂���

    //�����蔻��
    //BoxCollider* pBodyCollision_;

};