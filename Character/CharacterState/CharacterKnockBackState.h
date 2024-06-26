#pragma once
#include "CharacterState.h"

class RateFrame;

/// <summary>
/// プレイヤーが攻撃を食らっている状態
/// </summary>
class CharacterKnockBackState : public CharacterState
{

public:

	//コンストラクタ
	CharacterKnockBackState(Character* character, int model);

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

private:

	//緩急を付けるレート
	float knockBackRate_;

	//最終的な位置
	XMFLOAT3 lastPoint_;

	//線形補間に使うレート値
	//RateFrame* rate_;
};

