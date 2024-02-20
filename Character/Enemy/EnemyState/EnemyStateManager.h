#pragma once
#include "EnemyAttackState.h"
#include "EnemyDieState.h"
#include "EnemyIdleState.h"
#include "EnemyJumpState.h"
#include "EnemyKnockBackState.h"
#include "EnemyRunState.h"
#include "EnemyState.h"

//class Enemy;



/// <summary>
/// enemyの状態を管理する
/// </summary>
class EnemyStateManager : public EnemyState
{

public:

	
	//いちいちstateをnewして変えるより事前に静的に保持しておけばメモリの節約になるっていう予想
	EnemyAttackState* enemyAttackState_;
	EnemyDieState* enemyDieState_;
	EnemyIdleState* enemyIdleState_;
	EnemyJumpState* enemyJumpState_;
	EnemyKnockBackState* enemyKnockBackState_;
	EnemyRunState* enemyRunState_;

	EnemyState* enemyState_;

	EnemyStateManager();

	void Update(Enemy* enemy, CharacterAI* AI) override;

	void HandleInput(Enemy* enemy, CharacterAI* AI) override;

	void Enter(Enemy* enemy, CharacterAI* AI) override;

	/// <summary>
	/// 状態を変更する
	/// </summary>
	/// <param name="change">変更後の状態</param>
	/// <param name="enemy">変更するプレイヤーのポインタ</param>
	void ChangeState(EnemyStatePattern nextState, Enemy* enemy, CharacterAI* AI);

	//マネージャにAIのインスタンス持たせた所で結局update呼ぶときにはAI引数として必要だからなぁ
	//いっそのことそれぞれのstate全部のメンバ変数にAIの入れ物作る？それもなんか違う気がする
};
