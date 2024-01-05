#include "PlayerStateManager.h"



PlayerStateManager::PlayerStateManager()
{

	playerAttackState_ = new PlayerAttackState;
	playerDieState_ = new PlayerDieState;
	playerIdleState_ = new PlayerIdleState;
	playerJumpState_ = new PlayerJumpState;
	playerRunState_ = new PlayerRunState;

	playerState_ = playerIdleState_;
}

void PlayerStateManager::Update(Player* player)
{
}

void PlayerStateManager::HandleInput(Player* player)
{
}

void PlayerStateManager::Enter(Player* player)
{
}

void PlayerStateManager::ChangeState(PlayerState* nextState, Player* player)
{
	//��Ԃ�ύX���āA���̏�Ԃ̏������������s��
	playerState_ = nextState;
	playerState_->Enter(player);
}
