#pragma once
#include "CharacterAttackState.h"
#include "CharacterDieState.h"
#include "CharacterIdleState.h"
#include "CharacterJumpState.h"
#include "CharacterKnockBackState.h"
#include "CharacterRunState.h"
#include "CharacterState.h"
#include <vector>

/// <summary>
/// Characterの状態を管理する
/// </summary>
class CharacterStateManager : public CharacterState
{

public:
	
	//いちいちstateをnewして変えるより事前に保持しておけば負荷がかからない
	CharacterState* characterState_;

	//CharacterStateListのenum型順に入っている
	std::vector<CharacterState*> pCharacterStateList_;

	CharacterStateManager(Character* character, int model);
	~CharacterStateManager();

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

	/// <summary>
	/// 状態を変更する
	/// </summary>
	/// <param name="change">変更後の状態</param>
	/// <param name="Character">変更するプレイヤーのポインタ</param>
	void ChangeState(CharacterStateList nextState);

private:


};

