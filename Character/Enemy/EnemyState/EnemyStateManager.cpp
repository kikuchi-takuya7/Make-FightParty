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

	//���̉��ɓ����蔻�肾�Ƃ����S�ɂ��锻��Ƃ��̋��ʏ����������B�G���W�j�A�u�[�g�L�����v��super::UpDate�݂����Ȃ�͈�ԍŏ��ɏ����ׂ��������ȕ��������瑽�����̏��ԁH�ڍׂ̓����ł��Ȃ�����

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
