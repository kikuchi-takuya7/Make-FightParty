#include "EnemyStateManager.h"
#include "../../../AI/CharacterAI.h"
#include "../Enemy.h"

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

	
	//�U�����Ă鎞�ɍU�����������ɍU������������p�B���ꂼ���Enter�ɒu����������������
	if (enemyState_ != enemyAttackState_) {

		enemy->EraseCollider(COLLIDER_ATTACK);
	}
	
	//�ړ��s��ԂȂ�ړ��͂��Ȃ�
	if (enemyState_ == enemyDieState_ || enemyState_ == enemyKnockBackState_ || enemyState_ == enemyAttackState_) {
		
		enemyState_->Update(enemy, AI);
		return;
	}

	AI->MoveEnemy();
	enemyState_->Update(enemy, AI);

	//���ʏ��������ł����H
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
	//��Ԃ�ύX���āA���̏�Ԃ̏������������s��
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

