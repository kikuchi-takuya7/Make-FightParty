#include "PlayerJumpState.h"
#include "PlayerStateManager.h"

void PlayerJumpState::Update(Player* player)
{

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
}
