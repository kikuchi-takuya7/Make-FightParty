#include "PlayerKnockBackState.h"
#include "../../../Engine/Input.h"
#include "../Player.h"

void PlayerKnockBackState::Update(Player* player)
{

	time_++;

	//敵の向いている方向が欲しい.できればEnterの時点で飛ばされる座標を取っておいて、そこに着いたら動けるって感じにしたい。緩急付けて

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
