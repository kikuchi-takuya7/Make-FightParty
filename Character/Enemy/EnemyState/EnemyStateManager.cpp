#include "EnemyStateManager.h"
#include "../../../AI/CharacterAI.h"
#include "../Enemy.h"

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

	
	//攻撃してる時に攻撃喰らった時に攻撃判定を消す用。それぞれのEnterに置いた方がいいかな
	if (enemyState_ != enemyAttackState_) {

		enemy->EraseCollider(COLLIDER_ATTACK);
	}
	
	//移動不可状態なら移動はしない
	if (enemyState_ == enemyDieState_ || enemyState_ == enemyKnockBackState_ || enemyState_ == enemyAttackState_) {
		
		enemyState_->Update(enemy, AI);
		return;
	}

	AI->MoveEnemy();
	enemyState_->Update(enemy, AI);

	//死ぬ処理ここでいい？
	if (enemy->GetStatus().hp <= 0) {

		ChangeState(ENEMY_DIE, enemy, AI);
	}

}

void EnemyStateManager::HandleInput(Enemy* enemy, CharacterAI* AI)
{
}

void EnemyStateManager::Enter(Enemy* enemy, CharacterAI* AI)
{
}

void EnemyStateManager::ChangeState(EnemyStatePattern nextState, Enemy* enemy, CharacterAI* AI)
{
	//状態を変更して、その状態の初期化処理を行う
	switch (nextState)
	{
	case ENEMY_ATTACK:
		enemyState_ = enemyAttackState_;
		break;

	case ENEMY_DIE:
		enemyState_ = enemyDieState_;
		break;

	case ENEMY_IDLE:
		enemyState_ = enemyIdleState_;
		break;

	case ENEMY_JUMP:
		enemyState_ = enemyJumpState_;
		break;

	case ENEMY_KNOCKBACK:
		enemyState_ = enemyKnockBackState_;
		break;

	case ENEMY_RUN:
		enemyState_ = enemyRunState_;
		break;

	default:
		return;
		break;
	}

	enemyState_->Enter(enemy, AI);
}

