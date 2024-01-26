#include "PlayerKnockBackState.h"
#include "../../../Engine/Input.h"
#include "../Player.h"

void PlayerKnockBackState::Update(Player* player)
{

	time_++;

	//�G�̌����Ă���������~����.�ł����Enter�̎��_�Ŕ�΂������W������Ă����āA�����ɒ������瓮������Ċ����ɂ������B�ɋ}�t����

	XMFLOAT3 playerPos = player->GetPosition();
	playerPos.x += 0.1f;
	player->SetPosition(playerPos);

	if (time_ >= 30) {
		player->ChangeState(PLAYER_IDLE);
		player->ChangeKnockBack(false);
	}

	HandleInput(player);
}

void PlayerKnockBackState::HandleInput(Player* player)
{
}

void PlayerKnockBackState::Enter(Player* player)
{
	time_ = ZERO;
	player->ChangeKnockBack(true);
}
