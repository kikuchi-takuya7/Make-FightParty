#include "EnemyStateManager.h"

//�estatic�ϐ�������������Bstatic������O���[�o���Ȉʒu�ōŏ��ɏ��������Ȃ��ƃ_��


EnemyStateManager::EnemyStateManager()
{
	enemyAttackState_ = new EnemyAttackState;
	enemyDieState_ = new EnemyDieState;
	enemyIdleState_ = new EnemyIdleState;
	enemyJumpState_ = new EnemyJumpState;
	enemyKnockBackState_ = new EnemyKnockBackState;
	enemyRunState_ = new EnemyRunState;

	enemyState_ = new EnemyState;

}

void EnemyStateManager::Update(Enemy* enemy, CharacterAI* AI)
{


	AI->MoveEnemy();

	enemyState_->Update(enemy, AI);

	

}

void EnemyStateManager::HandleInput(Enemy* enemy)
{
}

void EnemyStateManager::Enter(Enemy* enemy)
{
}

void EnemyStateManager::ChangeState(EnemyStatePattern nextState, Enemy* enemy)
{
	//��Ԃ�ύX���āA���̏�Ԃ̏������������s��
	switch (nextState)
	{
	case EnemyStatePattern::ATTACK:
		enemyState_ = enemyAttackState_;
		break;

	case EnemyStatePattern::DIE:
		enemyState_ = enemyDieState_;
		break;

	case EnemyStatePattern::IDLE:
		enemyState_ = enemyIdleState_;
		break;

	case EnemyStatePattern::JUMP:
		enemyState_ = enemyJumpState_;
		break;

	case EnemyStatePattern::KNOCKBACK:
		enemyState_ = enemyKnockBackState_;
		break;

	case EnemyStatePattern::RUN:
		enemyState_ = enemyRunState_;
		break;

	case EnemyStatePattern::NUM:

	default:
		return;
		break;
	}

	enemyState_->Enter(enemy);
}

