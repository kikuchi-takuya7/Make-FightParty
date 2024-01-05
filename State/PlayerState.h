#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Global.h"
//#include "../Player/Player.h"

class Player;

/// <summary>
/// playerStateの基底クラス
/// </summary>
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
	/// 状態を変更する
	/// </summary>
	/// <param name="nextState">次の状態</param>
	void ChangeState(PlayerState nextState);
};

