#include "EnemyKnockBackState.h"
#include "../../../Engine/Input.h"
#include "../Enemy.h"

namespace {

	const float KNOCKBACK_DISTANCE = 3.0f;
	const int KNOCKBACK_RIGIDITYFLAME = 30;//喰らい硬直フレーム
}

void EnemyKnockBackState::Update(Enemy* enemy, CharacterAI* AI)
{

	flame_++;

	enemy->KnockBackUpdate(KNOCKBACK_RIGIDITYFLAME);

	/*if (enemyPos == lastPoint_) {
		enemy->ChangeState(PLAYER_IDLE);
		enemy->ChangeKnockBack(false);
	}*/

	//喰らい硬直が終わったら
	if (flame_ >= KNOCKBACK_RIGIDITYFLAME) {
		enemy->ChangeState(ENEMY_IDLE);
	}

	HandleInput(enemy,AI);
}

void EnemyKnockBackState::HandleInput(Enemy* enemy, CharacterAI* AI)
{
}

void EnemyKnockBackState::Enter(Enemy* enemy, CharacterAI* AI)
{
	flame_ = 0;
	enemy->KnockBackEnter(KNOCKBACK_DISTANCE);

}

float EnemyKnockBackState::GetRateValue(float begin, float end, float rate)
{
	return (end - begin) * rate + begin;
}
