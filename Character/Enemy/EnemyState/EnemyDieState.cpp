#include "EnemyDieState.h"
#include "../Enemy.h"
<<<<<<< HEAD
=======
#include "../../../AI/CharacterAI.h"
>>>>>>> MapEditor_ver.2

void EnemyDieState::Update(Enemy* enemy, CharacterAI* AI)
{
}

void EnemyDieState::HandleInput(Enemy* enemy, CharacterAI* AI)
{
}

<<<<<<< HEAD
void EnemyDieState::Enter(Enemy* enemy)
{
	//死ぬときにコライダーつけてまとめて消せるようにみたいな
	//enemy->EraseCollider(COLLIDER_ATTACK);
	//enemy->EraseCollider(COLLIDER_BODY);

	enemy->ClearCollider();

	//死んだことをメタAIに伝える
	enemy->Dead();
	enemy->TellStatus();
=======
void EnemyDieState::Enter(Enemy* enemy, CharacterAI* AI)
{
	//死ぬときにコライダーつけてまとめて消せるようにみたいな
	enemy->EraseCollider(COLLIDER_ATTACK);
	enemy->EraseCollider(COLLIDER_BODY);

	//enemy->ClearCollider();

	//死んだことをメタAIに伝える
	AI->TellStatus();
>>>>>>> MapEditor_ver.2
}
