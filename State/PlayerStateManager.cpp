#include "PlayerStateManager.h"

//各static変数を初期化する。staticだからグローバルな位置で最初に初期化しないとダメ
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
	//状態を変更して、その状態の初期化処理を行う
	playerState_ = nextState;
	playerState_->Enter(player);
}
