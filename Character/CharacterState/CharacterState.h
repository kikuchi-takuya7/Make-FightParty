#pragma once
//#include "../Engine/GameObject.h"
#include "../../../Engine/Global.h"
#include "../../../Engine/Input.h"
#include "../../../Engine/Model.h"

//前方宣言
class Character;

//この順番でManagerのリストに入っている
enum CharacterStateList {
	IDLE,
	ATTACK,
	JUMP,
	KNOCKBACK,
	RUN,
	DIE,
	STATE_NUM
};

/// <summary>
/// CharacterStateの基底クラス
/// </summary>
class CharacterState
{

public:

	//コンストラクタ
	CharacterState(Character* character, int model);


	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() {};


	/// <summary>
	/// 入力によって状態を変化する
	/// </summary>
	virtual void HandleInput() {};

	/// <summary>
	/// 状態変化したときに一度だけ呼ばれる関数
	/// </summary>
	virtual void Enter() {};

	/// <summary>
	/// 今のstateから離れる時に一度だけ呼ばれる関数
	/// </summary>
	virtual void Leave() {};

protected:

	//プレイヤーかエネミーのインスタンスを持っておく
	Character* pCharacter_;

	int hCharacterModel_;

};

//純粋仮想関数にするとmanagerで実態を持てないからダメ