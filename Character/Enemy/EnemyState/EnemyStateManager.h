#pragma once
#include "EnemyAttackState.h"
#include "EnemyDieState.h"
#include "EnemyIdleState.h"
#include "EnemyJumpState.h"
#include "EnemyRunState.h"
#include "EnemyState.h"

class Enemy;

/// <summary>
/// enemy�̏�Ԃ��Ǘ�����
/// </summary>
class EnemyStateManager
{

public:

	//��������state��new���ĕς����莖�O�ɐÓI�ɕێ����Ă����΃������̐ߖ�ɂȂ���Ă����\�z
	static EnemyAttackState* enemyAttackState_;
	static EnemyDieState* enemyDieState_;
	static EnemyIdleState* enemyIdleState_;
	static EnemyJumpState* enemyJumpState_;
	static EnemyRunState* enemyRunState_;

	static EnemyState* enemyState_;

	EnemyStateManager();

	void Update(Enemy* enemy);

	void HandleInput(Enemy* enemy);

	void Enter(Enemy* enemy);

	/// <summary>
	/// ��Ԃ�ύX����
	/// </summary>
	/// <param name="change">�ύX��̏��</param>
	/// <param name="enemy">�ύX����v���C���[�̃|�C���^</param>
	void ChangeState(EnemyState* nextState, Enemy* enemy);

	//���ǂ����ɐÓI�Ɏc���Ă�state�Ō�������Ȃ炱�̊֐��g���Ă����Ǐ�̂��̃N���X���̕ϐ��g������Ӗ��Ȃ��ː�
};

//��y�͂���state���p�����Ă����ǌp���������R���悭�킩��Ȃ���������p�����Ȃ������B���Ă�������
