#pragma once

class Player;

class PlayerState
{
public:

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="player">Playerのポインタ</param>
	virtual void Update(Player* player) {};


	/// <summary>
	/// 入力によって状態を変化する
	/// </summary>
	/// <param name="player">Playerのポインタ</param>
	virtual void HandleInput(Player* player) {};

	/// <summary>
	/// 状態変化したときに一度だけ呼ばれる関数
	/// </summary>
	/// <param name="player">Playerのポインタ</param>
	virtual void Enter(Player* player) {};

	/// <summary>
	/// 状態変更
	/// </summary>
	/// <param name="nowState">現在の状態</param>
	/// <param name="state">変化したい状態</param>
	//void ChangeState(PlayerState* nowState, PlayerState* state);
};

