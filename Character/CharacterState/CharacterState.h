#pragma once
//#include "../Engine/GameObject.h"
#include "../../../Engine/Global.h"
#include "../../../Engine/Input.h"

//前方宣言
class Character;

enum CharacterStatePattern {
	ATTACK,
	DIE,
	IDLE,
	JUMP,
	KNOCKBACK,
	RUN
};

/// <summary>
/// CharacterStateの基底クラス
/// </summary>
class CharacterState
{

public:

	

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="Character">Characterのポインタ</param>
	virtual void Update(Character* character) {};


	/// <summary>
	/// 入力によって状態を変化する
	/// </summary>
	/// <param name="Character">Characterのポインタ</param>
	virtual void HandleInput(Character* character) {};

	/// <summary>
	/// 状態変化したときに一度だけ呼ばれる関数
	/// </summary>
	/// <param name="Character">Characterのポインタ</param>
	virtual void Enter(Character* character) {};

};

//純粋仮想関数にするとmanagerで実態を持てないからダメ