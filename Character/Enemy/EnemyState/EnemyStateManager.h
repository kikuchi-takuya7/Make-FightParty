#pragma once
#include "EnemyAttackState.h"
#include "EnemyDieState.h"
#include "EnemyIdleState.h"
#include "EnemyJumpState.h"
#include "EnemyKnockBackState.h"
#include "EnemyRunState.h"
#include "EnemyState.h"

//class Enemy;



/// <summary>
/// enemy�̏�Ԃ��Ǘ�����
/// </summary>
class EnemyStateManager : public EnemyState
{

public:

	
	//��������state��new���ĕς����莖�O�ɐÓI�ɕێ����Ă����΃������̐ߖ�ɂȂ���Ă����\�z
	EnemyAttackState* enemyAttackState_;
	EnemyDieState* enemyDieState_;
	EnemyIdleState* enemyIdleState_;
	EnemyJumpState* enemyJumpState_;
	EnemyKnockBackState* enemyKnockBackState_;
	EnemyRunState* enemyRunState_;

	EnemyState* enemyState_;

	EnemyStateManager();

	void Update(Enemy* enemy, CharacterAI* AI) override;

	void HandleInput(Enemy* enemy, CharacterAI* AI) override;

<<<<<<< HEAD
	void Enter(Enemy* enemy) override;
=======
	void Enter(Enemy* enemy, CharacterAI* AI) override;
>>>>>>> MapEditor_ver.2

	/// <summary>
	/// ��Ԃ�ύX����
	/// </summary>
	/// <param name="change">�ύX��̏��</param>
	/// <param name="enemy">�ύX����v���C���[�̃|�C���^</param>
<<<<<<< HEAD
	void ChangeState(EnemyStatePattern nextState, Enemy* enemy);
=======
	void ChangeState(EnemyStatePattern nextState, Enemy* enemy, CharacterAI* AI);
>>>>>>> MapEditor_ver.2

	//�}�l�[�W����AI�̃C���X�^���X�����������Ō���update�ĂԂƂ��ɂ�AI�����Ƃ��ĕK�v������Ȃ�
	//�������̂��Ƃ��ꂼ���state�S���̃����o�ϐ���AI�̓��ꕨ���H������Ȃ񂩈Ⴄ�C������
};
