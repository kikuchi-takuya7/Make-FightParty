#pragma once
#include "EnemyState.h"

/// <summary>
/// プレイヤーが走っている状態
/// </summary>
class EnemyRunState : public EnemyState
{

public:

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="enemy">Enemyのポインタ</param>
	void Update(Enemy* enemy, CharacterAI* AI) override;


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

};

