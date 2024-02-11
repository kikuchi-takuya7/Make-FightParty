#include "EnemyIdleState.h"
#include "../../../AI/CharacterAI.h"

void EnemyIdleState::Update(Enemy* enemy, CharacterAI* AI)
{
	
	HandleInput(enemy, AI);
}

void EnemyIdleState::HandleInput(Enemy* enemy, CharacterAI* AI)
{
	AI->IsAttack();

}

<<<<<<< HEAD
void EnemyIdleState::Enter(Enemy* enemy)
=======
void EnemyIdleState::Enter(Enemy* enemy, CharacterAI* AI)
>>>>>>> MapEditor_ver.2
{
}
