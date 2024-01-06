#include "PlayerStateManager.h"

//�estatic�ϐ�������������Bstatic������O���[�o���Ȉʒu�ōŏ��ɏ��������Ȃ��ƃ_��
PlayerAttackState* PlayerStateManager::playerAttackState_ = new PlayerAttackState;
PlayerDieState* PlayerStateManager::playerDieState_ = new PlayerDieState;
PlayerIdleState* PlayerStateManager::playerIdleState_ = new PlayerIdleState;
PlayerJumpState* PlayerStateManager::playerJumpState_ = new PlayerJumpState;
PlayerRunState* PlayerStateManager::playerRunState_ = new PlayerRunState;

PlayerState* PlayerStateManager::playerState_ = playerIdleState_;

PlayerStateManager::PlayerStateManager()
{

	
}

void PlayerStateManager::Update(Player* player)
{
	playerState_->Update(player);
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
