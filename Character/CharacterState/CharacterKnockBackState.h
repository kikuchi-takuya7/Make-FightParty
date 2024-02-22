#pragma once
#include "CharacterState.h"

/// <summary>
/// プレイヤーが走っている状態
/// </summary>
class CharacterKnockBackState : public CharacterState
{

public:

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="Character">Characterのポインタ</param>
	void Update(Character* character) override;


	/// <summary>
	/// 入力によって状態を変化する
	/// </summary>
	/// <param name="Character">Characterのポインタ</param>
	void HandleInput(Character* character) override;

	/// <summary>
	/// 状態変化したときに一度だけ呼ばれる関数
	/// </summary>
	/// <param name="Character">Characterのポインタ</param>
	void Enter(Character* character) override;

private:

	//時間（フレーム単位）
	int flame_;
};

