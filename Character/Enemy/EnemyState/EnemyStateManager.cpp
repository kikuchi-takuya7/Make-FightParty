#include "EnemyStateManager.h"
#include "../../../AI/CharacterAI.h"
#include "../Enemy.h"


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


	
	//UŒ‚‚µ‚Ä‚é‚ÉUŒ‚‹ò‚ç‚Á‚½‚ÉUŒ‚”»’è‚ğÁ‚·—pB‚»‚ê‚¼‚ê‚ÌEnter‚É’u‚¢‚½•û‚ª‚¢‚¢‚©‚È
	if (enemyState_ != enemyAttackState_) {

		enemy->EraseCollider(COLLIDER_ATTACK);
	}
	
	//ˆÚ“®•s‰Âó‘Ô‚È‚çˆÚ“®‚Í‚µ‚È‚¢
	if (enemyState_ == enemyDieState_ || enemyState_ == enemyKnockBackState_ || enemyState_ == enemyAttackState_) {
		
		enemyState_->Update(enemy, AI);
		return;
	}

	//€‚Êˆ—
	if (enemy->GetStatus().dead) {

		ChangeState(ENEMY_DIE, enemy, AI);
	}

	AI->MoveEnemy();
	enemyState_->Update(enemy, AI);

	//”X‚Ìˆ—‚ªI‚í‚Á‚ÄAUŒ‚”ÍˆÍ“à‚È‚çUŒ‚‚·‚é
	AI->IsAttack();

}

void EnemyStateManager::HandleInput(Enemy* enemy, CharacterAI* AI)
{
}

void EnemyStateManager::Enter(Enemy* enemy, CharacterAI* AI)
{
}

void EnemyStateManager::ChangeState(EnemyStatePattern nextState, Enemy* enemy, CharacterAI* AI)
{
	//ó‘Ô‚ğ•ÏX‚µ‚ÄA‚»‚Ìó‘Ô‚Ì‰Šú‰»ˆ—‚ğs‚¤
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

