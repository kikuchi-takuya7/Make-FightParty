#include "PlayerJumpState.h"
#include "PlayerStateManager.h"
#include "../Player/Player.h"

namespace {
	const float JUMP_VELOCITY = 1.0f;
	const float GRAVITY = 0.1f;
}

void PlayerJumpState::Update(Player* player)
{
	//�W�����v������
	XMFLOAT3 playerPos = player->GetPosition();
	playerPos.y += velocity_;
	velocity_ -= GRAVITY;

	//�����n�ʂɒ�������state��ς���
	if (playerPos.y <= ZERO) {
		playerPos.y = 0;

		PlayerStateManager::playerState_ = PlayerStateManager::playerIdleState_;
		PlayerStateManager::playerState_->Enter(player);
	}

	player->SetPosition(playerPos);

	

	HandleInput(player);
}

void PlayerJumpState::HandleInput(Player* player)
{
	if (Input::IsKeyDown(DIK_Q)) {
		PlayerStateManager::playerState_ = PlayerStateManager::playerDieState_;
		PlayerStateManager::playerState_->Enter(player);
	}
}

void PlayerJumpState::Enter(Player* player)
{

	//�����o�ϐ�������������
	velocity_ = JUMP_VELOCITY;

}
