#pragma once
#include "CharacterState.h"

/// <summary>
/// 死んだ状態
/// </summary>
class CharacterDieState : public CharacterState
{

public:

	//コンストラクタ
	CharacterDieState(Character* characte, int modelr);

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

