#pragma once
//#include "../Engine/GameObject.h"
#include "../../../Engine/Global.h"
#include "../../../Engine/Input.h"

//前方宣言
class Enemy;

/// <summary>
/// playerStateの基底クラス
/// </summary>
class EnemyState
{
public:

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="player">Enemyのポインタ</param>
	virtual void Update(Enemy* player) {};


	/// <summary>
	/// 入力によって状態を変化する
	/// </summary>
	/// <param name="player">Enemyのポインタ</param>
	virtual void HandleInput(Enemy* player) {};

	/// <summary>
	/// 状態変化したときに一度だけ呼ばれる関数
	/// </summary>
	/// <param name="player">Enemyのポインタ</param>
	virtual void Enter(Enemy* player) {};

};

//純粋仮想関数にするとmanagerで実態を持てないからダメ