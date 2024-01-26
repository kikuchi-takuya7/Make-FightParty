#include "EnemyAttackState.h"
#include "../Enemy.h"

void EnemyAttackState::Update(Enemy* enemy, CharacterAI* AI)
{
}

void EnemyAttackState::HandleInput(Enemy* enemy)
{
}

void EnemyAttackState::Enter(Enemy* enemy)
{
	time_ = 0;
	enemy->SetAttackCollider();
}
