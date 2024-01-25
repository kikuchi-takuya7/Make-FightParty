#include "EnemyStateManager.h"

//各static変数を初期化する。staticだからグローバルな位置で最初に初期化しないとダメ
EnemyAttackState* EnemyStateManager::enemyAttackState_ = new EnemyAttackState;
EnemyDieState* EnemyStateManager::enemyDieState_ = new EnemyDieState;
EnemyIdleState* EnemyStateManager::enemyIdleState_ = new EnemyIdleState;
EnemyJumpState* EnemyStateManager::enemyJumpState_ = new EnemyJumpState;
EnemyRunState* EnemyStateManager::enemyRunState_ = new EnemyRunState;

EnemyState* EnemyStateManager::enemyState_ = new EnemyState;

EnemyStateManager::EnemyStateManager()
{


}

void EnemyStateManager::Update(Enemy* enemy)
{
	enemyState_->Update(enemy);

	

}

void EnemyStateManager::HandleInput(Enemy* enemy)
{
}

void EnemyStateManager::Enter(Enemy* enemy)
{
}

void EnemyStateManager::ChangeState(EnemyState* nextState, Enemy* enemy)
{
	//状態を変更して、その状態の初期化処理を行う
	enemyState_ = nextState;
	enemyState_->Enter(enemy);
}
