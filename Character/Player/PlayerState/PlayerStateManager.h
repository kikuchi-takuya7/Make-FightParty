#pragma once
#include "PlayerAttackState.h"
#include "PlayerDieState.h"
#include "PlayerIdleState.h"
#include "PlayerJumpState.h"
#include "PlayerKnockBackState.h"
#include "PlayerRunState.h"
#include "PlayerState.h"

//class Player;



//プレイヤーと敵のステートマネージャ共通にしたほうがいい説もあり
//Characterクラスにステートマネージャ書けるし、当たり判定も継承しなくてよくなる

/// <summary>
/// playerの状態を管理する
/// </summary>
class PlayerStateManager : public PlayerState
{

public:

	
	
	//いちいちstateをnewして変えるより事前に静的に保持しておけばメモリの節約になるっていう予想
	//staticにしちゃうとクラス別でstateの変数持てないじゃんね
	//enum使えばstatic使わなくても行けそうだけど、どっちがいいか
	PlayerAttackState* playerAttackState_;
	PlayerDieState* playerDieState_;
	PlayerIdleState* playerIdleState_;
	PlayerJumpState* playerJumpState_;
	PlayerKnockBackState* playerKnockBackState_;
	PlayerRunState* playerRunState_;

	PlayerState* playerState_;

	PlayerStateManager();

	void Update(Player* player) override;

	void HandleInput(Player* player) override;

	void Enter(Player* player) override;

	/// <summary>
	/// 状態を変更する
	/// </summary>
	/// <param name="change">変更後の状態</param>
	/// <param name="player">変更するプレイヤーのポインタ</param>
	void ChangeState(PlayerStatePattern nextState, Player* player);

	void MovePlayer(Player* player);

	
	//////////////////////////アクセス関数/////////////////////////////////

	void SetEnemyRot(XMFLOAT3 rot) { playerKnockBackState_->SetEnemyRotate(rot); }


	//結局ここに静的に残してるstateで交換するならこの関数使っても結局上のこのクラス内の変数使うから意味なくね説

private:


};

//先輩はここstateを継承してたけど継承した理由がよくわからなかったから継承しなかった。っていうメモ
//関数が共通してるからなのかなぁ
