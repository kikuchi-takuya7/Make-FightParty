#pragma once
#include "PlayerAttackState.h"
#include "PlayerDieState.h"
#include "PlayerIdleState.h"
#include "PlayerJumpState.h"
#include "PlayerRunState.h"
#include "PlayerState.h"

class Player;

/// <summary>
/// playerの状態を管理する
/// </summary>
class PlayerStateManager : public PlayerState
{

public:

	static PlayerState* playerState_;
	
	//いちいちstateをnewして変えるより事前に静的に保持しておけばメモリの節約になる
	static PlayerAttackState* playerAttackState_;
	static PlayerDieState* playerDieState_;
	static PlayerIdleState* playerIdleState_;
	static PlayerJumpState* playerJumpState_;
	static PlayerRunState* playerRunState_;

	PlayerStateManager();

	virtual void Update(Player* player) override;

	virtual void HandleInput(Player* player) override;

	virtual void Enter(Player* player) override;

	/// <summary>
	/// 状態を変更する
	/// </summary>
	/// <param name="change">変更後の状態</param>
	/// <param name="player">変更するプレイヤーのポインタ</param>
	void ChangeState(PlayerState* nextState, Player* player);
};

