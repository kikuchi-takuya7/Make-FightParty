#include "EnemyStateManager.h"

//各static変数を初期化する。staticだからグローバルな位置で最初に初期化しないとダメ


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
	//状態を変更して、その状態の初期化処理を行う
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

