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
class PlayerStateManager
{

public:
	
	//いちいちstateをnewして変えるより事前に静的に保持しておけばメモリの節約になる
	static PlayerAttackState* playerAttackState_;
	static PlayerDieState* playerDieState_;
	static PlayerIdleState* playerIdleState_;
	static PlayerJumpState* playerJumpState_;
	static PlayerRunState* playerRunState_;

	static PlayerState* playerState_;

	PlayerStateManager();

	void Update(Player* player);

	void HandleInput(Player* player);

	void Enter(Player* player);

	/// <summary>
	/// 状態を変更する
	/// </summary>
	/// <param name="change">変更後の状態</param>
	/// <param name="player">変更するプレイヤーのポインタ</param>
	void ChangeState(PlayerState* nextState, Player* player);
	
	//結局ここに静的に残してるstateで交換するならこの関数使っても結局上のこのクラス内の変数使うから意味なくね説
};

