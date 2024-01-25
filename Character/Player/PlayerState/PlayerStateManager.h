#pragma once
#include "PlayerAttackState.h"
#include "PlayerDieState.h"
#include "PlayerIdleState.h"
#include "PlayerJumpState.h"
#include "PlayerKnockBackState.h"
#include "PlayerRunState.h"
#include "PlayerState.h"

class Player;

enum StatePattern {
	ATTACK,
	DIE,
	IDLE,
	JUMP,
	KNOCKBACK,
	RUN,
	NUM
};

//プレイヤーと敵のステートマネージャ共通にしたほうがいい説もあり
//Characterクラスにステートマネージャ書けるし、当たり判定も継承しなくてよくなる

/// <summary>
/// playerの状態を管理する
/// </summary>
class PlayerStateManager
{

public:
	
	//いちいちstateをnewして変えるより事前に静的に保持しておけばメモリの節約になるっていう予想
	//ちなみに複数playerstateあってもちゃんとクラス毎にstaticで取ってくれる
	//enum使えばstatic使わなくても行けそうだけど、どっちがいいか
	PlayerAttackState* playerAttackState_;
	PlayerDieState* playerDieState_;
	PlayerIdleState* playerIdleState_;
	PlayerJumpState* playerJumpState_;
	PlayerKnockBackState* playerKnockBackState_;
	PlayerRunState* playerRunState_;

	PlayerState* playerState_;

	PlayerStateManager();

	void Update(Player* player);

	void HandleInput(Player* player);

	void Enter(Player* player);

	/// <summary>
	/// 状態を変更する
	/// </summary>
	/// <param name="change">変更後の状態</param>
	/// <param name="player">変更するプレイヤーのポインタ</param>
	void ChangeState(StatePattern nextState, Player* player);
	
	//結局ここに静的に残してるstateで交換するならこの関数使っても結局上のこのクラス内の変数使うから意味なくね説

private:
	StatePattern nowState_;
};

//先輩はここstateを継承してたけど継承した理由がよくわからなかったから継承しなかった。っていうメモ
