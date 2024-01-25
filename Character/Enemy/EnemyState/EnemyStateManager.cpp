#include "EnemyStateManager.h"

//�estatic�ϐ�������������Bstatic������O���[�o���Ȉʒu�ōŏ��ɏ��������Ȃ��ƃ_��
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
	//��Ԃ�ύX���āA���̏�Ԃ̏������������s��
	enemyState_ = nextState;
	enemyState_->Enter(enemy);
}
