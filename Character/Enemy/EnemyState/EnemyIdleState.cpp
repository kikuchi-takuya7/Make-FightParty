#include "EnemyIdleState.h"
#include "../../../AI/CharacterAI.h"

void EnemyIdleState::Update(Enemy* enemy, CharacterAI* AI)
{
	
	HandleInput(enemy, AI);
}

void EnemyIdleState::HandleInput(Enemy* enemy, CharacterAI* AI)
{
}

void EnemyIdleState::Enter(Enemy* enemy, CharacterAI* AI)
{
}
