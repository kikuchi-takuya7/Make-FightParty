#include "EnemyAttackState.h"
#include "../Enemy.h"

void EnemyAttackState::Update(Enemy* enemy, CharacterAI* AI)
{
	time_++;

	if (time_ >= 60) {
		enemy->EraseCollider(COLLIDER_ATTACK);
		enemy->ChangeState(ENEMY_IDLE);
	}

	HandleInput(enemy, AI);
}

void EnemyAttackState::HandleInput(Enemy* enemy, CharacterAI* AI)
{

}

void EnemyAttackState::Enter(Enemy* enemy)
{
	time_ = 0;
	enemy->SetAttackCollider();
}
