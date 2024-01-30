#pragma once
//#include "../Engine/GameObject.h"
#include "../../../Engine/Global.h"
#include "../../../Engine/Input.h"
//#include "../../../AI/CharacterAI.h"

//前方宣言
class Enemy;
class CharacterAI;

enum EnemyStatePattern {
	ENEMY_ATTACK,
	ENEMY_DIE,
	ENEMY_IDLE,
	ENEMY_JUMP,
	ENEMY_KNOCKBACK,
	ENEMY_RUN
};

/// <summary>
/// EnemyStateの基底クラス
/// </summary>
class EnemyState
{
public:


	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="enemy">Enemyのポインタ</param>
	virtual void Update(Enemy* enemy, CharacterAI* AI) {};


	/// <summary>
	/// 入力によって状態を変化する
	/// </summary>
	/// <param name="enemy">Enemyのポインタ</param>
	virtual void HandleInput(Enemy* enemy, CharacterAI* AI) {};

	/// <summary>
	/// 状態変化したときに一度だけ呼ばれる関数
	/// </summary>
	/// <param name="enemy">Enemyのポインタ</param>
	virtual void Enter(Enemy* enemy) {};

};

//純粋仮想関数にするとmanagerで実態を持てないからダメ