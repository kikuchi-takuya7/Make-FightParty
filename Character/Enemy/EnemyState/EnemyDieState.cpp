#include "EnemyDieState.h"
#include "../Enemy.h"

void EnemyDieState::Update(Enemy* enemy, CharacterAI* AI)
{
}

void EnemyDieState::HandleInput(Enemy* enemy, CharacterAI* AI)
{
}

void EnemyDieState::Enter(Enemy* enemy)
{
	//enemy->ClearCollider();
	enemy->KillMe();
}
