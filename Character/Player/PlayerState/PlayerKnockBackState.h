#pragma once
#include "PlayerState.h"

/// <summary>
/// プレイヤーが走っている状態
/// </summary>
class PlayerKnockBackState : public PlayerState
{

public:

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="player">Playerのポインタ</param>
	void Update(Player* player) override;


	/// <summary>
	/// 入力によって状態を変化する
	/// </summary>
	/// <param name="player">Playerのポインタ</param>
	void HandleInput(Player* player) override;

	/// <summary>
	/// 状態変化したときに一度だけ呼ばれる関数
	/// </summary>
	/// <param name="player">Playerのポインタ</param>
	void Enter(Player* player) override;

	void SetEnemyRotate(XMFLOAT3 rot) { enemyRot_ = rot; }

	float GetRateValue(float begin, float end, float rate);

private:

	//時間（フレーム単位）
	int flame_;

	//緩急を付けるレート
	float rate_;

	//最終的な位置
	XMFLOAT3 lastPoint_;

	XMFLOAT3 enemyRot_;
};

