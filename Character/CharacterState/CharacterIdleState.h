#pragma once
#include "CharacterState.h"

/// <summary>
/// 動いてない状態
/// </summary>
class CharacterIdleState : public CharacterState
{

public:

	//コンストラクタ
	CharacterIdleState(Character* character, int model);

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

};

