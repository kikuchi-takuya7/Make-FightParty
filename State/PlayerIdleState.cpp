#include "PlayerIdleState.h"
#include "PlayerStateManager.h"
#include "../Player/Player.h"

void PlayerIdleState::Update(Player* player)
{



	HandleInput(player);
}


void PlayerIdleState::HandleInput(Player* player)
{

	

	if (Input::IsKeyDown(DIK_F)) {
		PlayerStateManager::playerState_ = PlayerStateManager::playerAttackState_;
		PlayerStateManager::playerState_->Enter(player);
	}
	
	if (Input::IsKeyDown(DIK_SPACE)) {
		PlayerStateManager::playerState_ = PlayerStateManager::playerJumpState_;
		PlayerStateManager::playerState_->Enter(player);
	}

}

void PlayerIdleState::Enter(Player* player)
{
}
