#pragma once
#include "EnemyState.h"

/// <summary>
/// プレイヤーが走っている状態
/// </summary>
class EnemyKnockBackState : public EnemyState
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
	void HandleInput(Enemy* enemy, CharacterAI* AI) override;

	/// <summary>
	/// 状態変化したときに一度だけ呼ばれる関数
	/// </summary>
	/// <param name="enemy">Enemyのポインタ</param>
	void Enter(Enemy* enemy, CharacterAI* AI) override;

	void SetPlayerRotate(XMFLOAT3 rot) { playerRot_ = rot; }

	float GetRateValue(float begin, float end, float rate);

private:

	//時間（フレーム単位）
	int flame_;

	//緩急を付けるレート
	float rate_;

	//最終的な位置
	XMFLOAT3 lastPoint_;

	XMFLOAT3 playerRot_;
};

