#include "EnemyDieState.h"
#include "../Enemy.h"
#include "../../../AI/CharacterAI.h"

void EnemyDieState::Update(Enemy* enemy, CharacterAI* AI)
{
}

void EnemyDieState::HandleInput(Enemy* enemy, CharacterAI* AI)
{
}

void EnemyDieState::Enter(Enemy* enemy, CharacterAI* AI)
{

	enemy->EraseCollider(COLLIDER_ATTACK);
	enemy->EraseCollider(COLLIDER_BODY);

	//enemy->ClearCollider();

	//Ž€‚ñ‚¾‚±‚Æ‚ðƒƒ^AI‚É“`‚¦‚é
	AI->TellStatus();
}
