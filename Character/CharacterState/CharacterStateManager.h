#pragma once
#include "CharacterAttackState.h"
#include "CharacterDieState.h"
#include "CharacterIdleState.h"
#include "CharacterJumpState.h"
#include "CharacterKnockBackState.h"
#include "CharacterRunState.h"
#include "CharacterState.h"

//class Character;



//プレイヤーと敵のステートマネージャ共通にしたほうがいい説もあり
//Characterクラスにステートマネージャ書けるし、当たり判定も継承しなくてよくなる

/// <summary>
/// Characterの状態を管理する
/// </summary>
class CharacterStateManager : public CharacterState
{

public:

	
	
	//いちいちstateをnewして変えるより事前に静的に保持しておけばメモリの節約になるっていう予想
	//staticにしちゃうとクラス別でstateの変数持てないじゃんね
	//enum使えばstatic使わなくても行けそうだけど、どっちがいいか
	CharacterAttackState* characterAttackState_;
	CharacterDieState* characterDieState_;
	CharacterIdleState* characterIdleState_;
	CharacterJumpState* characterJumpState_;
	CharacterKnockBackState* characterKnockBackState_;
	CharacterRunState* characterRunState_;

	CharacterState* characterState_;

	CharacterStateManager();

	void Update(Character* character) override;

	void HandleInput(Character* character) override;

	void Enter(Character* character) override;

	/// <summary>
	/// 状態を変更する
	/// </summary>
	/// <param name="change">変更後の状態</param>
	/// <param name="Character">変更するプレイヤーのポインタ</param>
	void ChangeState(CharacterStatePattern nextState, Character* character);

	void MoveCharacter(Character* character);

	
	//////////////////////////アクセス関数/////////////////////////////////


	//結局ここに静的に残してるstateで交換するならこの関数使っても結局上のこのクラス内の変数使うから意味なくね説

private:


};

