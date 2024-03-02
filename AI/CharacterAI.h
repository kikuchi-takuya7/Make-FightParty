#pragma once
#include "AI.h"

class NavigationAI;
class MetaAI;
class Enemy;

/// <summary>
/// 敵キャラクターを動かすAI
/// </summary>
class CharacterAI : public AI
{

public:

	//コンストラクタ
	CharacterAI(GameObject* parent);
	CharacterAI(GameObject* parent,Enemy* enemy, NavigationAI* naviAI);

	//デストラクタ
	~CharacterAI();

	//////////////オーバーライドした関数////////////////

	//初期化
	void Initialize() override;

	//解放
	void Release() override;

	/////////////////メンバ関数/////////////////////////

	/// <summary>
	/// 狙うべき敵をMetaAIに聞く関数
	/// </summary>
	void AskTarget();

	/// <summary>
	/// MetaAIに情報を伝える関数
	/// </summary>
	void TellStatus();

	/// <summary>
	/// NavigationAIに行くべき場所を聞き、移動する関数
	/// </summary>
	void MoveEnemy();

	/// <summary>
	/// 攻撃するかどうかを指示する関数
	/// </summary>
	void IsAttack();

	/// <summary>
	/// クリエイトモードで選択したオブジェクトを移動させる関数
	/// </summary>
	/// <returns>動かした後のTransform</returns>
	Transform MoveSelectObject();

	///////////////////アクセス関数///////////////////

	void SetEnemy(Enemy* enemy) { pEnemy_ = enemy; }
	void SetNavigationAI(NavigationAI* AI) { pNavigationAI_ = AI; }
	void SetMetaAI(MetaAI* AI) { pMetaAI_ = AI; }

	void SetTargetID(int ID) { targetID_ = ID; }

private:

	NavigationAI* pNavigationAI_;

	MetaAI* pMetaAI_;

	//自分が操る敵のインスタンス
	Enemy* pEnemy_;

	//今自分が狙っている敵のID
	int targetID_;

};

