#pragma once
#include "EnemyState.h"

class BoxCollider;

/// <summary>
/// 攻撃した状態
/// </summary>
class EnemyAttackState : public EnemyState
{

public:

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="enemy">Enemyのポインタ</param>
	void Update(Enemy* enemy) override;


	/// <summary>
	/// 入力によって状態を変化する
	/// </summary>
	/// <param name="enemy">Enemyのポインタ</param>
	void HandleInput(Enemy* enemy) override;

	/// <summary>
	/// 状態変化したときに一度だけ呼ばれる関数
	/// </summary>
	/// <param name="enemy">Enemyのポインタ</param>
	void Enter(Enemy* enemy) override;



private:

	int time_;
	//BoxCollider* pAttackCollision_;

};

