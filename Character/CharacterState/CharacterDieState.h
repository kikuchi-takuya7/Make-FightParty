#pragma once
#include "CharacterState.h"

/// <summary>
/// 死んだ状態
/// </summary>
class CharacterDieState : public CharacterState
{

public:

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="character">Characterのポインタ</param>
	void Update(Character* character) override;


	/// <summary>
	/// 入力によって状態を変化する
	/// </summary>
	/// <param name="character">Characterのポインタ</param>
	void HandleInput(Character* character) override;

	/// <summary>
	/// 状態変化したときに一度だけ呼ばれる関数
	/// </summary>
	/// <param name="character">Characterのポインタ</param>
	void Enter(Character* character) override;

};

