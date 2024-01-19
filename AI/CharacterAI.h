#pragma once
#include "AI.h"
#include "NavigationAI.h"
#include "MetaAI.h"
#include "../Character/Enemy/Enemy.h"

class MetaAI;

/// <summary>
/// 敵キャラクターを動かすAI
/// </summary>
class CharacterAI : public AI
{

public:

	//コンストラクタ
	CharacterAI();
	CharacterAI(Enemy* enemy);

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


	///////////////////アクセス関数/////////////

	void SetEnemy(Enemy* enemy) { pEnemy_ = enemy; }


private:

	NavigationAI* pNavigationAI_;

	MetaAI* pMetaAI_;

	Enemy* pEnemy_;

};

