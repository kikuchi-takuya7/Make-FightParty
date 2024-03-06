#pragma once
#include "CharacterState.h"

class BoxCollider;

/// <summary>
/// 攻撃している状態
/// </summary>
class CharacterAttackState : public CharacterState
{

public:

	//コンストラクタ
	CharacterAttackState(Character* character, int model);

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

	//当たり判定を設置済みか否か。設置済みならtrue
	bool settedCollision_;

	//攻撃時のSE
	int hAudio_;

};

