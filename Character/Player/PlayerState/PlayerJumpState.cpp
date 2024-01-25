#include "PlayerJumpState.h"
#include "PlayerStateManager.h"
#include "../Player.h"

namespace {
	const float JUMP_VELOCITY = 1.0f;
	const float GRAVITY = 0.1f;
}

void PlayerJumpState::Update(Player* player)
{
	//ジャンプさせる
	XMFLOAT3 playerPos = player->GetPosition();
	playerPos.y += velocity_;
	velocity_ -= GRAVITY;

	//もし地面に着いたらstateを変える
	if (playerPos.y <= ZERO) {
		playerPos.y = 0;

		player->ChangeState(IDLE);
	}

	player->SetPosition(playerPos);

	

	HandleInput(player);
}

void PlayerJumpState::HandleInput(Player* player)
{
	/*if (Input::IsKeyDown(DIK_Q)) {
		PlayerStateManager::playerState_ = PlayerStateManager::playerDieState_;
		PlayerStateManager::playerState_->Enter(player);
	}*/

	if (Input::IsKeyDown(DIK_F)) {
		player->ChangeState(ATTACK);
	}
}

void PlayerJumpState::Enter(Player* player)
{

	//メンバ変数を初期化する
	velocity_ = JUMP_VELOCITY;

}
