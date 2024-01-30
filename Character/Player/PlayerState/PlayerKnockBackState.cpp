#include "PlayerKnockBackState.h"
#include "../../../Engine/Input.h"
#include "../Player.h"

namespace {

	const float KNOCKBACK_DISTANCE = 3.0f;
	const int KNOCKBACK_RIGIDITYFLAME = 30;//��炢�d���t���[��
}

void PlayerKnockBackState::Update(Player* player)
{

	flame_++;

	player->KnockBackUpdate(KNOCKBACK_RIGIDITYFLAME);

	/*if (playerPos == lastPoint_) {
		player->ChangeState(PLAYER_IDLE);
		player->ChangeKnockBack(false);
	}*/

	//��炢�d�����I�������
	if (flame_ >= KNOCKBACK_RIGIDITYFLAME) {
		player->ChangeState(PLAYER_IDLE);
	}

	HandleInput(player);
}

void PlayerKnockBackState::HandleInput(Player* player)
{
}

void PlayerKnockBackState::Enter(Player* player)
{
	flame_ = 0;
	player->KnockBackEnter(KNOCKBACK_DISTANCE);

}

