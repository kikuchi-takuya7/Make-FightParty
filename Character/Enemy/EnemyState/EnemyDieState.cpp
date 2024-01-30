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
	//死ぬときにコライダーつけてまとめて消せるようにみたいな
	//enemy->EraseCollider(COLLIDER_ATTACK);
	//enemy->EraseCollider(COLLIDER_BODY);

	enemy->ClearCollider();
}
