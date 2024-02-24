#pragma once
#include "CharacterState.h"

/// <summary>
/// ジャンプしてる状態
/// </summary>
class CharacterJumpState : public CharacterState
{

public:

	//コンストラクタ
	CharacterJumpState(Character* character);

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

	float velocity_;

};

