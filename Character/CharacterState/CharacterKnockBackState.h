#pragma once
#include "CharacterState.h"

/// <summary>
/// プレイヤーが走っている状態
/// </summary>
class CharacterKnockBackState : public CharacterState
{

public:

	//コンストラクタ
	CharacterKnockBackState(Character* character);

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;


	/// <summary>
	/// 入力によって状態を変化する
	/// </summary>
	void HandleInput() override;

	/// <summary>
	/// 状態変化した最初に一度だけ呼ばれる関数
	/// </summary>
	void Enter() override;

	/// <summary>
	/// 今のstateから離れる時に一度だけ呼ばれる関数
	/// </summary>
	void Leave() override;

	float GetRateValue(float begin, float end, float rate);

private:

	//時間（フレーム単位）
	int flame_;

	//緩急を付けるレート
	float knockBackRate_;

	//最終的な位置
	XMFLOAT3 lastPoint_;
};

