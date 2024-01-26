#include "PlayerStateManager.h"
#include "../Player.h"

//各static変数を初期化する。staticだからグローバルな位置で最初に初期化しないとダメ
//PlayerAttackState* PlayerStateManager::playerAttackState_ = new PlayerAttackState;
//PlayerDieState* PlayerStateManager::playerDieState_ = new PlayerDieState;
//PlayerIdleState* PlayerStateManager::playerIdleState_ = new PlayerIdleState;
//PlayerJumpState* PlayerStateManager::playerJumpState_ = new PlayerJumpState;
//PlayerRunState* PlayerStateManager::playerRunState_ = new PlayerRunState;

//PlayerState* PlayerStateManager::playerState_ = playerIdleState_;

PlayerStateManager::PlayerStateManager()
{
	playerAttackState_ = new PlayerAttackState;
	playerDieState_ = new PlayerDieState;
	playerIdleState_ = new PlayerIdleState;
	playerJumpState_ = new PlayerJumpState;
	playerKnockBackState_ = new PlayerKnockBackState;
	playerRunState_ = new PlayerRunState;

	playerState_ = playerIdleState_;

	nowState_ = IDLE;
}

void PlayerStateManager::Update(Player* player)
{

	//ここに共通処理を書く。stateの処理を実行してからか実行する前かは後で決める

	//ノックバック中じゃなければ移動できるように
	if (player->IsKnockBack() == false) {

		player->MoveCharacter();
	}

	playerState_->Update(player);

}

void PlayerStateManager::HandleInput(Player* player)
{
}

void PlayerStateManager::Enter(Player* player)
{
}

void PlayerStateManager::ChangeState(PlayerStatePattern nextState, Player* player)
{

	//状態を変更して、その状態の初期化処理を行う
	switch (nextState)
	{
	case ATTACK:
		playerState_ = playerAttackState_;
		break;

	case DIE:
		playerState_ = playerDieState_;
		break;

	case IDLE:
		playerState_ = playerIdleState_;
		break;

	case JUMP:
		playerState_ = playerJumpState_;
		break;

	case KNOCKBACK:
		playerState_ = playerKnockBackState_;
		break;

	case RUN:
		playerState_ = playerRunState_;
		break;

	case NUM:

	default:
		return;
		break;
	}

	playerState_->Enter(player);
	
}
