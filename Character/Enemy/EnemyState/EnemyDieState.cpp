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
	//���ʂƂ��ɃR���C�_�[���Ă܂Ƃ߂ď�����悤�ɂ݂�����
	//enemy->EraseCollider(COLLIDER_ATTACK);
	//enemy->EraseCollider(COLLIDER_BODY);

	enemy->ClearCollider();

	//���񂾂��Ƃ����^AI�ɓ`����
	enemy->Dead();
	enemy->TellStatus();
=======
void EnemyDieState::Enter(Enemy* enemy, CharacterAI* AI)
{
	//���ʂƂ��ɃR���C�_�[���Ă܂Ƃ߂ď�����悤�ɂ݂�����
	enemy->EraseCollider(COLLIDER_ATTACK);
	enemy->EraseCollider(COLLIDER_BODY);

	//enemy->ClearCollider();

	//���񂾂��Ƃ����^AI�ɓ`����
	AI->TellStatus();
>>>>>>> MapEditor_ver.2
}
