#pragma once
#include "../Player/Player.h"
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

	PlayerState playerState_;
	
	//いちいちstateをnewして変えるより事前に静的に保持しておけばメモリの節約になる
	PlayerAttackState* playerAttackState_;
	PlayerDieState* playerDieState_;
	PlayerIdleState* playerIdleState_;
	PlayerJumpState* playerJumpState_;
	PlayerRunState* playerRunState_;

	virtual void Update(Player* player) override;

	virtual void HandleInput(Player* player) override;

	virtual void Enter(Player* player) override;
};

