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
	CharacterAI();
	CharacterAI(Enemy* enemy, NavigationAI* naviAI);

	//デストラクタ
	~CharacterAI();

	/////////オーバーライドした関数///////

	//初期化
	void Initialize() override;

	//解放
	void Release() override;

	/////////////////メンバ関数//////////////////////////

	
	////////////////オブジェクトを操るメンバ関数///////////////////

	void MoveEnemy();

	void Attack();

	///////////////////アクセス関数/////////////

	void SetEnemy(Enemy* enemy) { pEnemy_ = enemy; }
	void SetNavigationAI(NavigationAI* AI) { pNavigationAI_ = AI; }

private:

	NavigationAI* pNavigationAI_;

	MetaAI* pMetaAI_;

	//自分が操る敵のインスタンス
	Enemy* pEnemy_;

};

