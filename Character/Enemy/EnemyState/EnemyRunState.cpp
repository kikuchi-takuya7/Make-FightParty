#include "EnemyRunState.h"
#include "../../../AI/CharacterAI.h"

void EnemyRunState::Update(Enemy* enemy, CharacterAI* AI)
{

	HandleInput(enemy, AI);
}

void EnemyRunState::HandleInput(Enemy* enemy, CharacterAI* AI)
{
}

void EnemyRunState::Enter(Enemy* enemy, CharacterAI* AI)
{
}
