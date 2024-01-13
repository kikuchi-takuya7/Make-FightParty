#pragma once
#include "EnemyAttackState.h"
#include "EnemyDieState.h"
#include "EnemyIdleState.h"
#include "EnemyJumpState.h"
#include "EnemyRunState.h"
#include "EnemyState.h"

class Enemy;

/// <summary>
/// enemyの状態を管理する
/// </summary>
class EnemyStateManager
{

public:

	//いちいちstateをnewして変えるより事前に静的に保持しておけばメモリの節約になるっていう予想
	static EnemyAttackState* enemyAttackState_;
	static EnemyDieState* enemyDieState_;
	static EnemyIdleState* enemyIdleState_;
	static EnemyJumpState* enemyJumpState_;
	static EnemyRunState* enemyRunState_;

	static EnemyState* enemyState_;

	EnemyStateManager();

	void Update(Enemy* enemy);

	void HandleInput(Enemy* enemy);

	void Enter(Enemy* enemy);

	/// <summary>
	/// 状態を変更する
	/// </summary>
	/// <param name="change">変更後の状態</param>
	/// <param name="enemy">変更するプレイヤーのポインタ</param>
	void ChangeState(EnemyState* nextState, Enemy* enemy);

	//結局ここに静的に残してるstateで交換するならこの関数使っても結局上のこのクラス内の変数使うから意味なくね説
};

//先輩はここstateを継承してたけど継承した理由がよくわからなかったから継承しなかった。っていうメモ
