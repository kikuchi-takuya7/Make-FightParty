#pragma once
#include "../State/PlayerState.h"


class PlayerJumpStatee : public PlayerState
{

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

};

